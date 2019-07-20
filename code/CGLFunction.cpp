#include "CGLFunction.h"
#include<iostream>
using namespace std;
CGLFunction::CGLFunction()
{

}
CGLFunction::~CGLFunction()
{

}
void CGLFunction::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void CGLFunction::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
}

void CGLFunction::paintGL()
{
     /******E00数据可视化******/
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3d(0, 0, 0);
    if(aMap!=NULL)
    {
        for(unsigned int i=0;i<aMap->Arcs.size();i++)
            aMap->DrawArc(aMap->Arcs.at(i).points);
        for(unsigned int i=0;i<aMap->Nodes.size();i++)
            DrawCircle(aMap->Nodes.at(i).NdPoint);

        /******通过鼠标点击节点查询******/
        if (this->IsSearchByClick==true) {

            if(ClickedTimes==2)
            {
                /******寻找最短路径******/
                ShortestPath.FStPath(minDisPoint1.NdID,minDisPoint2.NdID,aMap);
                glColor3f(1.0,0.0,0.0);
                for(unsigned int i=0;i<aMap->ArcIDpath.size();i++){
                    aMap->DrawArc(aMap->Arcs.at(aMap->ArcIDpath.at(i)-1).points);
                }
                aMap->ArcIDpath.clear();
                ClickedTimes=0;
            }
        }

        /******通过输入id查询******/
        else if(this->IsSearchByID==true){
            /******寻找最短路径******/
            ShortestPath.FStPath(minDisPoint1.NdID,minDisPoint2.NdID,aMap);
            glColor3f(1.0,0.0,0.0);
            for(unsigned int i=0;i<aMap->ArcIDpath.size();i++){
                aMap->DrawArc(aMap->Arcs.at(aMap->ArcIDpath.at(i)-1).points);
            }
            aMap->ArcIDpath.clear();
            IsSearchByID=false;
        }
    }
}
void CGLFunction::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta();
    if(numDegrees>0){
        scale=scale*1.1;
    }else{
        scale=scale*(1/1.1);
    }
    cout<<event->x()<<endl;
    cout<<event->y()<<endl;

    /******通过重设窗口大小实现缩放******/
    this->resize(int(width()*scale),int(height()*scale));

    /*通过调整可视区域实现缩放
    resize(100,100);
      int m_zoom=event->delta();
      float dx,dy;
      dx = (XMAX-XMIN)/20;
      dy= (YMAX-YMIN)/20;
      if(m_zoom<0)
      {
          XMIN -= dx;
          XMAX += dx;
          YMAX += dy;
          YMIN -= dy;
      }else
      {
          XMIN +=dx;
          XMAX -=dx;
          YMAX -=dy;
          YMIN +=dy;
      }
      update();
     */
}
void CGLFunction::DrawCircle(QPointF point)
{
    /******绘制节点******/
    glBegin(GL_POLYGON);
    QPointF pt;
    float scale=aMap->MaxP.rx()-aMap->MinP.rx();
    scale=scale/400;
    glColor3f(0.0,0.0,1.0);
    for(int j=0;j<3600;j++)
    {
        pt=QPointF(point.rx()+scale*cos(2*PI*j/3600),point.ry()+scale*sin(2*PI*j/3600));
        pt=pointOrtho(pt);
        glVertex2f(pt.rx(),pt.ry());
    }
    glEnd();
}

QPointF CGLFunction::pointOrtho(QPointF point)
{
    /******地理坐标转换为-1~1******/
    float width=aMap->MaxP.rx()-aMap->MinP.rx();
    float height=aMap->MaxP.ry()-aMap->MinP.ry();
    return QPointF((point.x()-aMap->MinP.rx())/width*2-1,
                   (point.y()-aMap->MinP.ry())/height*2-1);
}

QPointF CGLFunction::pointOrtho2(QPointF point, int wi, int he)
{
    /******窗口坐标转换为地理坐标******/
    float width=aMap->MaxP.rx()-aMap->MinP.rx();
    float height=aMap->MaxP.ry()-aMap->MinP.ry();
    return QPointF(point.x()*width/wi+aMap->MinP.rx(),-point.y()*height/he+aMap->MaxP.ry());
}

void CGLFunction::mousePressEvent(QMouseEvent *m)
{
    /******鼠标点击事件******/
    PressPoint = m->pos();
    int x = m->pos().x();
    int y = m->pos().y();
    cout<<x<<endl;
    cout<<y<<endl;
    ClickPoint= QPointF(x,y);
    int wi=width();
    int he=height();
    ClickPoint=pointOrtho2(ClickPoint,wi,he);
    ostringstream s;
    string str;

    /******获取起点******/
    if(ClickedTimes==0)
    {
        minDisPoint1=aMap->FindMinDisPoint(ClickPoint);
        s<<minDisPoint1.NdID;
        str = s.str();
        QToolTip::showText(m->globalPos(),QString::fromStdString(str));
        ClickedTimes=1;
    }

    /******获取终点******/
    else
    {
        minDisPoint2=aMap->FindMinDisPoint(ClickPoint);
        s<<minDisPoint2.NdID;
        str = s.str();
        QToolTip::showText(m->globalPos(),QString::fromStdString(str));
        ClickedTimes=2;
        this->update();
    }
}

void CGLFunction::mouseMoveEvent(QMouseEvent *m)
{
    /******平移******/
    /*通过调整可见区域实现平移
    float dx=m->x()-PressPoint.x();
    float dy=m->y()-PressPoint.y();
    PressPoint=m->pos();
    if(m->buttons() & Qt::LeftButton)
    {
        double xMove=dx/width()*(XMAX-XMIN);
        double yMove=dy/height()*(YMAX-YMIN);
        XMIN -=xMove;
        XMAX -=xMove;
        YMAX +=yMove;
        YMIN +=yMove;
        update();
    }
    */
}
