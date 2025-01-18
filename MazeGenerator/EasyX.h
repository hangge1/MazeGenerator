#pragma once

#include <graphics.h>		// 引用图形库头文件
#include <conio.h>



class EasyX
{
public:
    EasyX(int w, int h);
    ~EasyX();

    void InitGraph(int w, int h);

    void CloseGraph();
};

