#ifndef CINFOTIC_H
#define CINFOTIC_H
#include <QPointF>

/******矫正点类******/
class CInfoTIC
{
public:
    CInfoTIC();

    /******矫正点编号******/
    int TICID;

    /******矫正点坐标******/
    QPointF TICP;
};

#endif // CINFOTIC_H
