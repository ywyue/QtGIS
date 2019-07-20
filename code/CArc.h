#ifndef CARC_H
#define CARC_H
#include<QString>
#include<QPointF>
#include<vector>
using namespace std;

/******线要素类******/
class CArc
{
public:
    CArc();

    /******线记录号******/
    int arcID;

    /******用户编码******/
    int arcNO;

    /******开始端点的编号******/
    int arcFP;

    /******结束端点的编号******/
    int arcTP;

    /******左多边形编号******/
    int arcrPolyid;

    /******右多边形编号******/
    int arclPolyid;

    /******点的数目******/
    int arcPN;

    /******点串坐标******/
    vector<QPointF> points;
};

#endif // CARC_H
