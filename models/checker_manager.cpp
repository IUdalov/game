#include "checker_manager.h"

#define MaxArrowsCount 15

#define POINTS_FOR_BIG_CH 4
#define POINTS_FOR_MIDDLE_CH 2
#define POINTS_FOR_SMALL_CH 1

//#define PoleWidth 8
//#define PoleHeight 8

static void CheckerToObj(PhChecker ch, ObjChecker& obj, double& x, double& y){
    x = ch.coord.x;
    y = ch.coord.y;
    obj.vSpeed.x = ch.speed.x;
    obj.vSpeed.y = ch.speed.y;
    obj.weight = ch.weight;

    obj.angle = ch.angle;
    obj.angle_speed = ch.angle_speed;
}
static void ObjToChecker(PhChecker& ch, ObjChecker obj, double x, double y, int radius){
    ch.coord.x = x;
    ch.coord.y = y;
    ch.speed.x = obj.vSpeed.x;
    ch.speed.y = obj.vSpeed.y;
    ch.weight = obj.weight;
    ch.rub = 0.13;//Rub::normal;
    ch.spring = Spring::normal;

    ch.angle = obj.angle;
    ch.angle_speed = obj.angle_speed;
    ch.radius = radius;
}
void AlignBetween( double& x, double width, double min, double max){
    if( (x - width) <= min)
        x = width + min + 1;
    if( (x + width) >= max)
        x = max - width - 1;
}


