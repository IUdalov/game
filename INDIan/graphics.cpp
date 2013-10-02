#include "graphics.h"

//int ScreenWidth = 0;
//int ScreenHeight = 0;

//int ScaleX = 0;
//int ScaleY = 0;

QGLWidget* wndClass;

xBmp::xBmp(){
    TextureID = 0;
    MaskID = 0;
    useMask = false;
    Width = Height = Volume = Columns = Lines = 0;
}
bool xBmp::Create(QString Image, QString Mask, int _Volume, int _Columns, int _Lines){
    QImage* img = new QImage;
    if(img->load(QString(Image))){
        Width = img->width() / _Columns;
        Height = img->height() / _Lines;
        delete img;
    }
    else{
        delete img;
        return false;
    }

    // создаём, связываем, загружаем, возвращаем уникальный номер:
    TextureID = wndClass->bindTexture(QPixmap(QString(Image)), GL_TEXTURE_2D);
    // далее параметры текстурного объекта
    // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // цвет текселя полностью замещает цвет фрагмента фигуры
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    if(Mask.isEmpty()){
        useMask = false;
    }
    else{
        useMask = true;
        //и тоже самое для маски
        MaskID = wndClass->bindTexture(QPixmap(QString(Mask)), GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }
    Volume = _Volume;
    Columns = _Columns;
    Lines = _Lines;

    return true;
}

int xBmp::GetWidth(){ return Width; }

int xBmp::GetHeight(){ return Height; }

int xBmp::GetVolume(){ return Volume; }

void xBmp::Draw(int num,  Coord x1, Coord x2, Coord x3, Coord x4){
    float stepx = 1./Columns;
    float stepy = 1./Lines;

    if(useMask){
    glBlendFunc(GL_DST_COLOR, GL_ZERO);

    glBindTexture(GL_TEXTURE_2D, MaskID);
        glBegin(GL_QUADS);
            glTexCoord2f(stepx*nnx(num), stepy*nny(num));
                glVertex2f(x4.x, x4.y);
            glTexCoord2f(stepx*(nnx(num) + 1), stepy*nny(num));
                glVertex2f(x3.x, x3.y);
            glTexCoord2f(stepx*(nnx(num) + 1), stepy*(nny(num) + 1));
                glVertex2f(x2.x, x2.y);
            glTexCoord2f(stepx*nnx(num), stepy*(nny(num) + 1));
                glVertex2f(x1.x, x1.y);
        glEnd();
       glBlendFunc(GL_ONE, GL_ONE);
    }
    glBindTexture(GL_TEXTURE_2D, TextureID);
        glBegin(GL_QUADS);
            glTexCoord2f(stepx*nnx(num), stepy*nny(num));
                glVertex2f(x4.x, x4.y);
            glTexCoord2f(stepx*(nnx(num)+1), stepy*nny(num));
                glVertex2f(x3.x, x3.y);
            glTexCoord2f(stepx*(nnx(num)+1), stepy*(nny(num) + 1));
                glVertex2f(x2.x, x2.y);
            glTexCoord2f(stepx*nnx(num), stepy*(nny(num) + 1));
                glVertex2f(x1.x, x1.y);
        glEnd();
}

GLuint xBmp::GetTextID(){
    return TextureID;
}

int xBmp::nnx(int num){ return num - (num / Columns); }
int xBmp::nny(int num){ return (num / Columns); }

bool HitImgImg(xBmp bmp1, QRect rect1, xBmp bmp2, QRect rect2){
    if(!HitRectRect(rect1, rect2))
        return false;

    int left = MAX(rect1.left(), rect2.left());
    int right = MIN(rect1.right(), rect2.right());
    int top = MAX(rect1.top(), rect2.top());
    int bottom = MIN(rect1.bottom(), rect2.bottom());

    for( int x = left; x <= right; x++){
        for( int y = top; y <= bottom; y++){
            if(bmp1.GetImage().pixel(x,y) && bmp2.GetImage().pixel(x,y))
                return true;
        }
    }
    return false;
}
