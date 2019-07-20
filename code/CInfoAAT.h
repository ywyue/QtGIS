#ifndef CINFOAAT_H
#define CINFOAAT_H
#include <QPointF>
#include <QString>

/******AAT属性类******/
class CInfoAAT
{
public:
    CInfoAAT();

    /******起始节点******/
    int aatFN;
    int aatTN;

    /******左右多边形******/
    int aatLP;
    int aatRP;

    /******弧线长度******/
    double aatLength;
};

#endif // CINFOAAT_H
