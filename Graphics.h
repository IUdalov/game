#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "core_includes.h"

class xBmp{
private:
    GLuint TextureID;
    GLuint MaskID;
    bool useMask;

    int Width, Height;
    int Volume, Columns, Lines;

private:
    int nnx(int num);
    int nny(int num);
public:
    xBmp();
    bool Create(QString Image, QString Mask, int _Volume, int _Columns, int _Lines);
    int GetWidth();
    int GetHeight();
    int GetVolume();
    void Draw(int num, int x, int y);
    GLuint GetTextID();
};

#endif // GRAPHICS_H
