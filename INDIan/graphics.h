#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "dependences.h"
#include "formuls.h"

class xBmp{
private:
    GLuint TextureID;
    GLuint MaskID;
    bool useMask;

    int Width, Height;
    int Volume, Columns, Lines;

    QImage image;

private:
    int nnx(int num);
    int nny(int num);
public:
    xBmp();
    bool Create(QString Image, QString Mask, int _Volume, int _Columns, int _Lines);
    int GetWidth();
    int GetHeight();
    int GetVolume();
    void Draw(int num, Coord x1, Coord x2, Coord x3, Coord x4);
    GLuint GetTextID();
    QImage GetImage(){ return image;}
};

bool HitImgImg(xBmp bmp1, QRect rect1, xBmp bmp2, QRect rect2);

#endif // GRAPHICS_H
