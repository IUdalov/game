#include "example_model.h"

cExample Example;

#define SpeedVal 10
#define TimeSpeedReCalc 20

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
    ch.rub = 1.;//Rub::normal;
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
    CObj obj;
    IDn ID;
    sMouse mouse;
    Coord pnt;
    switch(mess){
    case ME_CREATE:
        Root.AddTimer(1);
        Root.AddTimer(TimeSpeedReCalc);
        ObjManager.ReBuildGrid(10, 10, 50, 50, 0);
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
            ObjManager.GetObj(this->GetObj(0),obj);
            ObjChecker* objch = (ObjChecker*)obj.GetSubStr();
            if( (objch->vSpeed.x == 0)  && (objch->vSpeed.y == 0) )
                return;
            PhChecker ch;
            PhWall wall;
            ObjToChecker(ch, *objch, obj.x, obj.y);
            //++движение
            Move(ch, *((int*)data));
            //--
            // ++столкновения со стенами
            wall.spring = Spring::normal;
            if( ((obj.x - obj.GetWidth() / 2) < 0) || ( (obj.x + obj.GetWidth() / 2) > ScreenWidth) ){
                AlignBetween(obj.x, obj.GetWidth()/2, 0, ScreenWidth);
                ObjToChecker(ch, *objch, obj.x, obj.y);
                wall.phi = State::vertical;
                Clash(ch, wall);
            }
            if( ((obj.y - obj.GetHeight() / 2) < 0) || ((obj.y + obj.GetHeight() / 2) > ScreenHeight) ){
                AlignBetween(obj.y, obj.GetHeight() / 2, 0, ScreenHeight);
                ObjToChecker(ch, *objch, obj.x, obj.y);
                wall.phi = State::horizontal;
                Clash(ch, wall);
            }
            // --столкновения со стенами
            CheckerToObj(ch, *objch, obj.x, obj.y);
            ObjManager.ChangeObj(this->GetObj(0), obj);
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
            ObjManager.GetObj(this->GetObj(0),obj);
            pnt.x = mouse.x;
            pnt.y = mouse.y;
            if(obj.HitPoint(pnt)){
                CheckEnable = 1;
            }
        }
        if(mouse.L == S_UP){
            if(CheckEnable == 2){
                mouse = Root.GetMouseStatus();
                ObjManager.GetObj(this->GetObj(0),obj);
                double xr, yr;
                xr = mouse.x - obj.x;
                yr = mouse.y - obj.y;
                ((ObjChecker*)obj.GetSubStr())->vSpeed.x = xr / SpeedVal;
                ((ObjChecker*)obj.GetSubStr())->vSpeed.y = yr / SpeedVal;
                ObjManager.ChangeObj(this->GetObj(0),obj);
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
            ObjManager.GetObj(this->GetObj(0),obj);
            int xr, yr;
            xr = mouse.x - obj.x;
            yr = mouse.y - obj.y;
            if(sqrt( pow(xr, 2.) + pow(yr, 2.)) >=  ((double)obj.GetWidth())/2){
                CheckEnable = 2;
                CreateArrow( arrow, obj.x, obj.y, mouse.x, mouse.y, obj.GetWidth()/2);
//                arrows.push_back(arrow);
            }
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

