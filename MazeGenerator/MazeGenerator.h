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
    const int kWall = 0;
    const int kRoad = 1;
    struct Cell
    {
        Cell(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        int x;
        int y;
    };

    MazeGenerator() 
    {
    }

    virtual void InitMaze(int row, int col, int win_Height, int win_Width)
    {
        row_ = row;
        col_ = col;
        cellHeightSize_ = win_Height / row_;
        cellWidthSize_ = win_Width / col_;

        map_.resize(row_, std::vector<int>(col_, kWall));
        visited_.resize(row_, std::vector<bool>(col_, false));
    }

    virtual void Generate(){};

    //Prim生成
    void Prim_Generate()
    {
        Prim();
    } 

    //法2: Prim算法
    void Prim()
    {
        std::set<std::pair<int,int>> TodoRoadPointSets; //待处理路点集合

        //1 起点的四周路点加入待处理路点集合
        for(Cell p : GetNextNeighbors(1, 1))
            TodoRoadPointSets.insert({ p.x, p.y });
        SetMap(1, 1, kRoad); //起点变成路

        while(!TodoRoadPointSets.empty())
        {
            //2 从待处理路点集合, 随机获取一个元素
            int randomIndex = Utils::GetRandomRange(0, (int)TodoRoadPointSets.size() - 1);
            auto it = TodoRoadPointSets.begin();
            std::advance(it, randomIndex);
            auto [cellX, cellY] = *it;
            TodoRoadPointSets.erase(it);
            
            //3 获取路点的四周邻居
            std::vector<Cell> Neighbors = GetNextNeighbors(cellX, cellY);
            bool isFirstBreakWall = false; //只允许一次打破一个墙
            while(!Neighbors.empty())
            {
                //4 随机获取一个邻居
                int randomNeighbor = Utils::GetRandomRange(0, (int)Neighbors.size() - 1);
                auto [nextX, nextY] = Neighbors[randomNeighbor];
                Neighbors.erase(Neighbors.begin() + randomNeighbor);

                //4.1 如果邻居已经是路, 就打通之间的墙 [一次最多只打通一个邻居的墙]
                if(map_[nextX][nextY] == kRoad && !isFirstBreakWall) 
                {
                    int wallX = (cellX + nextX) / 2;
                    int wallY = (cellY + nextY) / 2;
                    SetMap(wallX, wallY, kRoad); //墙变路

                    SetMap(cellX, cellY, kRoad); //自己变路
                    isFirstBreakWall = true;
                }
                else //4.2 邻居还没成路,加入集合
                {
                    if(map_[nextX][nextY] == kWall)
                    {
                        TodoRoadPointSets.insert({nextX, nextY});
                    }
                }
            }
        }
    }

    void UpdateCellColor(int i, int j)
    {
        if(map_[i][j] == kRoad)
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
        EasyX::Get().UpdateCellColor(i * cellWidthSize_, j * cellHeightSize_, 
            (i+1) * cellWidthSize_, (j+1) * cellHeightSize_, Color);
    }

    //获取直接的4个邻居
    std::vector<Cell> GetNeighbors(int x, int y)
    {
        if(!IsInRange(x,y)) return {};

        std::vector<Cell> result;
        if(IsInRange(x - 1, y)) result.emplace_back(x - 1, y);
        if(IsInRange(x + 1, y)) result.emplace_back(x + 1, y);
        if(IsInRange(x, y - 1)) result.emplace_back(x, y - 1);
        if(IsInRange(x, y + 1)) result.emplace_back(x, y + 1);

        return result;
    }

    //获取间隔一个的4个邻居
    std::vector<Cell> GetNextNeighbors(int x, int y)
    {
        if(!IsInRange(x,y)) return {};

        std::vector<Cell> result;
        if(IsInRange(x - 2, y)) result.emplace_back(x - 2, y);
        if(IsInRange(x + 2, y)) result.emplace_back(x + 2, y);
        if(IsInRange(x, y - 2)) result.emplace_back(x, y - 2);
        if(IsInRange(x, y + 2)) result.emplace_back(x, y + 2);

        return result;
    }

    //坐标在范围之内
    bool IsInRange(int i, int j)
    {
        if(i <= 0 || j <= 0 || i >= row_ || j >= col_)
            return false;
        return true;
    }

    void DisplayMap()
    {
        for(int i = 0; i < row_; i++)
        {
            for(int j = 0; j < col_; j++)
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

    void SetMap(int i, int j, int val)
    {
        if(!IsInRange(i,j)) return;

        map_[i][j] = val;
        UpdateCellColor(i, j);
        Sleep(Delay);
    }

    std::vector<std::vector<int>> map_;
    std::vector<std::vector<bool>> visited_;
    int row_;
    int col_;

    int cellHeightSize_;
    int cellWidthSize_;

    int Delay = 18; //用于显示每一步的迷宫生成的时间延迟(ms)
};