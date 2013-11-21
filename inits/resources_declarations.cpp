#include "declarations.h"

using namespace INDIan;

void initImages(){
    Resources::SetTileCount(NumTileRes);

//    Resources::AddTile(ID_BMP_BIG_CHEKER, QString("../images/big_checker.bmp"), QString("../images/big_ch_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_BIG_CHEKER, QString("../images/men.bmp"), QString("../images/men_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_MID_CHEKER, QString("../images/men_middle.bmp"), QString("../images/men_mask_middle.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_SMALL_CHEKER, QString("../images/men_small.bmp"), QString("../images/men_mask_small.bmp"), 1, 1, 1);

    Resources::AddTile(ID_BMP_BIG_CHEKER2, QString("../images/men2.bmp"), QString("../images/men2_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_MID_CHEKER2, QString("../images/men2_middle.bmp"), QString("../images/men2_mask_middle.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_SMALL_CHEKER2, QString("../images/men2_small.bmp"), QString("../images/men2_mask_small.bmp"), 1, 1, 1);

    Resources::AddTile(ID_BMP_SELECTOR_BIG, QString("../images/selector_big.bmp"), QString("../images/selector_big_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_SELECTOR_MIDDLE, QString("../images/selector_middle.bmp"), QString("../images/selector_middle_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_SELECTOR_SMALL, QString("../images/selector_small.bmp"), QString("../images/selector_small_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_BTNPLAY, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);

    Resources::AddTile(ID_BMP_ARROW, QString("../images/arrow.bmp"), QString("../images/arrow_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_CELL, QString("../images/cell.bmp"), QString("../images/cell_mask.bmp"), 9, 3, 3);
    Resources::AddTile(ID_BMP_CELL_SHINE1, QString("../images/cell_shine1.bmp"), QString("../images/cell_shine1_mask.bmp"), 9, 3, 3);
    Resources::AddTile(ID_BMP_CELL_SHINE2, QString("../images/cell_shine2.bmp"), QString("../images/cell_shine2_mask.bmp"), 9, 3, 3);
    Resources::AddTile(ID_BMP_CELL_SHINE3, QString("../images/cell_shine3.bmp"), QString("../images/cell_shine3_mask.bmp"), 9, 3, 3);

    Resources::AddTile(ID_BMP_MENU_SINGLE, QString("../images/button_menu_single.bmp"), QString("../images/button_menu_single_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_MENU_MULTI, QString("../images/button_menu_multi.bmp"), QString("../images/button_menu_multi_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_RULES, QString("../images/button_rules.bmp"), QString("../images/button_rules_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_OPTIONS, QString("../images/button_options.bmp"), QString("../images/button_optionsr_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_EXIT, QString("../images/button_exit.bmp"), QString("../images/button_exit_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_BACK, QString("../images/button_back.bmp"), QString("../images/button_back_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_PLAY, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_PAUSE, QString("../images/button_play.bmp"), QString("../images/button_play_mask.bmp"), 1, 1, 1);
    Resources::AddTile(ID_BMP_RESTART, QString("../images/button_restart.bmp"), QString("../images/button_restart_mask.bmp"), 1, 1, 1);
}
