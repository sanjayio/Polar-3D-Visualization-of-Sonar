#include "glwidget.h"
#include <QWidget>
#include <QtGui/qevent.h>
#include <QtOpenGL>
#include <iostream>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <QTime>
#include <QTimer>
#include <time.h>

using namespace std;

static int rad = 0;
static float gr = 2.0;

struct float3d {
    GLfloat x, y, z;
};

struct GLintPoint {
    GLint x, y;
};

GLintPoint point[1];
bool selected = false;
int screenw = 640, screenh = 480;
static int position = 9;

float array[360]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0.1, 0.2, 0.5, 1, 0.5, 0.2, 0.1, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(0);
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(1280, 720);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}



void GLWidget::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    //glEnable(GL_LIGHT3);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
    //cout<<float(rand())*0.000000001<<endl;
    //glutMouseFunc(clickfeed);
}

void GLWidget::resizeGL(int width, int height)
{
    //int side = qMin(width, height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::displaylatest() {
    for(int i = 0; i < 10; i ++) {
     //   cout<<array[position][i];
    }
    cout<<endl;
    updateGL();
    if(position == 0)
        position = 0;
    else
        position--;
}

void GLWidget::displayolder() {
    for(int i = 0; i < 10; i ++) {
       // cout<<array[position][i];
    }
    cout<<endl;
    updateGL();
    if(position == 9)
        position = 9;
    else
        position++;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    bool x = event->button() == Qt::LeftButton;
    bool y = event->button() == Qt::RightButton;
    if(x) {displaylatest();}
    if(y) {displayolder();}
}



void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);

    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}


void GLWidget::DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_QUADS);
    glLineWidth(4.0);
    for(int ii = 0; ii < 360; ii++)
    {
        if((array[ii] >= 1) || (array[ii+1] >= 1)) {
            glColor3f(1, 0, 0);
        }
        else if((array[ii] >= 0.5) && (array[ii] < 1) || (array[ii+1] >= 0.5) && (array[ii+1] < 1)) {
            glColor3f(0.5, 0, 0.5);
        }
        else if((array[ii] > 0.1) && (array[ii] <= 0.2) || (array[ii+1] > 0.1) && (array[ii+1] <= 0.2)) {
            glColor3f(0, 0.5, 0);
        }
        else {
            glColor3f(0, 1, 0);
        }
        float theta1 = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x1 = r * cosf(theta1);//calculate the x component
        float y1 = r * sinf(theta1);//calculate the y component
        float theta2 = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x2 = (r-0.1) * cosf(theta2);//calculate the x component
        float y2 = (r-0.1) * sinf(theta2);//calculate the y component
        float theta3 = 2.0f * 3.1415926f * float(ii+1) / float(num_segments);//get the current angle
        float x3 = r * cosf(theta3);//calculate the x component
        float y3 = r * sinf(theta3);//calculate the y component
        float theta4 = 2.0f * 3.1415926f * float(ii+1) / float(num_segments);//get the current angle
        float x4 = (r-0.1) * cosf(theta4);//calculate the x component
        float y4 = (r-0.1) * sinf(theta4);//calculate the y component
        //glVertex3f(x1 + cx, y1 + cy, 0);//output vertex
        glVertex3f(x1 + cx, y1 + cy, array[ii]+0.1);//output vertex
        glVertex3f(x2 + cx, y2 + cy, array[ii]+0.1);//output vertex
        //glVertex3f(x2 + cx, y2 + cy, 0);//output vertex
        //glVertex3f(x2 + cx, y2 + cy, array[ii]+0.1);//output vertex
        glVertex3f(x4 + cx, y4 + cy, array[ii+1]+0.1);//output vertex
        //glVertex3f(x3 + cx, y3 + cy, 0);//output vertex
        //glVertex3f(x4 + cx, y4 + cy, array[ii+1]+0.1);//output vertex
        glVertex3f(x3 + cx, y3 + cy, array[ii+1]+0.1);//output vertex
        //glVertex3f(x4 + cx, y4 + cy, 0);//output vertex
        //glVertex3f(x3 + cx, y3 + cy, array[ii+1]+0.1);//output vertex
        //glVertex3f(x1 + cx, y1 + cy, array[ii]+0.1);//output vertex


    }
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4.0);
    glColor3f(0, 0, 0);
    for(int ii = 0; ii < 360; ii++)
    {
        float theta1 = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x1 = r * cosf(theta1);//calculate the x component
        float y1 = r * sinf(theta1);//calculate the y component
        float theta2 = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x2 = (r-0.1) * cosf(theta2);//calculate the x component
        float y2 = (r-0.1) * sinf(theta2);//calculate the y component
        float theta3 = 2.0f * 3.1415926f * float(ii+1) / float(num_segments);//get the current angle
        float x3 = r * cosf(theta3);//calculate the x component
        float y3 = r * sinf(theta3);//calculate the y component
        float theta4 = 2.0f * 3.1415926f * float(ii+1) / float(num_segments);//get the current angle
        float x4 = (r-0.1) * cosf(theta4);//calculate the x component
        float y4 = (r-0.1) * sinf(theta4);//calculate the y component
        //glVertex3f(x1 + cx, y1 + cy, 0);//output vertex
        glVertex3f(x1 + cx, y1 + cy, array[ii]+0.1);//output vertex
        glVertex3f(x2 + cx, y2 + cy, array[ii]+0.1);//output vertex
        //glVertex3f(x2 + cx, y2 + cy, 0);//output vertex
        glVertex3f(x2 + cx, y2 + cy, array[ii]+0.1);//output vertex
        glVertex3f(x4 + cx, y4 + cy, array[ii+1]+0.1);//output vertex
        //glVertex3f(x3 + cx, y3 + cy, 0);//output vertex
        glVertex3f(x4 + cx, y4 + cy, array[ii+1]+0.1);//output vertex
        glVertex3f(x3 + cx, y3 + cy, array[ii+1]+0.1);//output vertex
        //glVertex3f(x4 + cx, y4 + cy, 0);//output vertex
        glVertex3f(x3 + cx, y3 + cy, array[ii+1]+0.1);//output vertex
        glVertex3f(x1 + cx, y1 + cy, array[ii]+0.1);//output vertex


    }
    glEnd();


    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    float theta1 = 2.0f * 3.1415926f * float(rad) / float(num_segments);
//    float theta2 = 2.0f * 3.1415926f * float(rad+1) / float(num_segments);
//    float theta3 = 2.0f * 3.1415926f * float(rad-1) / float(num_segments);
    float x1 = r * cosf(theta1);
    float y1 = r * sinf(theta1);
//    float x2 = r * cosf(theta2);
//    float y2 = r * sinf(theta2);
//    float x3 = r * cosf(theta3);
//    float y3 = r * sinf(theta3);
    glVertex3f(0, 0, 0);
    glVertex3f(x1, y1, 0);
//    glVertex3f(x2, y2, -0.25);
//    glVertex3f(x2, y2, 0.25);
//    glVertex3f(x3, y3, -0.25);
//    glVertex3f(x3, y3, 0.25);
    glEnd();
}

void GLWidget::draw()
{
    for(int i = 0; i < 5; i++) {
        DrawCircle(0, 0, gr - (i * 0.1), 360);
    }
    if(rad == 359) {
        rad = 0;
    }
    else {
        rad++;
        //cout<<rad;
        //cout<<endl;
    }
    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 1);
    glVertex3f(-0.1, -0.1, 0);
    glColor3f(0.5, 0.5, 1);
    glVertex3f(0.1, -0.1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0.1, 0);
    glEnd();

}

