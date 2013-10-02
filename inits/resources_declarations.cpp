#include "../INDIan/resources.h"
#include "declarations.h"
extern cResources Resources;

BEGIN INIT_BMP SETCOUNT NumBmpRes PLEASE
    Resources.Add_BMP(ID_BMP_BACKGROUND, QString("../images/Untitled.bmp"), QString("../images/mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_ARROW, QString("../images/arrow.bmp"), QString("../images/arrow_mask.bmp"), 1, 1, 1);
END
