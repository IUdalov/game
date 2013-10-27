#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "dependences.h"
#include "formuls.h"

namespace INDIan{
    class Tile{
    private:
        GLuint textureID;
        GLuint maskID;
        bool useMask;

        int width, height;
        int volume, columns, lines;

        QImage image;

    private:
        int nnx(int num);
        int nny(int num);
    public:
        Tile();
        ~Tile();
        bool Create(QString image, QString mask, int _volume, int _columns, int _lines);
        int GetWidth();
        int GetHeight();
        int GetVolume();
        void Draw(int num, Coord x1, Coord x2, Coord x3, Coord x4);
        GLuint GetTextID();
        QImage GetImage(){ return image;}
    };

    bool HitImgImg(Tile bmp1, QRect rect1, Tile bmp2, QRect rect2);
}

#endif // GRAPHICS_H
