#include "../INDIan/resources.h"
#include "declarations.h"
extern cResources Resources;

BEGIN INIT_BMP SETCOUNT NumBmpRes PLEASE
    Resources.Add_BMP(ID_BMP_BIG_CHEKER, QString("../images/big_checker.bmp"), QString("../images/big_ch_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_MID_CHEKER, QString("../images/middle_checker.bmp"), QString("../images/middle_ch_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_SMALL_CHEKER, QString("../images/small_checker.bmp"), QString("../images/small_ch_mask.bmp"), 1, 1, 1);

    Resources.Add_BMP(ID_BMP_BIG_CHEKER2, QString("../images/big_checker2.bmp"), QString("../images/big_ch2_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_MID_CHEKER2, QString("../images/middle_checker2.bmp"), QString("../images/middle_ch2_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_SMALL_CHEKER2, QString("../images/small_checker2.bmp"), QString("../images/small_ch2_mask.bmp"), 1, 1, 1);

    Resources.Add_BMP(ID_BMP_BTNPLAY, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_ARROW, QString("../images/arrow.bmp"), QString("../images/arrow_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_CELL, QString("../images/cell.bmp"), QString("../images/cell_mask.bmp"), 1, 1, 1);

    Resources.Add_BMP(ID_BMP_MENU_PLAY, QString("../images/arrow.bmp"), QString("../images/arrow_mask.bmp"), 1, 1, 1);
END
