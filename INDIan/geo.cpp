#include "geo.h"

namespace INDIan{
    GeoScaner::GeoScaner(){
        curr_elem = -1;
        status = GSS_BREAK;
    }
    GeoScaner::~GeoScaner(){

    }
    void GeoScaner::init(GEO_SCAN_TYPE inGeoType, vector<Object> inVObj, void* inData, int inDataSize){
        if((inGeoType == GST_BREP_BREP) && (((Object*)inData)->geo.type == GEO_NONE)){
            status = GSS_BREAK;
            return;
        }
        geo_type = inGeoType;
        vObj = inVObj;
        data = malloc(inDataSize);
        memcpy(data, inData, inDataSize);
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
        if(vObj[curr_elem].geo.preScaner){
            status = (GEO_SCAN_STATUS)(*vObj[curr_elem].geo.preScaner)(geo_type, vObj[curr_elem], data);
            if(geo_type == GST_BREP_BREP)
                status = (GEO_SCAN_STATUS)(status |
                           (*((Object*)data)->geo.preScaner)(geo_type, *((Object*)data), &vObj[curr_elem]));
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
    Object GeoScaner::GetCurrElem(){
        return vObj[curr_elem];
    }
}
