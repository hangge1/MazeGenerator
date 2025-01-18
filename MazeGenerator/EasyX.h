#pragma once

#include <graphics.h>		// 引用图形库头文件
#include <conio.h>



class EasyX
{
public:
    EasyX();
    ~EasyX();

    static EasyX& Get()
    {
        static EasyX eaxyX;
        return eaxyX;
    }

    void InitGraph(int w, int h);

    void CloseGraph();

    void UpdateCellColor(int left, int up, int right, int bottom, int color);
};

