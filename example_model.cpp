#include "example_model.h"

cExample Example;

cExample::cExample() : Model_Objects(1,0){
    step.x = step.y= 0;
    CheckEnable = false;
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

        arrow.BMP = ID_BMP_ARROW;
        arrow.image = 0;
        arrow.SetRectByImage();
        break;
    case ME_DRAW:
        if(*((int*)data) != 1)
            return;
        if(CheckEnable){
            arrow.Draw();
        }
        break;
    case ME_TIMER:
        if(*((int*)data) == 1){
            ObjManager.GetObj(this->GetObj(0),obj);
            obj.x += step.x;
            obj.y += step.y;
            ObjManager.ChangeObj(this->GetObj(0), obj);
        }
        break;
    case ME_KEYDOWN:
        switch(*((int*)data)){
        case Qt::Key_Right:
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
            break;
        case Qt::Key_Escape:
            Root.CloseApp();
            break;
        }
        break;
    case ME_KEYUP:
        step.x = step.y = 0;
        break;
    case ME_MOUSECLICK:
        mouse = Root.GetMouseStatus();
        if(mouse.L == S_DOWN){
            ObjManager.GetObj(this->GetObj(0),obj);
            pnt.x = mouse.x;
            pnt.y = mouse.y;
            if(obj.HitPoint(pnt)){
                CheckEnable = true;
            }
        }
        if(mouse.L == S_UP){
            CheckEnable = false;
        }
        break;
    case ME_MOUSEMOVE:
        if(CheckEnable){
            mouse = Root.GetMouseStatus();
            ObjManager.GetObj(this->GetObj(0),obj);
            int xr, yr;
            double a, b, bs, as, cs, length, x0, y0;
            xr = mouse.x - obj.x;
            yr = mouse.y - obj.y;
            x0 = obj.x;
            y0 = obj.y;
            length = obj.GetWidth()/2 + arrow.GetHeight();
            if(sqrt( pow(xr, 2.) + pow(yr, 2.)) >=  ((double)obj.GetWidth())/2){
                if(fabs(obj.x - mouse.x) < 2.){
                    arrow.x = mouse.x;
                    if(obj.y > mouse.y)
                        arrow.y = obj.y - length;
                    else
                        arrow.y = obj.y + length;
                    return;
                }

                if(fabs(obj.y - mouse.y) < 2.){
                    arrow.y = mouse.y;
                    if(obj.x > mouse.x)
                        arrow.x = obj.x - length;
                    else
                        arrow.x = obj.x + length;
                    return;
                }

                a = (obj.y - (double)mouse.y) / (obj.x - (double)mouse.x);
                b = ((double)mouse.y) - a * ((double)mouse.x);

                bs = (2*x0 - 2*a*b + 2*a*y0);
                as = 1 + pow(a, 2.);
                cs = pow(x0, 2.) - pow(length, 2.) + pow(b, 2.) - 2*b*y0 + pow(y0, 2.);
                if( obj.x < (double)mouse.x )
                    arrow.x = ( bs + sqrt( pow(bs, 2.) - 4*as*cs) ) /
                                    ( 2*as);
                if( obj.x > (double)mouse.x )
                    arrow.x = ( bs - sqrt( pow(bs, 2.) - 4*as*cs) ) /
                                    ( 2*as);
                arrow.y = a*arrow.x + b;

                double ang = atan(a);
                if( mouse.x < obj.x){
                    arrow.TurnImage(M_PI/2. + ang);
                }
                else if(mouse.x > obj.x){
                    arrow.TurnImage(ang + (M_PI*3.)/2.);
                }
                else if( fabs(obj.x - mouse.x) < 2.){
                    if( mouse.y > obj.y)
                        arrow.SetDefaultAngle();
                    else
                        arrow.TurnImage(M_PI);
                }
            }
        }
        break;
    }
}