CheckerManager::CheckerManager() : Model( STO_CHEKERS, sizeof(ObjChecker)){
    CheckEnable = 0;
    memset(&FieldRect, 0 , sizeof(Rect));
    FieldMiddle = 0;
    NeedFlyToPos = false;
    players_progress = _1st;
    selector.busy[0] = selector.busy[1] = selector.busy[2] = false;
    CurNumMoveCh = 0;
    ChangeProgressAfterStop = false;
    points_1st = 0;
    points_2nd = 0;
    alive_che1_count  = alive_che2_count = 0;
}
CheckerManager::~CheckerManager(){

}
void CheckerManager::EventsHandler(int mess, void *data){
    Object obj, obj2;
    IDn ID, ID2;
    GameParam* gameparam;
    switch(mess){
    case ME_KEYDOWN:
        if(*((int*)data) == Qt::Key_Return){
            Root::PutEventToQueue( 0, SE_NEXTGAMEPART, STO_CHEKERS);
        }
        else if(*((int*)data) == Qt::Key_F2){
            if(game_part == End){
                gameparam = (GameParam*)Root::PutEventToQueue( sizeof(GameParam), SE_STARTGAME, STO_CHEKERS);
                memcpy(gameparam, &game_param, sizeof(GameParam));
            }
            else
                Root::PutEventToQueue( 0, SE_ENDGAME, STO_CHEKERS);
        }
        else if(*((int*)data) == Qt::Key_Escape){
            Root::CloseApp();
        }
        else if(*((int*)data) == Qt::Key_F1){
            Root::PutEventToQueue( 0, SE_REPLAY, STO_CHEKERS);
        }
        break;
    case ME_CREATE:
        break;
    case SE_STARTGAME:
        if(!data)
            return;
        gameparam = (GameParam*)data;
        Root::AddTimer(1);

        int *param;
        param = (int*)Root::PutEventToQueue(sizeof(int) * 2, SE_CREATEFIELD, STO_FIELD);
        if(param){
            *param = gameparam->FieldWidth;
            *(param + 1) = gameparam->FieldHeight;
        }
        game_part = Start;
        memcpy(&game_param, gameparam, sizeof(GameParam));
        break;
    case SE_FIELDPARAM:
        FieldRect = *((Rect*)data);
        FieldMiddle = (FieldRect.right + FieldRect.left) / 2;
        Root::PutEventToQueue( 0, SE_NEXTGAMEPART, STO_CHEKERS);
        break;
    case SE_INITSELECTOR:
        int yStep, xStep;
        int img1, img2, img3;
        switch(players_progress){
        case _1st:
            img1 = ID_BMP_BIG_CHEKER; img2 = ID_BMP_MID_CHEKER; img3 = ID_BMP_SMALL_CHEKER;
            xStep = FieldRect.left - Resources::GetTile(ID_BMP_BIG_CHEKER)->GetWidth();
            break;
        case _2nd:
            img1 = ID_BMP_BIG_CHEKER2; img2 = ID_BMP_MID_CHEKER2; img3 = ID_BMP_SMALL_CHEKER2;
            xStep = FieldRect.right + Resources::GetTile(ID_BMP_BIG_CHEKER2)->GetWidth();
            break;
        default:
            return;
        }
        yStep = (FieldRect.bottom - FieldRect.top) / 3;

        selector.pnt[0].x = xStep;
        selector.pnt[0].y = yStep / 2 + FieldRect.top;

        selector.pnt[1].x = xStep;
        selector.pnt[1].y = (yStep * 3) / 2 + FieldRect.top;

        selector.pnt[2].x = xStep;
        selector.pnt[2].y = (yStep * 5) / 2 + FieldRect.top;

        obj.subType = STO_CHEKERS;
        obj.sizeOfSubStr = sizeof(ObjChecker);
        obj.levelOfDraw = 2;
        obj.image = 0;
        obj.geo.type = GEO_BREP;
        obj.geo.preScaner = gps_for_checker;

        ClearSelector();

        ObjChecker* obj_ch;
        for(int i = 0 ; i < game_param.big_num; i ++){
            obj.tileId = img1;
            obj.SetRectByImage();
            obj.x = selector.pnt[0].x;
            obj.y = selector.pnt[0].y;
            ObjManager::CreateObj(obj, ID);
            this->SaveObj(ID);
            ObjManager::GetObj(ID, obj);
            obj_ch = ((ObjChecker*)obj.subStr);
            obj_ch->master = players_progress;
            obj_ch->weight = Weight::huge;
            obj_ch->vSpeed.x = obj_ch ->vSpeed.y = 0;
            obj_ch->type = big;
            obj_ch->angle = 0;
            obj_ch->angle_speed = 0.;
            selector.big_chs.push_back(ID);
        }
        for(int i = 0 ; i < game_param.midle_num; i ++){
            obj.tileId = img2;
            obj.SetRectByImage();
            obj.x = selector.pnt[1].x;
            obj.y = selector.pnt[1].y;
            ObjManager::CreateObj(obj, ID);
            this->SaveObj(ID);
            ObjManager::GetObj(ID, obj);
            obj_ch = ((ObjChecker*)obj.subStr);
            obj_ch->master = players_progress;
            obj_ch->weight = Weight::normal;
            obj_ch->vSpeed.x = obj_ch ->vSpeed.y = 0;
            obj_ch->type = middle;
            obj_ch->angle = 0;
            obj_ch->angle_speed = 0.;
            selector.middle_chs.push_back(ID);
        }
        for(int i = 0 ; i < game_param.small_num; i ++){
            obj.tileId = img3;
            obj.SetRectByImage();
            obj.x = selector.pnt[2].x;
            obj.y = selector.pnt[2].y;
            ObjManager::CreateObj(obj, ID);
            this->SaveObj(ID);
            ObjManager::GetObj(ID, obj);
            obj_ch = ((ObjChecker*)obj.subStr);
            obj_ch->master = players_progress;
            obj_ch->weight = Weight::low;
            obj_ch->vSpeed.x = obj_ch ->vSpeed.y = 0;
            obj_ch->type = small;
            obj_ch->angle = 0;
            obj_ch->angle_speed = 0.;
            selector.small_chs.push_back(ID);
        }
        selector.busy[0] = false;
        selector.busy[1] = false;
        selector.busy[2] = false;

        LocateSelector();
        break;
    case SE_NEXTGAMEPART:
        if(game_part == Start){
            Root::PutEventToQueue( 0, SE_INITSELECTOR, STO_CHEKERS);
            game_part = Disposal;
            points_1st = points_2nd = 0;
            alive_che1_count = alive_che2_count = 0;
            players_progress = _1st;
            CheckEnable = 0;
            Root::PutEventToQueue( 0, SE_FIELD_SHINE_LEFT, STO_FIELD);
            while(this->GetVolume())
                ObjManager::DeleteObj(this->GetObj(0));
        }
        else if(game_part == Disposal){
            if(players_progress == _1st){
                players_progress = _2nd;
                Root::PutEventToQueue( 0, SE_FIELD_SHINE_CLOSE, STO_FIELD);
                Root::PutEventToQueue( 0, SE_FIELD_SHINE_RIGHT, STO_FIELD);
                Root::PutEventToQueue( 0, SE_INITSELECTOR, STO_CHEKERS);
            }
            else if(players_progress == _2nd){
                Root::PutEventToQueue( 0, SE_FIELD_SHINE_CLOSE, STO_FIELD);
                ClearSelector();
                players_progress = _1st;
                game_part = Game;
                CheckEnable = 0;
                RecalcActualAliveCheCount();
            }
        }
        else if(game_part == Game){
            if(( alive_che1_count <= 0) || (alive_che2_count <= 0)){
                game_part = End;
                CheckEnable = 0;
            }
            else if(players_progress == _1st){
                players_progress = _2nd;
            }
            else if(players_progress == _2nd){
                players_progress = _1st;
            }
        }
        break;
    case SE_REPLAY:
        Root::PutEventToQueue( 0, SE_ENDGAME, STO_CHEKERS);
        gameparam = (GameParam*)Root::PutEventToQueue( sizeof(GameParam), SE_STARTGAME, STO_CHEKERS);
        memcpy(gameparam, &game_param, sizeof(GameParam));
        break;
    case SE_ENDGAME:
        game_part = End;
        CheckEnable = 0;
        arrows.clear();
        CurNumMoveCh = 0;
        ChangeProgressAfterStop = false;
        NeedFlyToPos = false;
        points_1st = 0;
        points_2nd = 0;
        alive_che1_count = 0;
        alive_che2_count = 0;
        Root::PutEventToQueue(0, SE_DELETEFIELD, STO_FIELD);
        while(this->GetVolume()){
            ObjManager::DeleteObj(this->GetObj(0));
            this->DeleteObj(0);
        }
        break;
    case ME_DRAW:
        if(*((int*)data) == 1){
/*            obj.tileId = ID_BMP_EXAMPLE;
            obj.image = 0;
            obj.SetRectByImage();
            obj.x = GLWindow::GetScreenWidth()
/2;
            obj.y = GLWindow::GetScreenHeight()/2;
            obj.Draw();*/
            if(CheckEnable > 0){
                {
                Object selector;
                ObjManager::GetObj(CheckChecker, obj2);
                switch(((ObjChecker*)obj2.subStr)->type){
                case big:
                    selector.tileId = ID_BMP_SELECTOR_BIG;
                    break;
                case middle:
                    selector.tileId = ID_BMP_SELECTOR_MIDDLE;
                    break;
                case small:
                    selector.tileId = ID_BMP_SELECTOR_SMALL;
                    break;
                default:
                    break;
                }
                selector.image = 0;
                selector.SetRectByImage();
                selector.x = obj2.x;
                selector.y = obj2.y;
                selector.Draw();
                }
            }
        }
        if(*((int*)data) == 3){
            if(CheckEnable == 2){
                for( int i = 0; i < (int)arrows.size(); i++)
                    arrows[i].Draw();
            }
        }
        break;
    case ME_TIMER:
        switch(game_part){
        case Disposal:
            Disposal_Timer(data);
            break;
        case Game:
            Game_Timer(data);
            break;
        default:
            break;
        }
        break;
    case OE_MOUSECLICK:
        switch(game_part){
        case Disposal:
            Disposal_MouseDown(((OEDMouse*)data)->idObj,
                                ((OEDMouse*)data)->mouse);
            break;
        case Game:
            Game_MouseDown(((OEDMouse*)data)->idObj,
                                ((OEDMouse*)data)->mouse);
            break;
        default:
            break;
        }
        break;
    case ME_MOUSECLICK:
        switch(game_part){
        case Disposal:
            Disposal_MouseUp();
            break;
        case Game:
            Game_MouseUp();
            break;
        default:
            break;
        }
        break;
    case ME_MOUSEMOVE:
        switch(game_part){
        case Disposal:
            Disposal_MouseMove();
            break;
        case Game:
            Game_MouseMove();
            break;
        default:
            break;
        }
        break;
    case OE_CLASH:
    ID = ((OEDClash*)data)->idDest;
    ID2 = ((OEDClash*)data)->idSrc;
    if(!ObjManager::GetObj(ID, obj))
        break;
    if(!ObjManager::GetObj(ID2, obj2))
        break;
    if( obj.subType != GetSubType() || obj2.subType != GetSubType() )
        break;
    if( sqrt( pow(obj.x - obj2.x, 2.) + pow(obj.y - obj2.y, 2.) ) <= (obj.GetWidth()/2 + obj2.GetWidth()/2) ){
        switch(game_part){
        case Disposal:
            Disposal_HitChToCh(data);
            break;
        case Game:
            Game_HitChToCh(data);
            break;
        default:
            break;
        }
    }
    break;
    }
}
void CheckerManager::CreateArrow( Object& arrow, double x_c, double y_c, double x_l,
                             double y_l, double length, int max_num_arrow ){

    double a, b, bs, as, cs;
    double step = (double)arrow.GetHeight();
    int num = ( sqrt( pow( x_l - x_c, 2.)  + pow( y_l - y_c, 2.)) - length) / step;
    arrows.clear();

    if(num > max_num_arrow)
        num = max_num_arrow;

    if(fabs(x_c - x_l) < 2.){
        arrow.x = x_l;
        if(y_c > y_l){
            for( int i = 0; i < num; i++){
                arrow.y = y_c - length - ((double)i + 0.5)*step;
                arrow.SetDefaultAngle();
                arrows.push_back(arrow);
            }
        }
        else{
            for( int i = 0; i < num; i++){
                arrow.y = y_c + length +  ((double)i + 0.5)*step;
                arrow.TurnImage(M_PI);
                arrows.push_back(arrow);
            }
        }
        return;
    }

    if(fabs(y_c - y_l) < 2.){
        arrow.y = y_l;
        if(x_c > x_l){
            for( int i = 0; i < num; i++){
                arrow.x = x_c - length - ((double)i + 0.5)*step;
                arrow.TurnImage( (M_PI * 3.) / 2.);
                arrows.push_back(arrow);
            }
        }
        else{
            for( int i = 0; i < num; i++){
                arrow.x = x_c + length + ((double)i + 0.5)*step;
                arrow.TurnImage( M_PI / 2.);
                arrows.push_back(arrow);
            }
        }
        return;
    }

    a = (y_c - y_l) / (x_c - x_l);
    b = y_l - a * x_l;

    bs = (2*x_c - 2*a*b + 2*a*y_c);
    as = 1 + pow(a, 2.);

    double dist = 0.;
    for( int i = 0; i < num; i++){
        dist = length + ((double)i + 0.5) * step;
        cs = pow(x_c, 2.) - pow(dist, 2.) + pow(b, 2.) - 2*b*y_c + pow(y_c, 2.);
        if( x_c < x_l )
            arrow.x = ( bs + sqrt( pow(bs, 2.) - 4*as*cs) ) /
                            ( 2*as);
        if( x_c > x_l )
            arrow.x = ( bs - sqrt( pow(bs, 2.) - 4*as*cs) ) /
                            ( 2*as);
        arrow.y = a*arrow.x + b;
        arrows.push_back(arrow);
    }

    double ang = atan(a);
    if( x_l < x_c){
        ang += (M_PI * 3.)/2.;
    }
    else if( x_l > x_c){
        ang += M_PI / 2.;
    }
    else if( fabs(x_c - x_l) < 2.){
        if( y_l > y_c)
            ang = M_PI;
        else
            ang = 0;
    }
    for( int i = 0; i < (int)arrows.size(); i++){
        if(ang == 0.)
            arrows[i].SetDefaultAngle();
        else
            arrows[i].TurnImage(ang);
    }
}
void CheckerManager::ClearSelector(void){
    if(selector.busy[0]){
        this->DeleteObj(selector.checker[0]);
        ObjManager::DeleteObj(selector.checker[0]);
    }
    if(selector.busy[1]){
        this->DeleteObj(selector.checker[1]);
        ObjManager::DeleteObj(selector.checker[1]);
    }
    if(selector.busy[2]){
        this->DeleteObj(selector.checker[2]);
        ObjManager::DeleteObj(selector.checker[2]);
    }

    for(int i = 0; i < (int)selector.big_chs.size(); i++){
        ObjManager::DeleteObj(selector.big_chs[i]);
        this->DeleteObj(selector.big_chs[i]);
    }
    selector.big_chs.clear();

    for(int i = 0; i < (int)selector.middle_chs.size(); i++){
        ObjManager::DeleteObj(selector.middle_chs[i]);
        this->DeleteObj(selector.middle_chs[i]);
    }
    selector.middle_chs.clear();

    for(int i = 0; i < (int)selector.small_chs.size(); i++){
        ObjManager::DeleteObj(selector.small_chs[i]);
        this->DeleteObj(selector.small_chs[i]);
    }
    selector.small_chs.clear();
}
void CheckerManager::PrepareForReturn(int type){
    if(selector.busy[type]){
        selector.busy[type] = false;
        IDn id = selector.checker[type];
        switch(type){
        case big:
            selector.big_chs.push_back(id);
            break;
        case middle:
            selector.middle_chs.push_back(id);
            break;
        case small:
            selector.small_chs.push_back(id);
            break;
        }
        ObjManager::DeleteFromGrid(id);
    }
}
void CheckerManager::LocateSelector(void){
    if(!selector.busy[0]){
        if(selector.big_chs.size()){
            selector.busy[0] = true;
            selector.checker[0] = selector.big_chs[selector.big_chs.size() - 1];
            selector.big_chs.pop_back();
            ObjManager::AddToGrid(selector.checker[0], false);
        }
    }
    if(!selector.busy[1]){
        if(selector.middle_chs.size()){
            selector.busy[1] = true;
            selector.checker[1] = selector.middle_chs[selector.middle_chs.size() - 1];
            selector.middle_chs.pop_back();
            ObjManager::AddToGrid(selector.checker[1], false);
        }
    }
    if(!selector.busy[2]){
        if(selector.small_chs.size()){
            selector.busy[2] = true;
            selector.checker[2] = selector.small_chs[selector.small_chs.size() - 1];
            selector.small_chs.pop_back();
            ObjManager::AddToGrid(selector.checker[2], false);
        }
    }
}
bool CheckerManager::RectInField(Rect r){
    if((FieldRect.left <= r.left) &&
            (FieldRect.right >= r.right) &&
            (FieldRect.top <= r.top) &&
            (FieldRect.bottom >= r.bottom)  )
        return true;
    else
        return false;
}
bool CheckerManager::RectInRect(Rect r1, Rect r2){
    if((r2.left <= r1.left) &&
            (r2.right >= r1.right) &&
            (r2.top <= r1.top) &&
            (r2.bottom >= r1.bottom)  )
        return true;
    else
        return false;
}
bool CheckerManager::RectOutField(Rect r){
    if((FieldRect.right < r.left) ||
            (FieldRect.left > r.right) ||
            (FieldRect.bottom < r.top) ||
            (FieldRect.top > r.bottom)  )
        return true;
    else
        return false;
}
bool CheckerManager::RectOutRect(Rect r1, Rect r2){
    if((r2.right < r1.left) ||
            (r2.left > r1.right) ||
            (r2.bottom < r1.top) ||
            (r2.top > r1.bottom)  )
        return true;
    else
        return false;
}
bool CheckerManager::CheckerInPartOfField(Rect rect, short part){
    Rect r;
    r.top = FieldRect.top;
    r.bottom = FieldRect.bottom;
    switch(part){
    case 0:
        r.left = FieldRect.left;
        r.right = FieldMiddle;
        break;
    case 1:
        r.left = FieldMiddle;
        r.right = FieldRect.right;
        break;
    default:
        r.left = FieldRect.left;
        r.right = FieldRect.right;
        break;
    }
    return RectInRect(rect, r);
}
bool CheckerManager::CheckerOutRect(DCoord crd, double radius, Rect rf){
    Rect r;
    r.left = crd.x - radius;
    r.right = crd.x + radius;
    r.top = crd.y - radius;
    r.bottom = crd.y + radius;
    if(!RectOutRect(r, rf)){
        if( crd.x < rf.left && crd.y < rf.top ){
            if( sqrt( pow(crd.x - rf.left, 2.)
                      + pow(crd.y - rf.top, 2.)) > radius){
                return false;
            }
        }
        if( crd.x > rf.right && crd.y < rf.top ){
            if( sqrt( pow(crd.x - rf.right, 2.)
                      + pow(crd.y - rf.top, 2.)) > radius){
                return false;
            }
        }
        if( crd.x > rf.right && crd.y > rf.bottom){
            if( sqrt( pow(crd.x - rf.right, 2.)
                      + pow(crd.y - rf.bottom, 2.)) > radius){
                return false;
            }
        }
        if( crd.x < rf.left && crd.y > rf.bottom ){
            if( sqrt( pow(crd.x - rf.left, 2.)
                      + pow(crd.y - rf.bottom, 2.)) > radius){
                return false;
            }
        }
        return true;
    }
    return false;
}
void CheckerManager::Disposal_Timer(void *data){
    Object obj;
    SMouse mouse;
    DCoord dcrd;
    if(*((int*)data) != 1)
        return;
    if(NeedFlyToPos){
        ObjManager::GetObj(CheckChecker,obj);
        ObjChecker* objch = (ObjChecker*)obj.subStr;
        ObjManager::DeleteFromGrid(CheckChecker);
        dcrd = objch->vSpeed;
        obj.x += dcrd.x;
        obj.y += dcrd.y;
        if(sqrt( pow( obj.x - point_to.x, 2.) + pow( obj.y - point_to.y, 2.) )<= 1 ){
            obj.x = point_to.x;
            obj.y = point_to.y;
            objch->vSpeed.x = objch->vSpeed.y = 0;
            NeedFlyToPos = false;
            selector.busy[objch->type] = true;
            selector.checker[objch->type] = CheckChecker;
        }
        ObjManager::ChangeObj(CheckChecker, obj);
        ObjManager::AddToGrid(CheckChecker, false);
    }
    else if( CheckEnable > 0 ){
        ObjManager::GetObj(CheckChecker,obj);
        ObjChecker* objch = (ObjChecker*)obj.subStr;
        mouse = Root::GetMouseStatus();
        if(sqrt( pow( obj.x - mouse.x, 2.) + pow( obj.y - mouse.y, 2.) )
            <= sqrt( pow( objch->vSpeed.x, 2.) + pow(objch->vSpeed.y, 2.)) ){
            objch->vSpeed.x = objch->vSpeed.y = 0;
            return;
        }
        ObjManager::DeleteFromGrid(CheckChecker);
        objch->vSpeed.x = (mouse.x - obj.x) / 10;
        objch->vSpeed.y = (mouse.y - obj.y) / 10;
        obj.x += objch->vSpeed.x;
        obj.y += objch->vSpeed.y;
        ObjManager::ChangeObj(CheckChecker, obj);
        ObjManager::AddToGrid(CheckChecker, true);
    }
}
void CheckerManager::Disposal_MouseDown(IDn id, SMouse mouse){
    Object obj;
    if(!ObjManager::GetObj(id, obj))
        return;
    if(NeedFlyToPos)
        return;
    if(mouse.L == Root::S_DOWN){
        if(obj.subType != STO_CHEKERS)
            return;
        if(((ObjChecker*)obj.subStr)->master != players_progress)
            return;
        CheckEnable = 1;
        CheckChecker = id;
        ObjManager::GetObj(CheckChecker, obj);
        int type = ((ObjChecker*)obj.subStr)->type;
        ((ObjChecker*)obj.subStr)->vSpeed.x =
           ((ObjChecker*)obj.subStr)->vSpeed.y = 0;
        if((selector.busy[type] == true)
                && (id == selector.checker[type])){
            selector.busy[type] = false;
        }
    }
}
void CheckerManager::Disposal_MouseUp(void){
    SMouse mouse = Root::GetMouseStatus();
    Object obj;
    if(mouse.L == Root::S_UP){
        if(CheckEnable > 0){
            ObjManager::GetObj(CheckChecker,obj);
            ObjChecker* objch = (ObjChecker*)obj.subStr;
            objch->vSpeed.x = 0;
            objch->vSpeed.y = 0;
            Rect r = obj.GetRect();
            if(CheckerInPartOfField(r, ((ObjChecker*)obj.subStr)->master)){
                LocateSelector();
            }
            else{
                switch(((ObjChecker*)obj.subStr)->type){
                case big:
                    point_to = selector.pnt[0];
                    break;
                case middle:
                    point_to = selector.pnt[1];
                    break;
                case small:
                    point_to = selector.pnt[2];
                    break;
                default:
                    break;
                }
                ObjManager::GetObj(CheckChecker,obj);
                ObjChecker* objch = (ObjChecker*)obj.subStr;
                objch->vSpeed.x = (point_to.x - obj.x) / 10;
                objch->vSpeed.y = (point_to.y - obj.y) / 10;
                int type = ((ObjChecker*)obj.subStr)->type;
                NeedFlyToPos = true;
                PrepareForReturn(type);
            }
        }
        CheckEnable = 0;
    }
}

