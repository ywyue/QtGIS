#ifndef CFILEMANAGER_H
#define CFILEMANAGER_H
#include <stdio.h>
#include <iostream>
#include <QString>
#include <CMap.h>

using namespace std;
/******文件读取类******/
class CFileManage
{
public:
    CFileManage();
    ~CFileManage();

    /******读文件******/
    void ReadFile(char* name);

    FILE *file;
    CMap aMap;
};

#endif // CFILEMANAGER_H
