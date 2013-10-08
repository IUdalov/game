#include "main_window.h"
//#include "root.h"
//#include "graphics.h"

#define ScreenResolutionX 1024
#define ScreenResolutionY 768

extern System_ROOT Root;
extern QGLWidget* wndClass;
extern cResources Resources;

void ReportSender(QtMsgType type, const QMessageLogContext& log, const QString& msg){
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
 }

MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    wndClass = this;

    glDepthFunc(GL_LEQUAL); // Буфер глубины

    QTimer *timRepaint = new QTimer(this);
    connect(timRepaint, SIGNAL(timeout()), this, SLOT(repaint()));
    timRepaint->start(10);

    QTimer *time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(mainTimer()));
    time->start(1);

    QRect rect = QApplication::desktop()->screenGeometry();
    int x1,y1, x2, y2;
    rect.getCoords( &x1, &y1, &x2, &y2);
    if(x2 < y2){
        Root.ScreenWidth = ScreenResolutionX;
        double coef = x2 / ScreenResolutionX;
        Root.ScreenHeight = ScreenResolutionY;
        Root.ScreenHeight += (y2 - ScreenResolutionY * coef);
    }
    else{
        Root.ScreenHeight = ScreenResolutionY;
        double coef = (double)y2 / (double)ScreenResolutionY;
        Root.ScreenWidth = ScreenResolutionX;
        Root.ScreenWidth += (x2 - ScreenResolutionX * coef) + 1;
    }
    Root.WndScaleX = (double)Root.ScreenWidth / (double)x2;
    Root.WndScaleY = (double)Root.ScreenHeight / (double)y2;
    QWidget::showFullScreen();

    setMouseTracking(true);
}

MainWindow::~MainWindow(){
    int size = 0;

    for(int i = 0; i < Resources.GetBmpCount(); i++)
        if(Resources.Get_BMP(i))
            size++;

    if(!size)
       return;

    GLuint ids[size];
    int n = 0;

    for(int i = 0; i < Resources.GetBmpCount(); i++)
        if(Resources.Get_BMP(i)){
            ids[n] = Resources.Get_BMP(i)->GetTextID();
            n++;
        }

    Root.Destroy();
    glDeleteTextures(size, ids); // удаляем текстурные объекты
    wndClass = NULL;
}

void MainWindow::initializeGL(){
    this->doubleBuffer();
    glViewport(0, 0, Root.ScreenWidth, Root.ScreenHeight); //Adjust the viewport
    glMatrixMode(GL_PROJECTION); //Adjust the projection matrix
    glOrtho(0, Root.ScreenWidth, Root.ScreenHeight, 0, 0, 1);
    glLoadIdentity();
    qglClearColor(Qt::black);
    //настройки для текстур
    Root.Create();
    glEnable(GL_TEXTURE_2D); // установить режим двумерных текстур
    //getTextureArray(); // определить массив текстурных координат вершин
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void MainWindow::resizeGL(int nWidth, int nHeight){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}
void MainWindow::paintGL(){
    glClearColor(0., 0., 0., 0.);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glOrtho(0, Root.ScreenWidth, Root.ScreenHeight, 0, 0, 1);
    glEnable(GL_BLEND);       // Разрешение смешивания
    glDisable(GL_DEPTH_TEST); // Запрет теста глубины
//    glTranslatef(0,0,-1);//(float)ScaleX/2., (float)ScaleY/2., -1.);

    Root.Draw();

    glEnable(GL_DEPTH_TEST); // Разрешение теста глубины
    glDisable(GL_BLEND);     // Запрещение смешивания
    glPopMatrix();
//    swapBuffers();
}
void MainWindow::keyPressEvent(QKeyEvent *ke){
    Root.KeyDown(ke->key());
}
void MainWindow::keyReleaseEvent(QKeyEvent *ke){
    Root.KeyUp(ke->key());
}
void MainWindow::mouseMoveEvent(QMouseEvent *me){
    Root.MouseMove(me->globalX(), me->globalY());
}
void MainWindow::mousePressEvent(QMouseEvent *me){
    Root.MouseDown(me->button());
}
void MainWindow::mouseReleaseEvent(QMouseEvent *me){
    Root.MouseUp(me->button());
}

void MainWindow::repaint(){
    updateGL();
}
void MainWindow::mainTimer(){
    Root.Timer();
}

