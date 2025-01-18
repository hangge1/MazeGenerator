#pragma once

#include "MazeGenerator.h"
#include "UnionSet.h"


class Kruskal_MazeGenerator : public MazeGenerator
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

        us.Init(MazeSize_.x * MazeSize_.y);
    }

    virtual void Generate() override
    {
        DisplayMap();
        Kruskal();
    }

    void Kruskal()
    {
        std::set<std::pair<int,int>> TodoEdgeSets; //待处理墙集合
        for(int i = 1; i < MazeSize_.x; i += 2)
        {
            for(int j = 1; j < MazeSize_.y; j += 2)
            {
                if(i < MazeSize_.x - 2)
                {
                    TodoEdgeSets.insert({i * MazeSize_.x + j, (i + 2) * MazeSize_.x + j});
                }
                if(j < MazeSize_.y - 2)
                {
                    TodoEdgeSets.insert({i * MazeSize_.y + j, i * MazeSize_.y + j + 2});
                }
            }
        }

        while(!TodoEdgeSets.empty())
        {
            //2 待处理墙集合, 随机获取一个墙
            int randomIndex = Utils::GetRandomRange(0, (int)TodoEdgeSets.size() - 1);
            auto it = TodoEdgeSets.begin();
            std::advance(it, randomIndex);
            auto [edgeStart, edgeEnd] = *it;
            TodoEdgeSets.erase(it);

            if(!us.IsSameSet(edgeStart, edgeEnd)) 
            {
                us.Union(edgeStart, edgeEnd);

                int x1 = edgeStart / MazeSize_.y;
                int y1 = edgeStart % MazeSize_.y;
                int x2 = edgeEnd / MazeSize_.y;
                int y2 = edgeEnd % MazeSize_.y;
                
                SetMap((x1 + x2) / 2, (y1 + y2) / 2, CellType::Path);
            }
        }
    }

private:

    UnionSet us;
};

