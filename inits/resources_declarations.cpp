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

    Resources.Add_BMP(ID_BMP_SELECTOR_BIG, QString("../images/selector_big.bmp"), QString("../images/selector_big_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_SELECTOR_MIDDLE, QString("../images/selector_middle.bmp"), QString("../images/selector_middle_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_SELECTOR_SMALL, QString("../images/selector_small.bmp"), QString("../images/selector_small_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_BTNPLAY, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_ARROW, QString("../images/arrow.bmp"), QString("../images/arrow_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_CELL, QString("../images/cell.bmp"), QString("../images/cell_mask.bmp"), 9, 3, 3);

    Resources.Add_BMP(ID_BMP_MENU_PLAY, QString("../images/button_menu_play.bmp"), QString("../images/button_menu_play_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_RULES, QString("../images/button_rules.bmp"), QString("../images/button_rules_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_OPTIONS, QString("../images/button_options.bmp"), QString("../images/button_optionsr_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_EXIT, QString("../images/button_exit.bmp"), QString("../images/button_exit_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_BACK, QString("../images/button_back.bmp"), QString("../images/button_back_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_PLAY, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_PAUSE, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);
    Resources.Add_BMP(ID_BMP_RESTART, QString("../images/button_restart.bmp"), QString("../images/button_restart_mask.bmp"), 1, 1, 1);

//    Resources.Add_BMP(ID_BMP_EXAMPLE, QString("../images/triangle.jpg"), QString(""), 1, 1, 1);
END
