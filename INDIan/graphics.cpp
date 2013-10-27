#include "graphics.h"

QGLWidget* wndClass;

namespace INDIan{
    Tile::Tile(){
        textureID = 0;
        maskID = 0;
        useMask = false;
        width = height = volume = columns = lines = 0;
    }
    Tile::~Tile(){
        glDeleteTextures(1, &textureID);
        if(useMask)
            glDeleteTextures(1, &maskID);
    }
    bool Tile::Create(QString image, QString mask, int _volume, int _columns, int _lines){
        QImage* img = new QImage;
        if(img->load(QString(image))){
            width = img->width() / _columns;
            height = img->height() / _lines;
            delete img;
        }
        else{
            delete img;
            return false;
        }

        // создаём, связываем, загружаем, возвращаем уникальный номер:
        textureID = wndClass->bindTexture(QPixmap(QString(image)), GL_TEXTURE_2D);
        // далее параметры текстурного объекта
        // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // цвет текселя полностью замещает цвет фрагмента фигуры
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        if(mask.isEmpty()){
            useMask = false;
        }
        else{
            useMask = true;
            //и тоже самое для маски
            maskID = wndClass->bindTexture(QPixmap(QString(mask)), GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        }
        volume = _volume;
        columns = _columns;
        lines = _lines;

        return true;
    }

    int Tile::GetWidth(){ return width; }

    int Tile::GetHeight(){ return height; }

    int Tile::GetVolume(){ return volume; }

    void Tile::Draw(int num,  Coord x1, Coord x2, Coord x3, Coord x4){
        float stepx = 1./((float)columns);
        float stepy = 1./((float)lines);

        if(useMask){
        glBlendFunc(GL_DST_COLOR, GL_ZERO);

        glBindTexture(GL_TEXTURE_2D, maskID);
            glBegin(GL_QUADS);
                glTexCoord2f(stepx * nnx(num), stepy * nny(num));
                    glVertex2f(x4.x, x4.y);
                glTexCoord2f(stepx * (nnx(num) + 1), stepy * nny(num));
                    glVertex2f(x3.x, x3.y);
                glTexCoord2f(stepx * (nnx(num) + 1), stepy * (nny(num) + 1));
                    glVertex2f(x2.x, x2.y);
                glTexCoord2f(stepx * nnx(num), stepy * (nny(num) + 1));
                    glVertex2f(x1.x, x1.y);
            glEnd();
           glBlendFunc(GL_ONE, GL_ONE);
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
            glBegin(GL_QUADS);
                glTexCoord2f(stepx * nnx(num), stepy * nny(num));
                    glVertex2f(x4.x, x4.y);
                glTexCoord2f(stepx * (nnx(num)+1), stepy * nny(num));
                    glVertex2f(x3.x, x3.y);
                glTexCoord2f(stepx * (nnx(num)+1), stepy * (nny(num) + 1));
                    glVertex2f(x2.x, x2.y);
                glTexCoord2f(stepx * nnx(num), stepy * (nny(num) + 1));
                    glVertex2f(x1.x, x1.y);
            glEnd();
    }

    GLuint Tile::GetTextID(){
        return textureID;
    }

    int Tile::nnx(int num){ return num - lines * (num / columns); }
    int Tile::nny(int num){ return (num / columns); }

    bool HitImgImg(Tile bmp1, QRect rect1, Tile bmp2, QRect rect2){
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
}
