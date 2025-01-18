
#include "EasyX.h"
#include "MageGenerator.h"

const int Window_Height = 800;
const int Window_Width = 800;

const int MazeRow = 21;
const int MazeCol = 21;



int main()
{
    EasyX easyX(Window_Height, Window_Width);

    MageGenerator gen;
    gen.InitMaze(MazeRow, MazeCol, Window_Height, Window_Width);

    //gen.DfsRunMaze();
    gen.Prim_Generate();

	_getch();   // 按任意键继续
	return 0;
}