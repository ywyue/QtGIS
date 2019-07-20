#ifndef CSHORTESTPATH_H
#define CSHORTESTPATH_H
#include <iostream>
#include <vector>
#include "CMap.h"
using namespace std;

/******最短路径类******/
class CShortestPath
{
public:
    CShortestPath();
    vector<int> path;
    vector<int> ArcIDPath;
    float length = 0;
    float shortestpath = 999999.0;

    /******深度优先遍历******/
    void DeepFind(int , int , CMap * );
    void FStPath(int , int , CMap * );
};

#endif // CSHORTESTPATH_H
