#pragma once

#include "MazeGenerator.h"

class DFS_MazeGenerator : public MazeGenerator
{
public:
    virtual void InitMaze(int row, int col, int win_Height, int win_Width) override
    {
        MazeGenerator::InitMaze(row, col, win_Height, win_Width);

        for(int i = 0; i < row_; i++)
        {
            for(int j = 0; j < col_; j++)
            {
                if(i % 2 == 1 && j % 2 == 1)
                {
                    map_[i][j] = kRoad;
                }
            }
        }
    }

    virtual void Generate() override
    {
        DisplayMap();
        dfs(1, 1);
    }

private:
    //法1: 随机化深搜
    void dfs(int i, int j)
    {
        if(!IsInRange(i,j) || IsVisited(i, j))
            return;

        SetVisited(i, j);

        std::vector<Cell> diff = {
            {-2, 0},
            {2, 0},
            {0, -2},
            {0, 2},
        };

        int SwapIndex = (int)diff.size() - 1;

        while(SwapIndex >= 0)
        {
            int index = Utils::GetRandomRange(0, SwapIndex);
            int dx = diff[index].x;
            int dy = diff[index].y;

            int nextRoadX = i + dx;
            int nextRoadY = j + dy;

            if(IsInRange(nextRoadX, nextRoadY) && !IsVisited(nextRoadX, nextRoadY))
            {
                int wallx = (i + nextRoadX) / 2;
                int wally = (j + nextRoadY) / 2;

                SetMap(wallx, wally, kRoad);
                SetVisited(wallx, wally);
                dfs(nextRoadX, nextRoadY);
            }

            //每次随机选中的没访问过的道路放到后部
            std::swap(diff[SwapIndex], diff[index]);
            SwapIndex--;
        }
    }
};