void CheckerManager::Disposal_MouseMove(){
    //Object obj;
    //SMouse mouse;
    if(CheckEnable > 0){
        //тут был пересчет скорости выбраной шашки
    }
}
void CheckerManager::Disposal_HitChToCh(void *data){
    Object obj, obj2;
    IDn ID = *((IDn*)data);
    IDn ID2 = *((IDn*)data + 1);

    ObjChecker* ch1;
    ObjManager::GetObj(ID, obj);
    ObjManager::GetObj(ID2, obj2);
    ObjManager::DeleteFromGrid(ID);
    ch1 = ((ObjChecker*)obj.subStr);
    //ch2 = ((ObjChecker*)obj2.subStr);
    int t_length = Resources::GetTile(obj.tileId)->GetWidth() / 2 + Resources::GetTile(obj2.tileId)->GetWidth() / 2;
    int r_length = sqrt( pow( obj.x - obj2.x, 2.) + pow( obj.y - obj2.y, 2.) );
    double d = r_length - t_length;
    DCoord c1, c2;
    c1.x = obj.x; c1.y = obj.y;
    c2.x = obj2.x; c2.y = obj2.y;
    DCoord v = vect_min(c2,c1);
    ch1->vSpeed = v;
    ch1->vSpeed = vect_norm(ch1->vSpeed);
    ch1->vSpeed = vect_mult_d(ch1->vSpeed, d);
    obj.x += ch1->vSpeed.x;
    obj.y += ch1->vSpeed.y;
    ch1->vSpeed = vect_null();
    ObjManager::ChangeObj(ID, obj);
    ObjManager::AddToGrid(ID, true);
}


