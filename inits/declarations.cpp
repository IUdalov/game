#include "../INDIan/core_includes.h"
#include "declarations.h"

extern cResources Resources;

GEO_SCAN_STATUS gps_for_menu_rect(GEO_SCAN_TYPE geo_pr_type, CObj obj, void* geo_pr_data){
    switch(geo_pr_type){
    case GST_BREP_BREP:
        return GSS_CONTINUE;
    case GST_BREP_PNT:
    {
        dCoord crd = *((dCoord*)geo_pr_data);
        if(HitRectCrd(obj.GetRect(), crd.x, crd.y))
            return GEO_SCAN_STATUS(GSS_OK | GSS_BREAK);
    }
    default:
        return GSS_CONTINUE;
    }
    return GSS_CONTINUE;
}
GEO_SCAN_STATUS gps_for_menu_circle(GEO_SCAN_TYPE geo_pr_type, CObj obj, void* geo_pr_data){
    switch(geo_pr_type){
    case GST_BREP_BREP:
        return GSS_CONTINUE;
    case GST_BREP_PNT:
    {
        dCoord crd = *((dCoord*)geo_pr_data);
        if( sqrt( pow(crd.x - obj.x, 2.) + pow(crd.y - obj.y, 2.))
                < Resources.Get_BMP(obj.BMP)->GetWidth() / 2)
            return GEO_SCAN_STATUS(GSS_OK | GSS_BREAK);
    }
    default:
        return GSS_CONTINUE;
    }
    return GSS_CONTINUE;
}
GEO_SCAN_STATUS gps_for_checker(GEO_SCAN_TYPE geo_pr_type, CObj obj, void* geo_pr_data){
    switch(geo_pr_type){
    case GST_BREP_BREP:
    {
        CObj* obj2 = ((CObj*)geo_pr_data);
        if( sqrt( pow(obj.x - obj2->x, 2.) + pow(obj.y - obj2->y, 2.))
                <= (Resources.Get_BMP(obj.BMP)->GetWidth() / 2 +
                   Resources.Get_BMP(obj2->BMP)->GetWidth() / 2 ))
            return GEO_SCAN_STATUS(GSS_OK | GSS_CONTINUE);
        return GSS_CONTINUE;
    }
    case GST_BREP_PNT:
    {
        dCoord crd = *((dCoord*)geo_pr_data);
        if( sqrt( pow(crd.x - obj.x, 2.) + pow(crd.y - obj.y, 2.))
                <= Resources.Get_BMP(obj.BMP)->GetWidth() / 2)
            return GEO_SCAN_STATUS(GSS_OK | GSS_BREAK);
    }
    default:
        return GSS_CONTINUE;
    }
    return GSS_CONTINUE;
}

