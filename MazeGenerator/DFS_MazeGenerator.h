#pragma once

#include "MazeGenerator.h"

class DFS_MazeGenerator : public MazeGenerator
{
public:
    virtual void InitMaze(IntVec2 MazeSize, IntVec2 WindowSize) override
    {
        MazeGenerator::InitMaze(MazeSize, WindowSize);

        for( int i = 0; i < MazeSize_.x; i++ )
        {
            for(int j = 0; j < MazeSize_.y; j++)
            {
                if(i % 2 == 1 && j % 2 == 1)
                {
                    map_[i][j] = CellType::Path;
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

        std::vector<IntVec2> diff = {
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

                SetMap(wallx, wally, CellType::Path);
                SetVisited(wallx, wally);
                dfs(nextRoadX, nextRoadY);
            }

            //每次随机选中的没访问过的道路放到后部
            std::swap(diff[SwapIndex], diff[index]);
            SwapIndex--;
        }
    }
};

