#ifndef MainWindow_H
#define MainWindow_H

#include "transport.h"
#include "dependences.h"
#include "formuls.h"

//void ReportSender(QtMsgType type, const QMessageLogContext& log, const QString& msg);
namespace INDIan{
    class GLWindow : public QGLWidget{
        Q_OBJECT

        static int screenWidth;
        static int screenHeight;
        static double wndScaleX;
        static double wndScaleY;
    public:
        GLWindow(QWidget *parent = NULL);
        ~GLWindow();
        static int GetScreenWidth(void);
        static int GetScreenHeight(void);
        static double GetWndScaleX(void);
        static double GetWndScaleY(void);

        void Run(void);
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
        void MainTimer();
        void Repaint();
    };
}
#endif // MainWindow_H
