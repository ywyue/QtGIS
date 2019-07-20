#include "CFileManage.h"
#include<QStringList>
#include<iostream>
using namespace std;
CFileManage::CFileManage()
{

}
CFileManage::~CFileManage()
{

}
void CFileManage::ReadFile(char* name){
    /******打开E00文件******/
    file = fopen(name,"r");
    fseek(file, 0L,SEEK_END);
    size_t size = ftell (file);
    fseek(file, 0L,SEEK_SET);
    char *buffer = new char[size];
    fread(buffer, size, 1, file);
    fclose(file);
    QString stre = buffer;
    delete buffer;

    QStringList Str_List=stre.split("\n",QString::SkipEmptyParts);
    QStringList Line_List;
    int LineCounter=1;
    int PointLine;

    /******按行读ARC数据******/
    Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
    bool arcsOver=false;

    /******对于双精度的ARC数据******/
    if(Line_List.at(1).toInt()==3&&arcsOver==false)
    {
        LineCounter++;
        Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
         while(Line_List.at(0).toInt()!=-1)
        {
            CArc aArc;

            /******读取记录头******/
            aArc.arcID=Line_List.at(0).toInt();
            aArc.arcNO=Line_List.at(1).toInt();
            aArc.arcFP=Line_List.at(2).toInt();
            aArc.arcTP=Line_List.at(3).toInt();
            aArc.arcrPolyid=Line_List.at(4).toInt();
            aArc.arclPolyid=Line_List.at(5).toInt();
            aArc.arcPN=Line_List.at(6).toInt();

            LineCounter++;
            QPointF pt;
            PointLine=LineCounter;

            /******读取点串坐标******/
            for(;LineCounter<PointLine+aArc.arcPN;LineCounter++)
            {
                Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
                pt=QPointF(Line_List.at(0).toFloat(),Line_List.at(1).toFloat());
                aArc.points.push_back(pt);
            }
            Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
            aMap.Arcs.push_back(aArc);
        }
        arcsOver=true;
    }

    else
    {
        /******对于单精度ARC数据******/
        LineCounter++;
        Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
        while(Line_List.at(0).toInt()!=-1)
        {
            CArc aArc;

            /******读取记录头******/
            aArc.arcID=Line_List.at(0).toInt();
            aArc.arcNO=Line_List.at(1).toInt();
            aArc.arcFP=Line_List.at(2).toInt();
            aArc.arcTP=Line_List.at(3).toInt();
            aArc.arcrPolyid=Line_List.at(4).toInt();
            aArc.arclPolyid=Line_List.at(5).toInt();
            aArc.arcPN=Line_List.at(6).toInt();

            LineCounter++;
            PointLine=LineCounter;

            /******对于行数为偶数的点串坐标******/
            if(aArc.arcPN%2==0)
            {
                int n=aArc.arcPN/2;
                QPointF p1,p2;
                for(;LineCounter<PointLine+n;LineCounter++)
                {
                    Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
                    p1=QPointF(Line_List.at(0).toFloat(),Line_List.at(1).toFloat());
                    aArc.points.push_back(p1);
                    p2=QPointF(Line_List.at(2).toFloat(),Line_List.at(3).toFloat());
                    aArc.points.push_back(p2);
                }
            }

            /******对于行数为奇数的点串坐标******/
            else
            {
                int n=(aArc.arcPN+1)/2;
                QPointF p1,p2;
                for(;LineCounter<PointLine+n;LineCounter++)
                {
                    Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
                    if(LineCounter<PointLine+n-1)
                    {
                        p1=QPointF(Line_List.at(0).toFloat(),Line_List.at(1).toFloat());
                        aArc.points.push_back(p1);
                        p2=QPointF(Line_List.at(2).toFloat(),Line_List.at(3).toFloat());
                        aArc.points.push_back(p2);
                    }
                    else
                    {
                        p1=QPointF(Line_List.at(0).toFloat(),Line_List.at(1).toFloat());
                        aArc.points.push_back(p1);
                    }
                }
            }
            Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
            aMap.Arcs.push_back(aArc);
        }
    }

    do{
        LineCounter++;
        Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
    }while(Line_List.at(0)!="IFO");
    LineCounter++;
    Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
    LineCounter=LineCounter+Line_List.at(2).toInt()+1;

    /******读取AAT数据******/
    int fieldNum=Line_List.at(2).toInt(),LineDis;
    if(fieldNum%5==0)
        LineDis=fieldNum/5;
    else
        LineDis=fieldNum/5+1;
    Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
    while(Line_List.at(1)!="XX")
    {
        CInfoAAT aAAT;
        aAAT.aatFN=Line_List.at(0).toInt();
        aAAT.aatTN=Line_List.at(1).toInt();
        aAAT.aatLP=Line_List.at(2).toInt();
        aAAT.aatRP=Line_List.at(3).toInt();
        aAAT.aatLength=Line_List.at(4).toDouble();
        aMap.Info.AATs.push_back(aAAT);
        LineCounter=LineCounter+LineDis;
        Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
    }

    /******读取BND数据******/
    LineCounter=LineCounter+5;
    Line_List=Str_List.at(LineCounter).split(" ",QString::SkipEmptyParts);
    QPointF minP,maxP;
    minP=QPointF(Line_List.at(0).toFloat(),Line_List.at(1).toFloat());
    maxP=QPointF(Line_List.at(2).toFloat(),Line_List.at(3).toFloat());
    aMap.MinP=minP;
    aMap.MaxP=maxP;

    /******读取TIC数据******/
    for(int i=LineCounter+5;i<Str_List.size();i++)
    {
        Line_List=Str_List.at(i).split(" ",QString::SkipEmptyParts);
        if(Line_List.at(0)!="EOI")
        {
            CInfoTIC aTIC;
            aTIC.TICID=Line_List.at(0).toInt();
            QPointF ticP;
            ticP=QPointF(Line_List.at(1).toFloat(),Line_List.at(2).toFloat());
            aTIC.TICP=ticP;
            aMap.Info.TICs.push_back(aTIC);
        }
        else
            break;
    }

    /******添加节点和弧段到地图******/
    aMap.GetNodes();
    aMap.GetArcs();
}

