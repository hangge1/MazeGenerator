#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <vector>
#include <random>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

#define Window_Height 800
#define Window_Width 800

//迷宫生成器
class MageGenerator
{
    const int kWall = 0;
    const int kRoad = 1;
public:
    MageGenerator(int height, int width)
        : height_(height), width_(width)
    {
        map_.resize(height, vector<int>(width, kWall));
        visited_.resize(height, vector<bool>(width, false));

        cellHeightSize_ = Window_Height / height_;
        cellWidthSize_ = Window_Width / width_;
    }

    //随机化深搜
    void Dfs_Generate()
    {  
        for(int i = 0; i < height_; i++)
        {
            for(int j = 0; j < width_; j++)
            {
                if(i % 2 == 1 && j % 2 == 1)
                {
                    map_[i][j] = kRoad;
                }
            }
        }

        PrintMap();
        dfs(1, 1);
    }

    //Prim生成
    void Prim_Generate()
    {
        Prim();
    }

    //法1: 随机化深搜
    void dfs(int i, int j)
    {
        if(!IsInRange(i,j) || IsVisited(i, j))
            return;

        SetVisited(i, j);

        vector<pair<int,int>> diff = {
            {-2, 0},
            {2, 0},
            {0, -2},
            {0, 2},
        };

        int SwapIndex = (int)diff.size() - 1;

        while(SwapIndex >= 0)
        {
            int index = GetRandomIndex(0, SwapIndex);
            int dx = diff[index].first;
            int dy = diff[index].second;

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

    //法2: Prim算法
    void Prim()
    {
        set<pair<int,int>> TodoRoadPointSets; //待处理路点集合

        //1 起点的四周路点加入待处理路点集合
        for(pair<int,int> p : GetNextNeighbors(1, 1))
            TodoRoadPointSets.insert({p.first, p.second});
        SetMap(1, 1, kRoad); //起点变成路

        while(!TodoRoadPointSets.empty())
        {
            //2 从待处理路点集合, 随机获取一个元素
            int randomIndex = GetRandomIndex(0, TodoRoadPointSets.size() - 1);
            auto it = TodoRoadPointSets.begin();
            std::advance(it, randomIndex);
            auto [cellX, cellY] = *it;
            TodoRoadPointSets.erase(it);
            
            //3 获取路点的四周邻居
            vector<pair<int,int>> Neighbors = GetNextNeighbors(cellX, cellY);
            bool isFirstBreakWall = false; //只允许一次打破一个墙
            while(!Neighbors.empty())
            {
                //4 随机获取一个邻居
                int randomNeighbor = GetRandomIndex(0, Neighbors.size() - 1);
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
            setlinecolor(BLACK);
            setfillcolor(WHITE);
            fillrectangle(i * cellWidthSize_, j * cellHeightSize_, (i+1) * cellWidthSize_, (j+1) * cellHeightSize_);
        }
        else
        {
            setlinecolor(BLACK);
            setfillcolor(BLACK);
            fillrectangle(i * cellWidthSize_, j * cellHeightSize_, (i+1) * cellWidthSize_, (j+1) * cellHeightSize_);
        }
    }

    void SetCellColor(int i, int j, int Color)
    {
        setlinecolor(Color);
        setfillcolor(Color);
        fillrectangle(i * cellWidthSize_, j * cellHeightSize_, (i+1) * cellWidthSize_, (j+1) * cellHeightSize_);
    }

    //获取直接的4个邻居
    vector<pair<int,int>> GetNeighbors(int x, int y)
    {
        if(!IsInRange(x,y)) return {};

        vector<pair<int,int>> result;
        if(IsInRange(x - 1, y)) result.emplace_back(x - 1, y);
        if(IsInRange(x + 1, y)) result.emplace_back(x + 1, y);
        if(IsInRange(x, y - 1)) result.emplace_back(x, y - 1);
        if(IsInRange(x, y + 1)) result.emplace_back(x, y + 1);

        return result;
    }

    //获取间隔一个的4个邻居
    vector<pair<int,int>> GetNextNeighbors(int x, int y)
    {
        if(!IsInRange(x,y)) return {};

        vector<pair<int,int>> result;
        if(IsInRange(x - 2, y)) result.emplace_back(x - 2, y);
        if(IsInRange(x + 2, y)) result.emplace_back(x + 2, y);
        if(IsInRange(x, y - 2)) result.emplace_back(x, y - 2);
        if(IsInRange(x, y + 2)) result.emplace_back(x, y + 2);

        return result;
    }

    //返回随机数，范围是 [min,max]
    int GetRandomIndex(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(min, max);
        int randomInt = dis(gen);
        return randomInt;
    }

    //坐标在范围之内
    bool IsInRange(int i, int j)
    {
        if(i <= 0 || j <= 0 || i >= height_ || j >= width_)
            return false;
        return true;
    }

    void PrintMap()
    {
        for(int i = 0; i < height_; i++)
        {
            for(int j = 0; j < width_; j++)
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

    vector<vector<int>> map_;
    vector<vector<bool>> visited_;
    int height_;
    int width_;

    int cellHeightSize_;
    int cellWidthSize_;

    int Delay = 18; //用于显示每一步的迷宫生成的时间延迟(ms)
};

int main()
{
	initgraph(Window_Height, Window_Width);	// 创建绘图窗口，大小为 640x480 像素
    
    int row = 21; 
    int col = 21; 

    MageGenerator gen(row,col);
    //gen.DfsRunMaze();
    gen.Prim_Generate();

	_getch();   // 按任意键继续
	closegraph();   // 关闭绘图窗口
	return 0;
}