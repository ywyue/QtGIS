#include "CShortestPath.h"

CShortestPath::CShortestPath()
{

}
void CShortestPath::DeepFind(int Fn,int Tn,CMap* aMap)
{
    /******深度优先遍历******/
    int size = aMap->Nodes.size();
    CArc arc;
    CInfoAAT aat;
    CNode pt,point;
    int m;
    /******查找开始节点******/
    for(int i=0;i<size;i++)
    {
        point = aMap->Nodes.at(i);
        if(Fn==point.NdID)
        {
            pt = point;
            break;
        }
    }
    if(path.size()==0)
        path.push_back(pt.NdID);
    for(unsigned int i=0;i<pt.toArcID.size();i++)
    {
        if(shortestpath<length)
            break;
        /******获取相邻弧段******/
        int n = pt.toArcID.at(i)-1;
        arc = aMap->Arcs.at(n);
        aat = aMap->Info.AATs.at(n);

        if(arc.arcFP==pt.NdID)
            m = arc.arcTP;
        else
            m = arc.arcFP;
        unsigned int j=0;
        while (j<path.size())
        {
            j++;
            if(m==path.at(j-1))
                    break;
        }
        if(m==path.at(j-1))
            continue;
        path.push_back(m);
        ArcIDPath.push_back(arc.arcID);
        length+=aat.aatLength;
        if(m==Tn)
        {
            if(length<shortestpath)
            {
                shortestpath = length;
                aMap->ArcIDpath = ArcIDPath;
                aMap->pathNodeID = path;
            }
        }
        else
            DeepFind(m,Tn,aMap);
        path.pop_back();
        ArcIDPath.pop_back();
        length -=aat.aatLength;
    }
}

void CShortestPath::FStPath(int Fn,int Tn,CMap* aMap)
{
    DeepFind(Fn,Tn,aMap);
    length = 0;
    shortestpath = 999999.0;
    this->path.clear();
    this->ArcIDPath.clear();
}
