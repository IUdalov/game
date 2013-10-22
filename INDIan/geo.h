#ifndef GEO_H
#define GEO_H

#include "core_includes.h"

class GeoScaner{
    GEO_SCAN_TYPE geo_type;
    vector<CObj> vObj;
    void* data;
    int curr_elem;
    GEO_SCAN_STATUS status;
    
    bool geo_scan(GEO_SCAN_TYPE geoType, CObj obj, void* data){
        return false;
    }
public:
    GeoScaner();
    ~GeoScaner();
    void init(GEO_SCAN_TYPE geo_type, vector<CObj> vobj, void* data, int in_data_size);
    GEO_SCAN_ANS scan();
    int GetCurrElemNum();
    CObj GetCurrElem();
};

#endif // GEO_H
