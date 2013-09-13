#include "MainWindow.h"
#include "Root.h"
#include "Graphics.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern int ScaleX;
extern int ScaleY;
extern QGLWidget* wndClass;
extern cResources Resources;


MainWindow::MainWindow(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
    glDepthFunc(GL_LEQUAL); // Буфер глубины

    QTimer *timRepaint = new QTimer(this);
    connect(timRepaint, SIGNAL(timeout()), this, SLOT(repaint()));
    timRepaint->start(20);

    QTimer *time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(mainTimer()));
    time->start(1);

    QRect rect= QApplication::desktop()->screenGeometry();
    int x1,y1;
    rect.getCoords( &x1, &y1, &WndWidth, &WndHeight);
    QWidget::showFullScreen();
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
}

void MainWindow::initializeGL(){
    ScaleX = ScreenWidth;
    ScaleY = ScreenHeight;
    glViewport(0, 0, ScreenWidth, ScreenHeight); //Adjust the viewport
    glMatrixMode(GL_PROJECTION); //Adjust the projection matrix
    glOrtho(-ScreenWidth/2, ScreenWidth/2, ScreenHeight/2, -ScreenHeight/2, -1, 1);
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
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glScalef((float)ScaleX, (float)ScaleY, 1);
    glTranslatef(0., 0., -1.);

    Root.Draw();

    glPopMatrix();
    swapBuffers();
}
void MainWindow::keyPressEvent(QKeyEvent *ke){
    Root.KeyDown(ke->key());
}
void MainWindow::keyRealeseEvent(QKeyEvent *ke){
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

