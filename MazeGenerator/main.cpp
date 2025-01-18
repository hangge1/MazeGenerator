
#include "EasyX.h"
#include "MazeGenerator.h"
#include "DFS_MazeGenerator.h"

const int Window_Height = 800;
const int Window_Width = 800;

const int MazeRow = 21;
const int MazeCol = 21;



int main()
{
    EasyX& easyX = EasyX::Get();
    easyX.InitGraph(Window_Height, Window_Width);

    MazeGenerator* gen = new DFS_MazeGenerator();
    gen->InitMaze(MazeRow, MazeCol, Window_Height, Window_Width);
    gen->Generate();

    //gen.DfsRunMaze();
    //gen.Prim_Generate();

	_getch();   // 按任意键继续
	return 0;
}