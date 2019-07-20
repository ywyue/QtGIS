#ifndef CNODE_H
#define CNODE_H
#include <QPointF>
#include <vector>
using namespace std;

/******节点类******/
class CNode
{
public:
    CNode();

    /******节点编号******/
    int NdID;

    /******节点坐标******/
    QPointF NdPoint;

    /******节点所在弧段编号******/
    vector<int> toArcID;
};

#endif // CNODE_H
