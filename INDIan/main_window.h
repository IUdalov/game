#ifndef MainWindow_H
#define MainWindow_H


#include "dependences.h"
#include "root.h"
#include "graphics.h"


class MainWindow : public QGLWidget
{
    Q_OBJECT
    int WndWidth;
    int WndHeight;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void keyPressEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре
    void keyRealeseEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре
    void mouseMoveEvent(QMouseEvent *me); // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    void mousePressEvent(QMouseEvent *me); // Реагирует на нажатие кнопок мыши
    void mouseReleaseEvent(QMouseEvent *me); // Метод реагирует на "отжатие" кнопки мыши
protected slots:
    void mainTimer();
    void repaint();
};

#endif // MainWindow_H
