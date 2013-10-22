#include "geo.h"

GeoScaner::GeoScaner(){
    curr_elem = -1;
    status = GSS_BREAK;
}
GeoScaner::~GeoScaner(){
    
}
void GeoScaner::init(GEO_SCAN_TYPE in_geo_type, vector<CObj> in_vobj, void* in_data, int in_data_size){
    if((in_geo_type == GST_BREP_BREP) && (((CObj*)in_data)->geo.type == GEO_NONE)){
        status = GSS_BREAK;
        return;
    }
    geo_type = in_geo_type;
    vObj = in_vobj;
    data = malloc(in_data_size);
    memcpy(data, in_data, in_data_size);
    curr_elem = -1;
    status = GSS_DO;
}

GEO_SCAN_ANS GeoScaner::scan(){
    if(!vObj.size())
        return GSA_CANCEL;
    if(curr_elem < 0){
        curr_elem = 0;
    }
    else{
        curr_elem++;
        if(curr_elem >= (int)vObj.size())
            return GSA_CANCEL;
    }
    if( status & GSS_BREAK )
        return GSA_CANCEL;
    if(vObj[curr_elem].geo.pre_processor){
        status = (GEO_SCAN_STATUS)(*vObj[curr_elem].geo.pre_processor)(geo_type, vObj[curr_elem], data);
        if(geo_type == GST_BREP_BREP)
            status = (GEO_SCAN_STATUS)(status |
                       (*((CObj*)data)->geo.pre_processor)(geo_type, *((CObj*)data), &vObj[curr_elem]));
    }
    if( status & GSS_DO){
        status = ((GEO_SCAN_STATUS)(status & ~GSS_DO));
        if(vObj[curr_elem].geo.type == GEO_BREP)
            status = ((GEO_SCAN_STATUS)(status | geo_scan(geo_type, vObj[curr_elem], data)));
        else
            status = ((GEO_SCAN_STATUS)(status | GSS_CONTINUE));
    }
    if( status & GSS_CONTINUE){
        status = ((GEO_SCAN_STATUS)(status & ~GSS_CONTINUE));
        status = ((GEO_SCAN_STATUS)(status | GSS_DO));
    }
    else
        status = ((GEO_SCAN_STATUS)(status | GSS_BREAK));
    if( status & GSS_OK){
        status = ((GEO_SCAN_STATUS)(status & ~GSS_OK));
        return GSA_OK;
    }
    return GSA_CONTINUE;
}
int GeoScaner::GetCurrElemNum(){
    return curr_elem;
}
CObj GeoScaner::GetCurrElem(){
    return vObj[curr_elem];
}

