#include "example_model.h"

cExample Example;

#define SpeedVal 10

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
    ch.rub = 0.6;//Rub::normal;
    ch.spring = Spring::normal;
}
void AlignBetween( double& x, double width, double min, double max){
    if( (x - width) <= min)
        x = width + min + 1;
    if( (x + width) >= max)
        x = max - width - 1;
}


cExample::cExample() : Model_Objects( STO_CHEKERS, sizeof(ObjChecker)){
    CheckEnable = 0;
}
cExample::~cExample(){

}
void cExample::EventsHandler(unsigned int mess, void *data){
    CObj obj, obj2;
    IDn ID, ID2;
    sMouse mouse;
    Coord pnt;
    switch(mess){
    case ME_CREATE:
        Root.AddTimer(1);
        ObjManager.ReBuildGrid(Root.GetScreenWidth() / 50 + 1, Root.GetScreenHeight() / 50 + 1, 50, 50, 0);
        Root.NumLevelDraw = 2;
        this->CreateSimpleObj(&obj);
        obj.x = 200;
        obj.y = 200;
        obj.BMP = ID_BMP_BACKGROUND;
        obj.image = 0;
        obj.SetRectByImage();
        ObjManager.CreateObj(obj, ID);
        ObjManager.AddToGrid(ID, false);
        ObjManager.GetObj(ID, obj);
        ((ObjChecker*)obj.GetSubStr())->weight = Weight::huge;
        ((ObjChecker*)obj.GetSubStr())->vSpeed.x =
                ((ObjChecker*)obj.GetSubStr())->vSpeed.y = 0;

        this->CreateSimpleObj(&obj2);
        obj2.x = 500;
        obj2.y = 200;
        obj2.BMP = ID_BMP_BACKGROUND;
        obj2.image = 0;
        obj2.SetRectByImage();
        ObjManager.CreateObj(obj2, ID);
        ObjManager.AddToGrid(ID, false);
        ObjManager.GetObj(ID, obj2);
        ((ObjChecker*)obj2.GetSubStr())->weight = Weight::low;
        ((ObjChecker*)obj2.GetSubStr())->vSpeed.x =
                ((ObjChecker*)obj2.GetSubStr())->vSpeed.y = 0;
        break;
    case ME_DRAW:
        if(*((int*)data) != 1)
            return;
        if(CheckEnable == 2){
            for( int i = 0; i < (int)arrows.size(); i++)
                arrows[i].Draw();
        }
        break;
    case ME_TIMER:
        if(*((int*)data) == 1){
            for( int i = 0; i < (int)this->GetVolume(); i ++){
                ObjManager.GetObj(this->GetObj(i),obj);
                ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
                if( (objch->vSpeed.x == 0)  && (objch->vSpeed.y == 0) )
                    continue;
                ObjManager.DeleteFromGrid(this->GetObj(i));
                PhChecker ch;
                PhWall wall;
                ObjToChecker(ch, *objch, obj.x, obj.y);
                //++движение
                Move(ch, *((int*)data));
                //--
                // ++столкновения со стенами
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
                }
                // --столкновения со стенами
                CheckerToObj(ch, *objch, obj.x, obj.y);
                ObjManager.ChangeObj(this->GetObj(i), obj);
                ObjManager.AddToGrid(this->GetObj(i), true);
             }
         }
     break;
    case ME_KEYDOWN:
        switch(*((int*)data)){
/*        case Qt::Key_Right:
            step.x = 5;
            break;
        case Qt::Key_Left:
            step.x = -5;
            break;
        case Qt::Key_Up:
            step.y = -5;
            break;
        case Qt::Key_Down:
            step.y = 5;
            break;*/
        case Qt::Key_Escape:
            Root.CloseApp();
            break;
        }
        break;
    case ME_KEYUP:
 //       step.x = step.y = 0;
        break;
    case ME_MOUSECLICK:
        mouse = Root.GetMouseStatus();
        if(mouse.L == S_DOWN){
            for( int i = 0; i < (int)this->GetVolume(); i ++){
                ObjManager.GetObj(this->GetObj(i),obj);
                pnt.x = mouse.x;
                pnt.y = mouse.y;
                if(obj.HitPoint(pnt)){
                    CheckEnable = 1;
                    CheckChecker = this->GetObj(i);
                    break;
                }
            }
        }
        if(mouse.L == S_UP){
            if(CheckEnable == 2){
                mouse = Root.GetMouseStatus();
                ObjManager.GetObj(CheckChecker,obj);
                double xr, yr;
                xr = mouse.x - obj.x;
                yr = mouse.y - obj.y;
                ((ObjChecker*)obj.GetSubStr())->vSpeed.x = xr / SpeedVal;
                ((ObjChecker*)obj.GetSubStr())->vSpeed.y = yr / SpeedVal;
                ObjManager.ChangeObj(CheckChecker,obj);
            }
            CheckEnable = 0;
        }
        break;
    case ME_MOUSEMOVE:
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
                CreateArrow( arrow, obj.x, obj.y, mouse.x, mouse.y, obj.GetWidth()/2);
            }
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
        PhChecker ch1, ch2;
        ObjToChecker( ch1, *((ObjChecker*)obj.GetSubStr()), obj.x, obj.y );
        ObjToChecker( ch2, *((ObjChecker*)obj2.GetSubStr()), obj2.x, obj2.y );
        Clash(ch1, ch2);
        CheckerToObj( ch1, *((ObjChecker*)obj.GetSubStr()), obj.x, obj.y );
        CheckerToObj( ch2, *((ObjChecker*)obj2.GetSubStr()), obj2.x, obj2.y );
        ObjManager.ChangeObj(ID, obj);
        ObjManager.ChangeObj(ID2, obj2);
    }
    break;
    }
}
void cExample::CreateArrow( CObj& arrow, double x_c, double y_c, double x_l,
                             double y_l, double length ){

    double a, b, bs, as, cs;
    double step = (double)arrow.GetHeight();
    int num = ( sqrt( pow( x_l - x_c, 2.)  + pow( y_l - y_c, 2.)) - length) / step;
    arrows.clear();

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

