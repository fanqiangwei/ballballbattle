#include<graphics.h> /*安装图形库，引入头文件*/
#include<tchar.h>
#include<Windows.h>
#include<vector>
using namespace std; 
//*1 做一个窗口（控制台，图形界面）
//定义窗口宽
#define WIDTH   600
//定义窗口高
#define HEIGHT  600
//敌对球数量
#define NUM  20
struct Fx {                  //方向；
	int a;                   //单位时间x轴移动距离；正：右 负：左
	int b;                   //单位时间y轴移动距离；正：下 负：上
};
struct Ball {
	int         x, y;       //坐标
	int         radius;     //半径
	COLORREF    color;      //颜色
	Fx          fx;         //方向
};
//敌对球
vector<Ball> diBalls;
//自己球
Ball myBall;
COLORREF colors[7] = { BLACK,CYAN,GREEN,YELLOW,MAGENTA,BLUE,BROWN };
HWND hWnd;
//检测是否碰撞，是否存活
bool isLive = true; 


//初始化游戏
void initGame();
//游戏界面绘制
void drawGame();
//游戏流程控制
void controlGame();
//定时器处理函数
void proc();
//线程函数，设置自己球随鼠标移动
void setMyBall();
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
	hWnd=initgraph(WIDTH, HEIGHT);	
	//2 敌对球初始化                  定义指针，放在堆中，开内存
	Ball* pb = NULL;
	for (int i = 0; i < NUM; i++) {
		pb = new Ball;
		pb->x = 1;
		pb->y = HEIGHT / 2;
		//半径在1-50之间 随机
		pb->radius = rand() % 50 + 1;
		//颜色在colors的7个颜色中随机
		pb->color = colors[rand() % 7];
		//方向随机
		pb->fx.a = rand() % 5 + 1;
		pb->fx.b = rand() % 10 - 5;
		//把做出来的敌对球放到数组中去
		diBalls.push_back(*pb);
	}

	//3 自己球初始化
	myBall.color = RED;
	myBall.x = 500;
	myBall.y = 500;
	myBall.radius = 5;


}
void drawGame()
{
	//设置定时器，像定个闹钟	
	SetTimer(hWnd, 10086, 100, (TIMERPROC)proc);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)setMyBall, NULL, NULL,NULL);
	while (1) {
		controlGame();
		if (!isLive)break;  //如果不存活，结束	
		BeginBatchDraw();
		//1设置背景
		setbkcolor(WHITE);
		cleardevice();
		//2画自己球
		setfillcolor(myBall.color);
		solidcircle(myBall.x, myBall.y,myBall.radius);
		//3画敌对球
		for ( int i = 0; i < diBalls.size(); i++) {
			setfillcolor(diBalls[i].color);
			solidcircle(diBalls[i].x, diBalls[i].y, diBalls[i].radius);
		}
		EndBatchDraw();
	}
	setbkcolor(RED);
	cleardevice();
	outtextxy(100, 100, L"game over");
}
void controlGame(){ 

	int xLen, yLen;
	//如果有球移动出屏幕，重新生成之
	for (int i = 0; i < diBalls.size(); i++) {
		xLen = (diBalls[i].x > myBall.x) ? (diBalls[i].x - myBall.x) : (myBall.x - diBalls[i].x);
		yLen = (diBalls[i].y > myBall.y) ? (diBalls[i].y - myBall.y) : (myBall.y - diBalls[i].y);
		if ((xLen*xLen + yLen*yLen)<=(myBall.radius + diBalls[i].radius)* (myBall.radius + diBalls[i].radius)){
			//判断myBall和diBalls是否碰撞，如果碰撞，isLive = false;没有碰撞则不操作
			if (myBall.radius < diBalls[i].radius) {
				isLive = false;//圆心距离小于半径之和则碰撞
			}	
			else {//重新生成敌对球并且增加自己球的大小
				diBalls[i].x = 1;
				diBalls[i].y = HEIGHT / 2;
				//半径在1-50之间 随机
				diBalls[i].radius = rand() % 50 + 1;
				//颜色在colors的7个颜色中随机
				diBalls[i].color = colors[rand() % 7];
				//方向随机
				diBalls[i].fx.a = rand() % 5 + 1;
				diBalls[i].fx.b = rand() % 10 - 5;
				if (myBall.radius <= 97)
					myBall.radius += 3;
				
			}
		}
		if (diBalls[i].x > WIDTH || diBalls[i].x < 0 || diBalls[i].y > HEIGHT || diBalls[i].y < 0){
			diBalls[i].x = 1;
			diBalls[i].y = HEIGHT / 2;
			//半径在1-50之间 随机
			diBalls[i].radius = rand() % 50 + 1;
			//颜色在colors的7个颜色中随机
			diBalls[i].color = colors[rand() % 7];
			//方向随机
			diBalls[i].fx.a = rand() % 5 + 1;
			diBalls[i].fx.b = rand() % 10 - 5;
		}
	}

}

void proc() {//循环改坐标 
	for (int i = 0; i < diBalls.size(); i++) {
		diBalls[i].x += diBalls[i].fx.a;
		diBalls[i].y += diBalls[i].fx.b;
	}
}

void setMyBall()
{
	while (1) {
		//获取鼠标坐标
		MOUSEMSG msg = GetMouseMsg();
		//获取鼠标消息，如果没有鼠标消息，就等待
		//然后设置自己球坐标为鼠标坐标 
		if (msg.mkLButton) {
			myBall.x = msg.x;
			myBall.y = msg.y;
		}
	}
}



