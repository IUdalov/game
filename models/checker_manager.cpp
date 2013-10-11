#include "checker_manager.h"

CheckerManager Example;

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
}
static void ObjToChecker(PhChecker& ch, ObjChecker obj, double x, double y){
    ch.coord.x = x;
    ch.coord.y = y;
    ch.speed.x = obj.vSpeed.x;
    ch.speed.y = obj.vSpeed.y;
    ch.weight = obj.weight;
    ch.rub = 0.13;//Rub::normal;
    ch.spring = Spring::normal;
}
void AlignBetween( double& x, double width, double min, double max){
    if( (x - width) <= min)
        x = width + min + 1;
    if( (x + width) >= max)
        x = max - width - 1;
}


CheckerManager::CheckerManager() : Model_Objects( STO_CHEKERS, sizeof(ObjChecker)){
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
void CheckerManager::EventsHandler(unsigned int mess, void *data){
    CObj obj, obj2;
    IDn ID, ID2;
    GameParam* gameparam;
    switch(mess){
    case ME_KEYDOWN:
        if(*((int*)data) == Qt::Key_Return){
            Root.PutEventToQueue( 0, SE_NEXTGAMEPART, STO_CHEKERS);
        }
        else if(*((int*)data) == Qt::Key_Escape){
            Root.CloseApp();
        }
        else if(*((int*)data) == Qt::Key_F1){
            Root.PutEventToQueue( 0, SE_REPLAY, STO_CHEKERS);
        }
        break;
    case ME_CREATE:
        break;
    case SE_STARTGAME:
        if(!data)
            return;
        gameparam = (GameParam*)data;
        Root.AddTimer(1);

        int *param;
        param = (int*)Root.PutEventToQueue(sizeof(int) * 2, SE_CREATEFIELD, STO_FIELD);
        if(param){
            *param = gameparam->FieldWidth;
            *(param + 1) = gameparam->FieldHeight;
        }
        game_part = Start;
        memcpy(&game_param, gameparam, sizeof(GameParam));
        break;
    case SE_FIELDPARAM:
        FieldRect = *((Rect*)data);
        FieldMiddle = (FieldRect.right - FieldRect.left) / 2;
        Root.PutEventToQueue( 0, SE_NEXTGAMEPART, STO_CHEKERS);
        break;
    case SE_INITSELECTOR:
        int yStep, xStep;
        int img1, img2, img3;
        switch(players_progress){
        case _1st:
            img1 = ID_BMP_BIG_CHEKER; img2 = ID_BMP_MID_CHEKER; img3 = ID_BMP_SMALL_CHEKER;
            xStep = FieldRect.left - Resources.Get_BMP(ID_BMP_BIG_CHEKER)->GetWidth();
            break;
        case _2nd:
            img1 = ID_BMP_BIG_CHEKER2; img2 = ID_BMP_MID_CHEKER2; img3 = ID_BMP_SMALL_CHEKER2;
            xStep = FieldRect.right + Resources.Get_BMP(ID_BMP_BIG_CHEKER2)->GetWidth();
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

        this->CreateSimpleObj(&obj);
        obj.LevelOfDraw = 2;
        obj.image = 0;

        ClearSelector();

        for(int i = 0 ; i < game_param.big_num; i ++){
            obj.BMP = img1;
            obj.SetRectByImage();
            obj.x = selector.pnt[0].x;
            obj.y = selector.pnt[0].y;
            ObjManager.CreateObj(obj, ID);
            ObjManager.GetObj(ID, obj);
            ((ObjChecker*)obj.GetSubStr())->master = players_progress;
            ((ObjChecker*)obj.GetSubStr())->weight = Weight::huge;
            ((ObjChecker*)obj.GetSubStr())->vSpeed.x =
                    ((ObjChecker*)obj.GetSubStr())->vSpeed.y = 0;
            ((ObjChecker*)obj.GetSubStr())->type = big;
            selector.big_chs.push_back(ID);
        }
        for(int i = 0 ; i < game_param.midle_num; i ++){
            obj.BMP = img2;
            obj.SetRectByImage();
            obj.x = selector.pnt[1].x;
            obj.y = selector.pnt[1].y;
            ObjManager.CreateObj(obj, ID);
            ObjManager.GetObj(ID, obj);
            ((ObjChecker*)obj.GetSubStr())->master = players_progress;
            ((ObjChecker*)obj.GetSubStr())->weight = Weight::normal;
            ((ObjChecker*)obj.GetSubStr())->vSpeed.x =
                    ((ObjChecker*)obj.GetSubStr())->vSpeed.y = 0;
            ((ObjChecker*)obj.GetSubStr())->type = middle;
            selector.middle_chs.push_back(ID);
        }
        for(int i = 0 ; i < game_param.small_num; i ++){
            obj.BMP = img3;
            obj.SetRectByImage();
            obj.x = selector.pnt[2].x;
            obj.y = selector.pnt[2].y;
            ObjManager.CreateObj(obj, ID);
            ObjManager.GetObj(ID, obj);
            ((ObjChecker*)obj.GetSubStr())->master = players_progress;
            ((ObjChecker*)obj.GetSubStr())->weight = Weight::low;
            ((ObjChecker*)obj.GetSubStr())->vSpeed.x =
                    ((ObjChecker*)obj.GetSubStr())->vSpeed.y = 0;
            ((ObjChecker*)obj.GetSubStr())->type = small;
            selector.small_chs.push_back(ID);
        }
        selector.busy[0] = false;
        selector.busy[1] = false;
        selector.busy[2] = false;

        LocateSelector();
        break;
    case SE_NEXTGAMEPART:
        if(game_part == Start){
            Root.PutEventToQueue( 0, SE_INITSELECTOR, STO_CHEKERS);
            game_part = Disposal;
            points_1st = points_2nd = 0;
            alive_che1_count = alive_che2_count = 0;
            players_progress = _1st;
            while(this->GetVolume())
                ObjManager.DeleteObj(this->GetObj(0));
        }
        else if(game_part == Disposal){
            if(players_progress == _1st){
                players_progress = _2nd;
                Root.PutEventToQueue( 0, SE_INITSELECTOR, STO_CHEKERS);
            }
            else if(players_progress == _2nd){
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
        game_part = Start;
        Root.PutEventToQueue(0, SE_NEXTGAMEPART, STO_CHEKERS);
        break;
    case ME_DRAW:
        if(*((int*)data) == 1){
            if(CheckEnable > 0){
                {
                CObj selector;
                ObjManager.GetObj(CheckChecker, obj2);
                switch(((ObjChecker*)obj2.GetSubStr())->type){
                case big:
                    selector.BMP = ID_BMP_SELECTOR_BIG;
                    break;
                case middle:
                    selector.BMP = ID_BMP_SELECTOR_MIDDLE;
                    break;
                case small:
                    selector.BMP = ID_BMP_SELECTOR_SMALL;
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
    case ME_MOUSECLICK:
        switch(game_part){
        case Disposal:
            Disposal_MouseClick();
            break;
        case Game:
            Game_MouseClick();
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
    case ME_HITEVENT:
    ID = *((IDn*)data);
    ID2 = *((IDn*)data + 1);
    if(!ObjManager.GetObj(ID, obj))
        break;
    if(!ObjManager.GetObj(ID2, obj2))
        break;
    if( obj.GetSubType() != GetSubType() || obj2.GetSubType() != GetSubType() )
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
void CheckerManager::CreateArrow( CObj& arrow, double x_c, double y_c, double x_l,
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
    if(selector.busy[0])
        ObjManager.DeleteObj(selector.checker[0]);
    if(selector.busy[1])
        ObjManager.DeleteObj(selector.checker[1]);
    if(selector.busy[2])
        ObjManager.DeleteObj(selector.checker[2]);

    for(int i = 0; i < (int)selector.big_chs.size(); i++)
        ObjManager.DeleteObj(selector.big_chs[i]);
    selector.big_chs.clear();

    for(int i = 0; i < (int)selector.middle_chs.size(); i++)
        ObjManager.DeleteObj(selector.middle_chs[i]);
    selector.middle_chs.clear();

    for(int i = 0; i < (int)selector.small_chs.size(); i++)
        ObjManager.DeleteObj(selector.small_chs[i]);
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
        ObjManager.DeleteFromGrid(id);
    }
}
void CheckerManager::LocateSelector(void){
    if(!selector.busy[0]){
        if(selector.big_chs.size()){
            selector.busy[0] = true;
            selector.checker[0] = selector.big_chs[selector.big_chs.size() - 1];
            selector.big_chs.pop_back();
            ObjManager.AddToGrid(selector.checker[0], false);
        }
    }
    if(!selector.busy[1]){
        if(selector.middle_chs.size()){
            selector.busy[1] = true;
            selector.checker[1] = selector.middle_chs[selector.middle_chs.size() - 1];
            selector.middle_chs.pop_back();
            ObjManager.AddToGrid(selector.checker[1], false);
        }
    }
    if(!selector.busy[2]){
        if(selector.small_chs.size()){
            selector.busy[2] = true;
            selector.checker[2] = selector.small_chs[selector.small_chs.size() - 1];
            selector.small_chs.pop_back();
            ObjManager.AddToGrid(selector.checker[2], false);
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
bool CheckerManager::RectOutField(Rect r){
    if((FieldRect.right < r.left) ||
            (FieldRect.left > r.right) ||
            (FieldRect.bottom < r.top) ||
            (FieldRect.top > r.bottom)  )
        return true;
    else
        return false;
}

void CheckerManager::Disposal_Timer(void *data){
    CObj obj;
    sMouse mouse;
    dCoord dcrd;
    if(*((int*)data) != 1)
        return;
    if(NeedFlyToPos){
        ObjManager.GetObj(CheckChecker,obj);
        ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
        ObjManager.DeleteFromGrid(CheckChecker);
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
        ObjManager.ChangeObj(CheckChecker, obj);
        ObjManager.AddToGrid(CheckChecker, false);
    }
    else if( CheckEnable > 0 ){
        ObjManager.GetObj(CheckChecker,obj);
        ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
        if( (objch->vSpeed.x == 0)  && (objch->vSpeed.y == 0) )
            return;
        ObjManager.DeleteFromGrid(CheckChecker);
        dcrd = objch->vSpeed;
        obj.x += dcrd.x;
        obj.y += dcrd.y;
        mouse = Root.GetMouseStatus();
        if(sqrt( pow( obj.x - mouse.x, 2.) + pow( obj.y - mouse.y, 2.) )
            <= sqrt( pow( dcrd.x, 2.) + pow(dcrd.y, 2.)) ){
            objch->vSpeed.x = objch->vSpeed.y = 0;
        }
        ObjManager.ChangeObj(CheckChecker, obj);
        ObjManager.AddToGrid(CheckChecker, true);
    }
}
void CheckerManager::Disposal_MouseClick(void){
    CObj obj;
    Coord pnt;
    vector<IDn>* vObj;
    Rect rect;
    sMouse mouse;
    mouse = Root.GetMouseStatus();
    if(NeedFlyToPos)
        return;
    if(mouse.L == S_DOWN){
        vObj = ObjManager.GetVObjByCrd(mouse.x, mouse.y);
        for( int i = 0; i < (int)vObj->size(); i ++){
            ObjManager.GetObj((*vObj)[i],obj);
            if(obj.GetSubType() != STO_CHEKERS)
                continue;
            if(((ObjChecker*)obj.GetSubStr())->master != players_progress)
                continue;
            pnt.x = mouse.x;
            pnt.y = mouse.y;
            if(obj.HitPoint(pnt)){
                CheckEnable = 1;
                CheckChecker = (*vObj)[i];
                ObjManager.GetObj(CheckChecker, obj);
                int type = ((ObjChecker*)obj.GetSubStr())->type;
                ((ObjChecker*)obj.GetSubStr())->vSpeed.x =
                        ((ObjChecker*)obj.GetSubStr())->vSpeed.y = 0;
                if((selector.busy[type] == true)
                        && ((*vObj)[i].ID == selector.checker[type].ID)
                        && ((*vObj)[i].DateBorn == selector.checker[type].DateBorn)){
                    selector.busy[type] = false;
                }
            }
        }
    }
    if(mouse.L == S_UP){
        if(CheckEnable > 0){
            ObjManager.GetObj(CheckChecker,obj);
            ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
            objch->vSpeed.x = 0;
            objch->vSpeed.y = 0;
            rect = obj.GetRect();
            if(RectInField(rect)){
                LocateSelector();
            }
            else{
                switch(((ObjChecker*)obj.GetSubStr())->type){
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
                ObjManager.GetObj(CheckChecker,obj);
                ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
                objch->vSpeed.x = (point_to.x - obj.x) / 10;
                objch->vSpeed.y = (point_to.y - obj.y) / 10;
                int type = ((ObjChecker*)obj.GetSubStr())->type;
                NeedFlyToPos = true;
                PrepareForReturn(type);
            }
        }
        CheckEnable = 0;
    }
}
void CheckerManager::Disposal_MouseMove(){
    CObj obj;
    sMouse mouse;
    if(CheckEnable > 0){
        if(game_part == Disposal){
            mouse = Root.GetMouseStatus();
            ObjManager.GetObj(CheckChecker,obj);
            ((ObjChecker*)obj.GetSubStr())->vSpeed.x = (mouse.x - obj.x) / 10;
            ((ObjChecker*)obj.GetSubStr())->vSpeed.y = (mouse.y - obj.y) / 10;
        }
    }
}
void CheckerManager::Disposal_HitChToCh(void *data){
    CObj obj, obj2;
    IDn ID = *((IDn*)data);
    IDn ID2 = *((IDn*)data + 1);
    ObjChecker* ch1, *ch2;
    ObjManager.GetObj(ID, obj);
    ObjManager.GetObj(ID2, obj2);
    ch1 = ((ObjChecker*)obj.GetSubStr());
    ch2 = ((ObjChecker*)obj2.GetSubStr());
    int t_length = Resources.Get_BMP(obj.BMP)->GetWidth() / 2 + Resources.Get_BMP(obj2.BMP)->GetWidth() / 2;
    int r_length = sqrt( pow( obj.x - obj2.x, 2.) + pow( obj.y - obj2.y, 2.) );
    double d = r_length - t_length;
    dCoord c1, c2;
    c1.x = obj.x; c1.y = obj.y;
    c2.x = obj2.x; c2.y = obj2.y;
    if((ID.ID == CheckChecker.ID) && (ID.DateBorn == CheckChecker.DateBorn)){
        dCoord v = vect_min(c2,c1);
        ch1->vSpeed = v;
        ObjManager.DeleteFromGrid(ID);
        ch1->vSpeed = vect_norm(ch1->vSpeed);
        ch1->vSpeed = vect_mult_d(ch1->vSpeed, d);
        obj.x += ch1->vSpeed.x;
        obj.y += ch1->vSpeed.y;
        ch1->vSpeed = vect_null();
        ObjManager.ChangeObj(ID, obj);
        ObjManager.AddToGrid(ID, true);
    }
    else if((ID2.ID == CheckChecker.ID) && (ID2.DateBorn == CheckChecker.DateBorn)){
        dCoord v = vect_min(c1,c2);
        ch2->vSpeed = v;
        ObjManager.DeleteFromGrid(ID2);
        ch2->vSpeed = vect_norm(ch2->vSpeed);
        ch2->vSpeed = vect_mult_d(ch2->vSpeed, d);
        obj2.x += ch2->vSpeed.x;
        obj2.y += ch2->vSpeed.y;
        ch2->vSpeed = vect_null();
        ObjManager.ChangeObj(ID2, obj);
        ObjManager.AddToGrid(ID2, true);
    }
}


///////////////////////////////////////////////////////////////////////////////


void CheckerManager::Game_Timer(void *data){
    CObj obj;
    if(*((int*)data) == 1){
        CurNumMoveCh = 0;
        for( int i = 0; i < (int)this->GetVolume(); i ++){
            ObjManager.GetObj(this->GetObj(i),obj);
            ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
            if( (objch->vSpeed.x == 0)  && (objch->vSpeed.y == 0) ){
                if(RectOutField(obj.GetRect())){
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
                    ObjManager.DeleteObj(this->GetObj(i));
                }
                continue;
            }
            CurNumMoveCh++;
            ObjManager.DeleteFromGrid(this->GetObj(i));
            PhChecker ch;
            ObjToChecker(ch, *objch, obj.x, obj.y);
            //++движение
            Move(ch, (double)(*((int*)data)));
            //--
            // ++столкновения со стенами
            /*PhWall wall;
            wall.spring = Spring::normal;
            if( ((obj.x - obj.GetWidth() / 2) < 0) || ( (obj.x + obj.GetWidth() / 2) > Root.GetScreenWidth()) ){
                AlignBetween(obj.x, obj.GetWidth()/2, 0, Root.GetScreenWidth());
                ObjToChecker(ch, *objch, obj.x, obj.y);
                wall.phi = State::vertical;
                Clash(ch, wall);
            }
            if( ((obj.y - obj.GetHeight() / 2) < 0) || ((obj.y + obj.GetHeight() / 2) > Root.GetScreenHeight()) ){
                AlignBetween(obj.y, obj.GetHeight() / 2, 0, Root.GetScreenHeight());
                ObjToChecker(ch, *objch, obj.x, obj.y);
                wall.phi = State::horizontal;
                Clash(ch, wall);
            }*/
            // --столкновения со стенами
            CheckerToObj(ch, *objch, obj.x, obj.y);
            ObjManager.ChangeObj(this->GetObj(i), obj);
            ObjManager.AddToGrid(this->GetObj(i), true);
        }
        if((!CurNumMoveCh) && ChangeProgressAfterStop){
            Root.PutEventToQueue( 0, SE_NEXTGAMEPART, STO_CHEKERS);
            ChangeProgressAfterStop = false;
        }
    }
}
void CheckerManager::Game_MouseClick(void){
    CObj obj;
    Coord pnt;
    vector<IDn>* vObj;
    sMouse mouse;
    mouse = Root.GetMouseStatus();
    if(CurNumMoveCh || (game_part == End))
        return;
    if(mouse.L == S_DOWN){
        vObj = ObjManager.GetVObjByCrd(mouse.x, mouse.y);
        for( int i = 0; i < (int)vObj->size(); i ++){
            ObjManager.GetObj((*vObj)[i],obj);
            if(obj.GetSubType() != STO_CHEKERS)
                continue;
            if(((ObjChecker*)obj.GetSubStr())->master != players_progress)
                continue;
            pnt.x = mouse.x;
            pnt.y = mouse.y;
            if(obj.HitPoint(pnt)){
                CheckEnable = 1;
                CheckChecker = (*vObj)[i];
                ObjManager.GetObj(CheckChecker, obj);
                ((ObjChecker*)obj.GetSubStr())->vSpeed.x =
                        ((ObjChecker*)obj.GetSubStr())->vSpeed.y = 0;
            }
        }
    }
    else if(mouse.L == S_UP){
        if(CheckEnable == 2){
            if(!arrows.size()){
                CheckEnable = 0;
                return;
            }
            mouse = Root.GetMouseStatus();
            ObjManager.GetObj(CheckChecker,obj);
            ObjChecker* obj_checker = ((ObjChecker*)obj.GetSubStr());
            double coef = ( arrows.size() );
            dCoord v1 = {(double)mouse.x, (double)mouse.y}, v2 = {obj.x, obj.y};
            v1 = vect_min(v1, v2);
            v1 = vect_norm(v1);
            v1 = vect_mult_d(v1, coef);
            obj_checker->vSpeed.x = v1.x;
            obj_checker->vSpeed.y = v1.y;
            ObjManager.ChangeObj(CheckChecker,obj);
            ChangeProgressAfterStop = true;
        }
        CheckEnable = 0;
    }
}
void CheckerManager::Game_MouseMove(){
    CObj obj;
    sMouse mouse;
    if(game_part == End)
            return;
    if(CheckEnable > 0){
        CObj arrow;
        arrow.BMP = ID_BMP_ARROW;
        arrow.image = 0;
        arrow.SetRectByImage();

        mouse = Root.GetMouseStatus();
        ObjManager.GetObj(CheckChecker,obj);
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
    CObj obj, obj2;
    IDn ID = *((IDn*)data);
    IDn ID2 = *((IDn*)data + 1);
    ObjManager.GetObj(ID, obj);
    ObjManager.GetObj(ID2, obj2);
    ObjManager.DeleteFromGrid(ID);
    dCoord v1,v2, v3;
    v1.x = obj.x; v1.y = obj.y;
    v2.x = obj2.x; v2.y = obj2.y;
    v3 = vect_min(v1, v2);
    v3 = vect_norm(v3);
    v3 = vect_mult_d(v3, Resources.Get_BMP(obj.BMP)->GetWidth() / 2 + Resources.Get_BMP(obj2.BMP)->GetWidth() / 2);
    v3 = vect_sum(v2, v3);
    obj.x = v3.x;
    obj.y = v3.y;
    ObjManager.ChangeObj(ID, obj);
    ObjManager.AddToGrid(ID, false);
    PhChecker ch1, ch2;
    ObjToChecker( ch1, *((ObjChecker*)obj.GetSubStr()), obj.x, obj.y );
    ObjToChecker( ch2, *((ObjChecker*)obj2.GetSubStr()), obj2.x, obj2.y );
    Clash(ch1, ch2);
    CheckerToObj( ch1, *((ObjChecker*)obj.GetSubStr()), obj.x, obj.y );
    CheckerToObj( ch2, *((ObjChecker*)obj2.GetSubStr()), obj2.x, obj2.y );
    ObjManager.ChangeObj(ID, obj);
    ObjManager.ChangeObj(ID2, obj2);
}

void CheckerManager::RecalcActualAliveCheCount(){
    CObj obj;
    alive_che1_count = alive_che2_count = 0;
    for( int i = 0; i < (int)this->GetVolume(); i++){
        if(ObjManager.GetObj(this->GetObj(i), obj)){
            switch(((ObjChecker*)obj.GetSubStr())->master){
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
