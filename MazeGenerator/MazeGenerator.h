#pragma once

#include <vector>
#include <set>
#include <algorithm>

#include "Utils.h"

#include "EasyX.h"



//迷宫生成器
class MazeGenerator
{   
public:
    enum class CellType
    {
        Wall = 0,
        Path = 1
    };

    struct IntVec2
    {
        IntVec2(){}
        IntVec2(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        int x = 0;
        int y = 0;
    };

    MazeGenerator() 
    {
    }

    virtual void InitMaze(IntVec2 MazeSize, IntVec2 WindowSize)
    {
        MazeSize_ = MazeSize;
        CellSize_.x = WindowSize.x / MazeSize.x;
        CellSize_.y = WindowSize.y / MazeSize.y;

        map_.resize(MazeSize_.x, std::vector<CellType>(MazeSize_.y, CellType::Wall));
        visited_.resize(MazeSize_.x, std::vector<bool>(MazeSize_.y, false));
    }

    virtual void Generate(){};

    void UpdateCellColor(int i, int j)
    {
        if(map_[i][j] == CellType::Path)
        {         
            SetCellColor(i, j, WHITE);
        }
        else
        {
            SetCellColor(i, j, BLACK);
        }
    }

    void SetCellColor(int i, int j, int Color)
    {
        EasyX::Get().UpdateCellColor(i * CellSize_.x, j * CellSize_.y, 
            (i+1) * CellSize_.x, (j+1) * CellSize_.y, Color);
    }

    //获取直接的4个邻居
    std::vector<IntVec2> GetNeighbors(int x, int y)
    {
        if(!IsInRange(x,y)) return {};

        std::vector<IntVec2> result;
        if(IsInRange(x - 1, y)) result.emplace_back(x - 1, y);
        if(IsInRange(x + 1, y)) result.emplace_back(x + 1, y);
        if(IsInRange(x, y - 1)) result.emplace_back(x, y - 1);
        if(IsInRange(x, y + 1)) result.emplace_back(x, y + 1);

        return result;
    }

    //获取间隔一个的4个邻居
    std::vector<IntVec2> GetNextNeighbors(int x, int y)
    {
        if(!IsInRange(x,y)) return {};

        std::vector<IntVec2> result;
        if(IsInRange(x - 2, y)) result.emplace_back(x - 2, y);
        if(IsInRange(x + 2, y)) result.emplace_back(x + 2, y);
        if(IsInRange(x, y - 2)) result.emplace_back(x, y - 2);
        if(IsInRange(x, y + 2)) result.emplace_back(x, y + 2);

        return result;
    }

    //坐标在范围之内
    bool IsInRange(int i, int j)
    {
        if(i <= 0 || j <= 0 || i >= MazeSize_.x || j >= MazeSize_.y)
            return false;
        return true;
    }

    void DisplayMap()
    {
        for(int i = 0; i < MazeSize_.x; i++)
        {
            for(int j = 0; j < MazeSize_.y; j++)
            {
                UpdateCellColor(i,j);
            }
        }
    }

    bool IsVisited(int i, int j)
    {
        return visited_[i][j];
    }

    void SetVisited(int i, int j, bool visit = true)
    {
        visited_[i][j] = visit;
    }

    void SetMap(int i, int j, CellType cellType)
    {
        if(!IsInRange(i,j)) return;

        map_[i][j] = cellType;
        UpdateCellColor(i, j);
        Sleep(Delay);
    }

    std::vector<std::vector<CellType>> map_;
    std::vector<std::vector<bool>> visited_;
    IntVec2 MazeSize_;
    IntVec2 CellSize_;

    int Delay = 18; //用于显示每一步的迷宫生成的时间延迟(ms)
};