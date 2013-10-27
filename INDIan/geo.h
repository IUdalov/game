#ifndef GEO_H
#define GEO_H

#include "object.h"
#include "transport.h"
#include "dependences.h"
#include "formuls.h"

namespace INDIan{
    class GeoScaner{
        GEO_SCAN_TYPE geo_type;
        vector<Object> vObj;
        void* data;
        int curr_elem;
        GEO_SCAN_STATUS status;

        bool geo_scan(GEO_SCAN_TYPE geoType, Object obj, void* data){
            return false;
        }
    public:
        GeoScaner();
        ~GeoScaner();
        void init(GEO_SCAN_TYPE geo_type, vector<Object> vobj, void* data, int in_data_size);
        GEO_SCAN_ANS scan();
        int GetCurrElemNum();
        Object GetCurrElem();
    };
}

#endif // GEO_H
