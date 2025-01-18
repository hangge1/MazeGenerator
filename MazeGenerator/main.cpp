
#include "EasyX.h"
#include "MazeGenerator.h"
#include "DFS_MazeGenerator.h"
#include "Prim_MazeGenerator.h"

const int Window_Height = 800;
const int Window_Width = 800;

const int MazeRow = 21;
const int MazeCol = 21;



int main()
{
    EasyX& easyX = EasyX::Get();
    easyX.InitGraph(Window_Height, Window_Width);
    
    //Prim
    /*MazeGenerator* gen = new Prim_MazeGenerator();
    gen->InitMaze({MazeRow, MazeCol}, {Window_Height, Window_Width});
    gen->Generate();*/

    //DFS
    MazeGenerator* gen = new DFS_MazeGenerator();
    gen->InitMaze({MazeRow, MazeCol}, {Window_Height, Window_Width});
    gen->Generate();


	_getch();   // 按任意键继续
	return 0;
}