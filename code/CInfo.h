#ifndef CINFO_H
#define CINFO_H
#include<CInfoAAT.h>
#include<CInfoTIC.h>
#include<vector>
using namespace std;

/******属性信息类******/
class CInfo
{
public:
    CInfo();

    /******AAT属性******/
    vector<CInfoAAT> AATs;

    /******TIC属性******/
    vector<CInfoTIC> TICs;
};

#endif // CINFO_H
