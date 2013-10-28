#ifndef GEO_H
#define GEO_H

#include "dependences.h"
#include "transport.h"
#include "formuls.h"


namespace INDIan{
    class Object;

    class GeoScaner{
        GEO_SCAN_TYPE geoType;
        vector<Object> vObj;
        void* data;
        int currElem;
        GEO_SCAN_STATUS status;

        bool GeoScan(GEO_SCAN_TYPE _geoType, Object obj, void* data);
    public:
        GeoScaner();
        ~GeoScaner();
        void Init(GEO_SCAN_TYPE _geoType, vector<Object> vobj, void* data, int dataSize);
        GEO_SCAN_ANS Scan();
        int GetCurrElemNum();
        Object GetCurrElem();
    };
}

#endif // GEO_H
