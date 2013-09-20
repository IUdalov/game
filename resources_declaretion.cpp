#include "INDIan/resources.h"
extern cResources Resources;

BEGIN INIT_BMP //"/home/mihacooper/projects/game/Untitled.bmp"
    Resources.Add_BMP(ID_BMP_BACKGROUND, QString("Images/Untitled.bmp"), QString("Images/mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_ARROW, QString("Images/arrow.bmp"), QString("Images/arrow_mask.bmp"), 1, 1, 1);
END
