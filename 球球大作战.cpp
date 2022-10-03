#include<graphics.h> /*安装图形库，引入头文件*/
#include<tchar.h>
#include<Windows.h>
//定义窗口宽
#define WIDTH 600
//定义窗口高
#define HEIGHT 800

/*1 做一个窗口（控制台，图形界面）
2 做敌对小球 n个
	2.1 生成小球
	2.2 小球移动
	2.3 小球死亡（移动出界面）
3 做自己的小球
	3.1 生成小球
	3.2 小球移动
	3.3 碰撞检测：小球变大和游戏结束*/
	//初始化游戏
void initGame();
//游戏界面绘制
void drawGame();
//游戏流程控制
void controlGame();
int  _tmain(int argc, _TCHAR* argv[])
{

	initGame();
	drawGame();
	system("pause");
	return 0;
}
void initGame()
{
	//1 画窗口
	initgraph(WIDTH, HEIGHT);

	//2 敌对球初始化

	//3 自己球初始化

}
void drawGame()
{

}
void controlGame()
{

}



