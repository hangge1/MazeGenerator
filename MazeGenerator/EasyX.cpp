#include "EasyX.h"

EasyX::EasyX()
{

}

EasyX::~EasyX()
{
    CloseGraph();
}

void EasyX::InitGraph(int w, int h)
{
    initgraph(w, h);
}

void EasyX::CloseGraph()
{
    closegraph();   // 关闭绘图窗口
}

void EasyX::UpdateCellColor(int left, int up, int right, int bottom, 
    int color)
{
    //setlinecolor(color);
    setfillcolor(color);
    fillrectangle(left, up, right, bottom);
}
