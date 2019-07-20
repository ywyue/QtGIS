#ifndef CMAP_H
#define CMAP_H
#include <QString>
#include <QStringList>
#include <vector>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "CArc.h"
#include "CInfo.h"
#include "CNode.h"
using namespace std;

/******地图类******/
class CMap
{
public:
    CMap();
    ~CMap();

    vector<CArc> Arcs;
    vector<CNode> Nodes;
    CInfo Info;
    CNode aNode;
    vector<int> ArcIDpath;
    vector<int> pathNodeID;

    /******坐标范围******/
    QPointF MinP,MaxP;

    /******坐标转换函数（经纬度到-1~1）******/
    QPointF pointOrtho(QPointF point);

    /******绘制弧段******/
    void DrawArc(vector<QPointF> points);

    /******查找距离鼠标点击点最近的节点******/
    CNode FindMinDisPoint(QPointF ClickPoint);

    /******计算窗口中两点之间距离******/
    float distanceCalculate(QPointF point1, QPointF point2);

    void GetNodes();
    void AddNode(int NdID, QPointF NdPoint);
    void GetArcs();
};

#endif // CMAP_H