///////////////////////////////////////////////////////////////////////////////


void CheckerManager::Game_Timer(void *data){
    Object obj;
    if(*((int*)data) == 1){
        CurNumMoveCh = 0;
        for( int i = 0; i < (int)this->GetVolume(); i ++){
            ObjManager::GetObj(this->GetObj(i),obj);
            ObjChecker* objch = (ObjChecker*)obj.subStr;
            if( (objch->vSpeed.x == 0)  && (objch->vSpeed.y == 0)
                    && (objch->angle_speed == 0.)){
                DCoord crd = {obj.x, obj.y};
                if(!CheckerOutRect(crd, Resources::GetTile(obj.tileId)->GetWidth()/2, FieldRect)){
                    int points;
                    switch(objch->type){
                    case big:
                        points = POINTS_FOR_BIG_CH;
                        break;
                    case middle:
                        points = POINTS_FOR_MIDDLE_CH;
                        break;
                    case small: default:
                        points = POINTS_FOR_SMALL_CH;
                        break;
                    }
                    switch(objch->master){
                    case _1st:
                        points_1st += points;
                        alive_che1_count--;
                        break;
                    case _2nd:
                        points_2nd += points;
                        alive_che2_count--;
                        break;
                    default:
                        break;
                    }
                    ObjManager::DeleteObj(this->GetObj(i));
                    this->DeleteObj(this->GetObj(i));
                }
                continue;
            }
            CurNumMoveCh++;
            ObjManager::DeleteFromGrid(this->GetObj(i));
            PhChecker ch;
            ObjToChecker(ch, *objch, obj.x, obj.y, Resources::GetTile(obj.tileId)->GetWidth() / 2);
            //++движение
            Move(ch, 1./(double)(*((int*)data)));
            //--
            // ++столкновения со стенами
            /*PhWall wall;
            wall.spring = Spring::normal;
            if( ((obj.x - obj.GetWidth() / 2) < 0) || ( (obj.x + obj.GetWidth() / 2) > GLWindow::GetScreenWidth()
) ){
                AlignBetween(obj.x, obj.GetWidth()/2, 0, GLWindow::GetScreenWidth()
);
                ObjToChecker(ch, *objch, obj.x, obj.y);
                wall.phi = State::vertical;
                Clash(ch, wall);
            }
            if( ((obj.y - obj.GetHeight() / 2) < 0) || ((obj.y + obj.GetHeight() / 2) > GLWindow::GetScreenHeight()) ){
                AlignBetween(obj.y, obj.GetHeight() / 2, 0, GLWindow::GetScreenHeight());
                ObjToChecker(ch, *objch, obj.x, obj.y);
                wall.phi = State::horizontal;
                Clash(ch, wall);
            }*/
            // --столкновения со стенами
            CheckerToObj(ch, *objch, obj.x, obj.y);
            if(objch->angle){
                objch->angle = RoundConPi(objch->angle);
                obj.TurnImage(objch->angle);
            }
            ObjManager::ChangeObj(this->GetObj(i), obj);
            ObjManager::AddToGrid(this->GetObj(i), true);
        }
        if((!CurNumMoveCh) && ChangeProgressAfterStop){
            Root::PutEventToQueue( 0, SE_NEXTGAMEPART, STO_CHEKERS);
            ChangeProgressAfterStop = false;
        }
    }
}
void CheckerManager::Game_MouseDown(IDn id, SMouse mouse){
    Object obj;
    if(!ObjManager::GetObj(id, obj))
        return;
    if(CurNumMoveCh || (game_part == End))
        return;
    if(mouse.L == Root::S_DOWN){
        if(obj.subType != STO_CHEKERS)
            return;
        if(((ObjChecker*)obj.subStr)->master != players_progress)
            return;
        CheckEnable = 1;
        CheckChecker = id;
        ObjManager::GetObj(CheckChecker, obj);
        ((ObjChecker*)obj.subStr)->vSpeed.x =
        ((ObjChecker*)obj.subStr)->vSpeed.y = 0;
    }
}
void CheckerManager::Game_MouseUp(){
    Object obj;
    SMouse mouse = Root::GetMouseStatus();
    if(mouse.L == Root::S_UP){
        if(CheckEnable == 2){
            if(!arrows.size()){
                CheckEnable = 0;
                return;
            }
            mouse = Root::GetMouseStatus();
            ObjManager::GetObj(CheckChecker, obj);
            ObjChecker* obj_checker = ((ObjChecker*)obj.subStr);
            double coef = ( arrows.size() );
            DCoord v1 = {(double)mouse.x, (double)mouse.y}, v2 = {obj.x, obj.y};
            v1 = vect_min(v1, v2);
            v1 = vect_norm(v1);
            v1 = vect_mult_d(v1, coef);
            obj_checker->vSpeed.x = v1.x;
            obj_checker->vSpeed.y = v1.y;
            ObjManager::ChangeObj(CheckChecker, obj);
            ChangeProgressAfterStop = true;
        }
        CheckEnable = 0;
    }
}
void CheckerManager::Game_MouseMove(){
    Object obj;
    SMouse mouse;
    if(game_part == End)
            return;
    if(CheckEnable > 0){
        Object arrow;
        arrow.tileId = ID_BMP_ARROW;
        arrow.image = 0;
        arrow.SetRectByImage();

        mouse = Root::GetMouseStatus();
        ObjManager::GetObj(CheckChecker,obj);
        int xr, yr;
        xr = mouse.x - obj.x;
        yr = mouse.y - obj.y;
        if(sqrt( pow(xr, 2.) + pow(yr, 2.)) >=  ((double)obj.GetWidth())/2){
            CheckEnable = 2;
            CreateArrow( arrow, obj.x, obj.y, mouse.x, mouse.y, obj.GetWidth()/2, MaxArrowsCount);
        }
        else{
            CheckEnable = 1;
        }
    }
}
void CheckerManager::Game_HitChToCh(void* data){
    Object obj, obj2;
    IDn ID = *((IDn*)data);
    IDn ID2 = *((IDn*)data + 1);
    ObjManager::GetObj(ID, obj);
    ObjManager::GetObj(ID2, obj2);
    ObjManager::DeleteFromGrid(ID);
    DCoord v1,v2, v3;
    v1.x = obj.x; v1.y = obj.y;
    v2.x = obj2.x; v2.y = obj2.y;
    v3 = vect_min(v1, v2);
    v3 = vect_norm(v3);
    v3 = vect_mult_d(v3, Resources::GetTile(obj.tileId)->GetWidth() / 2 + Resources::GetTile(obj2.tileId)->GetWidth() / 2);
    v3 = vect_sum(v2, v3);
    obj.x = v3.x;
    obj.y = v3.y;
    ObjManager::ChangeObj(ID, obj);
    ObjManager::AddToGrid(ID, false);
    PhChecker ch1, ch2;
    ObjToChecker( ch1, *((ObjChecker*)obj.subStr),
                  obj.x, obj.y, Resources::GetTile(obj.tileId)->GetWidth() / 2 );
    ObjToChecker( ch2, *((ObjChecker*)obj2.subStr),
                  obj2.x, obj2.y, Resources::GetTile(obj2.tileId)->GetWidth() / 2);
    Clash(ch1, ch2);
    CheckerToObj( ch1, *((ObjChecker*)obj.subStr), obj.x, obj.y );
    CheckerToObj( ch2, *((ObjChecker*)obj2.subStr), obj2.x, obj2.y );

    //костыль чтоб крутилось
    //((ObjChecker*)obj.subStr)->angle_speed = M_PI /10;
    //
    if(((ObjChecker*)obj.subStr)->angle)
        obj.TurnImage(((ObjChecker*)obj.subStr)->angle);
    if(((ObjChecker*)obj2.subStr)->angle)
        obj.TurnImage(((ObjChecker*)obj2.subStr)->angle);
    ObjManager::ChangeObj(ID, obj);
    ObjManager::ChangeObj(ID2, obj2);
}

void CheckerManager::RecalcActualAliveCheCount(){
    Object obj;
    alive_che1_count = alive_che2_count = 0;
    for( int i = 0; i < (int)this->GetVolume(); i++){
        if(ObjManager::GetObj(this->GetObj(i), obj)){
            switch(((ObjChecker*)obj.subStr)->master){
            case _1st:
                alive_che1_count++;
                break;
            case _2nd:
                alive_che2_count++;
                break;
            default:
                break;
            }
        }
    }
}
