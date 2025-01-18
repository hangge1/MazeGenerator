#include "EasyX.h"

EasyX::EasyX(int w, int h)
{
    InitGraph(w, h);
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
