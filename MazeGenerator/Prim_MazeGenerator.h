#pragma once

#include "MazeGenerator.h"

class Prim_MazeGenerator : public MazeGenerator
{
public:
    virtual void Generate() override
    {
        Prim();
    }

private:
    //法2: Prim算法
    void Prim()
    {
        std::set<std::pair<int,int>> TodoRoadPointSets; //待处理路点集合

        //1 起点的四周路点加入待处理路点集合
        for(IntVec2 p : GetNextNeighbors(1, 1))
            TodoRoadPointSets.insert({ p.x, p.y });
        SetMap(1, 1, CellType::Path); //起点变成路

        while(!TodoRoadPointSets.empty())
        {
            //2 从待处理路点集合, 随机获取一个元素
            int randomIndex = Utils::GetRandomRange(0, (int)TodoRoadPointSets.size() - 1);
            auto it = TodoRoadPointSets.begin();
            std::advance(it, randomIndex);
            auto [cellX, cellY] = *it;
            TodoRoadPointSets.erase(it);
            
            //3 获取路点的四周邻居
            std::vector<IntVec2> Neighbors = GetNextNeighbors(cellX, cellY);
            bool isFirstBreakWall = false; //只允许一次打破一个墙
            while(!Neighbors.empty())
            {
                //4 随机获取一个邻居
                int randomNeighbor = Utils::GetRandomRange(0, (int)Neighbors.size() - 1);
                auto [nextX, nextY] = Neighbors[randomNeighbor];
                Neighbors.erase(Neighbors.begin() + randomNeighbor);

                //4.1 如果邻居已经是路, 就打通之间的墙 [一次最多只打通一个邻居的墙]
                if(map_[nextX][nextY] == CellType::Path && !isFirstBreakWall) 
                {
                    int wallX = (cellX + nextX) / 2;
                    int wallY = (cellY + nextY) / 2;
                    SetMap(wallX, wallY, CellType::Path); //墙变路

                    SetMap(cellX, cellY, CellType::Path); //自己变路
                    isFirstBreakWall = true;
                }
                else //4.2 邻居还没成路,加入集合
                {
                    if(map_[nextX][nextY] == CellType::Wall)
                    {
                        TodoRoadPointSets.insert({nextX, nextY});
                    }
                }
            }
        }
    }
};

