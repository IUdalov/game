#include "core_includes.h"

#define ScreenResolutionX 1024
#define ScreenResolutionY 768

extern QGLWidget* wndClass;

namespace INDIan{
    int GLWindow::screenWidth = 0;
    int GLWindow::screenHeight = 0;
    double GLWindow::wndScaleX = 0.;
    double GLWindow::wndScaleY = 0.;

    GLWindow::GLWindow(QWidget *parent)
        : QGLWidget(parent)
    {
        wndClass = this;

        glDepthFunc(GL_LEQUAL); // Буфер глубины

        QTimer *timRepaint = new QTimer(this);
        connect(timRepaint, SIGNAL(timeout()), this, SLOT(repaint()));
        timRepaint->start(25);

        QTimer *time = new QTimer(this);
        connect(time, SIGNAL(timeout()), this, SLOT(MainTimer()));
        time->start(10);

        QRect rect = QApplication::desktop()->screenGeometry();
        int x1,y1, x2, y2;
        rect.getCoords( &x1, &y1, &x2, &y2);
        if(x2 < y2){
            screenWidth = ScreenResolutionX;
            double coef = x2 / ScreenResolutionX;
            screenHeight = int((double)y2 / coef);
            //screenHeight = ScreenResolutionY;
            //screenHeight += (y2 - ScreenResolutionY * coef);
        }
        else{
            screenHeight = ScreenResolutionY;
            double coef = (double)y2 / (double)ScreenResolutionY;
            screenWidth = int((double)x2 / coef);
            //screenWidth = ScreenResolutionX;
            //screenWidth += (x2 - ScreenResolutionX * coef) + 1;
        }
        wndScaleX = (double)screenWidth / (double)x2;
        wndScaleY = (double)screenHeight / (double)y2;
        QWidget::showFullScreen();

        setMouseTracking(true);

        Root::Create();
    }

    GLWindow::~GLWindow(){
        Root::Destroy();
        wndClass = NULL;
    }

    void GLWindow::initializeGL(){
        this->doubleBuffer();
        glViewport(0, 0, screenWidth, screenHeight); //Adjust the viewport
        glMatrixMode(GL_PROJECTION); //Adjust the projection matrix
        glOrtho(0, screenWidth, screenHeight, 0, 0, 1);
        glLoadIdentity();
        qglClearColor(Qt::black);
        //настройки для текстур
        glEnable(GL_TEXTURE_2D); // установить режим двумерных текстур
        //getTextureArray(); // определить массив текстурных координат вершин
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    void GLWindow::resizeGL(int nWidth, int nHeight){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    }
    void GLWindow::paintGL(){
        glClearColor(0., 0., 0., 0.);
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glOrtho(0, screenWidth, screenHeight, 0, 0, 1);
        glEnable(GL_BLEND);       // Разрешение смешивания
        glDisable(GL_DEPTH_TEST); // Запрет теста глубины
    //    glTranslatef(0,0,-1);//(float)ScaleX/2., (float)ScaleY/2., -1.);

        Root::Draw();

        glEnable(GL_DEPTH_TEST); // Разрешение теста глубины
        glDisable(GL_BLEND);     // Запрещение смешивания
        glPopMatrix();
    //    swapBuffers();
    }
    void GLWindow::keyPressEvent(QKeyEvent *ke){
        Root::KeyDown(ke->key());
    }
    void GLWindow::keyReleaseEvent(QKeyEvent *ke){
        Root::KeyUp(ke->key());
    }
    void GLWindow::mouseMoveEvent(QMouseEvent *me){
        int x = (int)((double)me->globalX() * wndScaleX);
        int y = (int)((double)me->globalY() * wndScaleY);

        Root::MouseMove(x, y);
    }
    void GLWindow::mousePressEvent(QMouseEvent *me){
        Root::MouseDown(me->button());
    }
    void GLWindow::mouseReleaseEvent(QMouseEvent *me){
        Root::MouseUp(me->button());
    }

    void GLWindow::Repaint(){
        updateGL();
    }
    void GLWindow::MainTimer(){
        Root::Timer();
    }
    void GLWindow::Run(){
        this->show();
    }
    int GLWindow::GetScreenWidth(void){
        return screenWidth;
    }
    int GLWindow::GetScreenHeight(void){
        return screenHeight;
    }
    double GLWindow::GetWndScaleX(void){
        return wndScaleX;
    }
    double GLWindow::GetWndScaleY(void){
        return wndScaleY;
    }
}

/*void ReportSender(QtMsgType type, const QMessageLogContext& log, const QString& msg){
    FILE *file; // указатель на файл, в который пишем
    file = fopen("report.txt", "a"); // открываем файл на запись
     switch (type) {
     case QtDebugMsg:
         fprintf(file, QString("Debug: %s\n").toStdString().c_str(), msg.toStdString().c_str());
         break;
     case QtWarningMsg:
         fprintf(file, QString("Warning: %s\n").toStdString().c_str(), msg.toStdString().c_str());
         break;
     case QtCriticalMsg:
         fprintf(file, QString("Critical: %s\n").toStdString().c_str(), msg.toStdString().c_str());
         break;
     case QtFatalMsg:
         fprintf(file,  QString("Fatal: %s\n").toStdString().c_str(), msg.toStdString().c_str());
         abort();
     }
    fclose(file); // закрываем файл
 }*/

