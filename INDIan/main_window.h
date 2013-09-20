#ifndef MainWindow_H
#define MainWindow_H

#include "dependences.h"
#include "root.h"
#include "models.h"
#include "graphics.h"
#include "obj_manager.h"

void ReportSender(QtMsgType type, const QMessageLogContext& log, const QString& msg);

class MainWindow : public QGLWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void keyPressEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре
    void keyReleaseEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре
    void mouseMoveEvent(QMouseEvent *me); // Метод реагирует на перемещение указателя, но по умолчанию setMouseTracking(false)
    void mousePressEvent(QMouseEvent *me); // Реагирует на нажатие кнопок мыши
    void mouseReleaseEvent(QMouseEvent *me); // Метод реагирует на "отжатие" кнопки мыши
protected slots:
    void mainTimer();
    void repaint();
};

#endif // MainWindow_H
