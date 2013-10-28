#include "geo.h"
#include "object.h"

namespace INDIan{
    GeoScaner::GeoScaner(){
        currElem = -1;
        status = GSS_BREAK;
    }
    GeoScaner::~GeoScaner(){

    }
    bool GeoScaner::GeoScan(GEO_SCAN_TYPE _geoType, Object obj, void* data){
        return true;
    }
    void GeoScaner::Init(GEO_SCAN_TYPE _geoType, vector<Object> inVObj, void* _data, int dataSize){
        if((_geoType == GST_BREP_BREP) && (((Object*)_data)->geo.type == GEO_NONE)){
            status = GSS_BREAK;
            return;
        }
        geoType = _geoType;
        vObj = inVObj;
        data = malloc(dataSize);
        memcpy(data, _data, dataSize);
        currElem = -1;
        status = GSS_DO;
    }

    GEO_SCAN_ANS GeoScaner::Scan(){
        if(!vObj.size())
            return GSA_CANCEL;
        if(currElem < 0){
            currElem = 0;
        }
        else{
            currElem++;
            if(currElem >= (int)vObj.size())
                return GSA_CANCEL;
        }
        if( status & GSS_BREAK )
            return GSA_CANCEL;
        if(vObj[currElem].geo.preScaner){
            status = (GEO_SCAN_STATUS)(*vObj[currElem].geo.preScaner)(geoType, vObj[currElem], data);
            if(geoType == GST_BREP_BREP)
                status = (GEO_SCAN_STATUS)(status |
                           (*((Object*)data)->geo.preScaner)(geoType, *((Object*)data), &vObj[currElem]));
        }
        if( status & GSS_DO){
            status = ((GEO_SCAN_STATUS)(status & ~GSS_DO));
            if(vObj[currElem].geo.type == GEO_BREP)
                status = ((GEO_SCAN_STATUS)(status | GeoScan(geoType, vObj[currElem], data)));
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
        return currElem;
    }
    Object GeoScaner::GetCurrElem(){
        return vObj[currElem];
    }
}
