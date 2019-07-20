#include "CMap.h"
#include<stdio.h>
#include<iostream>
using namespace std;
CMap::CMap()
{

}
CMap::~CMap()
{

}

QPointF CMap::pointOrtho(QPointF point)
{
    /******坐标转换函数（经纬度到-1~1）******/
    float width=MaxP.rx()-MinP.rx();
    float height=MaxP.ry()-MinP.ry();
    return QPointF((point.x()-MinP.rx())/width*2-1,
                   (point.y()-MinP.ry())/height*2-1);
}

void CMap::DrawArc(vector<QPointF> points)
{
    /******绘制弧段******/
    QPointF pt;
    glBegin(GL_LINE_STRIP);
    for(unsigned int j=0;j<points.size();j++)
    {
        pt=points.at(j);
        pt=pointOrtho(pt);
        glVertex2f(pt.x(),pt.y());
    }
    glEnd();
}

CNode CMap::FindMinDisPoint(QPointF ClickPoint)
{
    /******查找距离鼠标点击点最近的节点******/
    CNode minDisPoint;
    float distance;
    for(unsigned int i=0;i<Nodes.size();i++)
    {
        if(i==0)
        {
            minDisPoint=Nodes.at(i);
            distance=distanceCalculate(Nodes.at(i).NdPoint,ClickPoint);
        }

        else if(distanceCalculate(Nodes.at(i).NdPoint,ClickPoint)==0)
        {
            minDisPoint=Nodes.at(i);
            break;
        }

        else if(distanceCalculate(Nodes.at(i).NdPoint,ClickPoint)<distance)
        {
            distance=distanceCalculate(Nodes.at(i).NdPoint,ClickPoint);
            minDisPoint=Nodes.at(i);
        }
    }
    return minDisPoint;
}

void CMap::GetNodes()
{
    /******获取弧段中的节点******/
    for(unsigned int i=0;i<Arcs.size();i++)
    {
        if(i==0)
        {
            AddNode(Arcs.at(i).arcFP,Arcs.at(i).points.at(0));
            if(Arcs.at(i).arcTP!=Nodes.at(0).NdID)
                AddNode(Arcs.at(i).arcTP,Arcs.at(i).points.at(Arcs.at(i).points.size()-1));
        }
        else
        {
            if(Arcs.at(i).arcFP>Nodes.at(Nodes.size()-1).NdID)
                AddNode(Arcs.at(i).arcFP,Arcs.at(i).points.at(0));
            if(Arcs.at(i).arcTP>Nodes.at(Nodes.size()-1).NdID)
                AddNode(Arcs.at(i).arcTP,Arcs.at(i).points.at(Arcs.at(i).points.size()-1));
        }
    }
}

void CMap::AddNode(int NdID, QPointF NdPoint)
{
    /******添加节点******/
    aNode.NdID=NdID;
    aNode.NdPoint=NdPoint;
    Nodes.push_back(aNode);
}

void CMap::GetArcs()
{
    /******获取弧段编号******/
    for(unsigned int i=0;i<Nodes.size();i++)
    {
        for(unsigned int j=0;j<Arcs.size();j++)
        {
            if(Nodes.at(i).NdID==Arcs.at(j).arcFP)
                Nodes.at(i).toArcID.push_back(Arcs.at(j).arcID);

            if(Nodes.at(i).NdID==Arcs.at(j).arcTP)
                Nodes.at(i).toArcID.push_back(Arcs.at(j).arcID);
        }
    }
}

float CMap::distanceCalculate(QPointF point1, QPointF point2)
{
    /******计算窗口中两点之间距离******/
    return ((point1.x()-point2.x())*(point1.x()-point2.x())+
           (point1.y()-point2.y())*(point1.y()-point2.y()));
}
