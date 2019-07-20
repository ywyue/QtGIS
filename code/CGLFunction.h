#ifndef CGLFUNCTION_H
#define CGLFUNCTION_H
#include <QMainWindow>
#include <QLabel>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <CMap.h>
#include <QMouseEvent>
#include <QWidget>
#include <QWheelEvent>
#include <QToolTip>
#include <sstream>
#include <QTableWidget>
#include "CShortestPath.h"

/******OpenGL绘制类******/
class CGLFunction : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    CGLFunction();
    ~CGLFunction();
    void initializeGL();
    void resizeGL(int width, int height);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *m);
    void mouseMoveEvent(QMouseEvent *m);

    /******图形绘制******/
    void paintGL();

    /******绘制节点******/
    void DrawCircle(QPointF point);

    /******地理坐标转换为-1~1******/
    QPointF pointOrtho(QPointF point);

    /******窗口坐标转换为地理坐标******/
    QPointF pointOrtho2(QPointF point,int wi,int he);

    CMap *aMap=NULL;
    CShortestPath ShortestPath;

    /******初始化鼠标点击次数******/
    int ClickedTimes=0;

    /******判断用户查询方式******/
    bool IsSearchByClick=false;
    bool IsSearchByID=false;

    QPointF ClickPoint;
    QPointF PressPoint;

    /******鼠标点击的起始点******/
    CNode minDisPoint1,minDisPoint2;

    float scale=1;
    float PI = 3.1415926f;
    vector<CArc> shortestPath;

    double XMIN=-1.0;
    double XMAX=1.0;
    double YMIN=-1.0;
    double YMAX=1.0;



};

#endif // CGLFUNCTION_H
