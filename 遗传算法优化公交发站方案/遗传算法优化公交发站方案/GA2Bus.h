#ifndef _GA2Bus_
#define _GA2Bus_
#include "GA.h"
#define timetable 209 //发站时间表（最小间隔5分钟，共有209个发车时间点，但第一班车和最后一班车必须发车）
#define mininter 5 //最小发车间隔时间

static int N = 18;//站点数
static int M = 50;//初始种群数
static int C = 1000;//迭代次数（与程序运行时间二选一，控制算法结束）
static int T = 30;//程序运行时间
static int m = 2.5;//适应值归一化淘汰加速指数
static double Pc = 0.6;//交叉概率
static double Pmutation = 0.15;//变异概率

static double pcost = 53187.0 / (365 * 24 * 60);//每位乘客等待每分钟的成本
static double ccost = 150;//每趟车成本
static int fare = 2;//车费

//公交到站时间表
static int arrtime[18] = { 0, 1, 3, 4, 8, 10, 11, 14, 17, 19, 21, 22, 24, 26, 28, 34, 39, 45 };
//各站的每分钟是否进行分配到站等待乘客的概率因子
static double ispassenger[18] = { 0.3, 0.8, 0.4, 0.4, 0.4, 0.6, 0.6, 0.7, 0.5, 0.6, 0.8, 0.5, 0.4, 0.4, 0.4, 0.3, 0.3, 0.3 };

//个体染色体结构
struct population {
	struct population* next = NULL;
	bool isDep[timetable];//发站时间表
	double fitness;//适应度
	double np;//净利润
};

population* newpop();//产生新个体
void inspopm(population* first, population* p);//插入个体操作
void delpopm(population* first);//删除种群

void netpro(population* p);//净利润
void fit(population* first);//适应值

void inipopm(population* first, int M);//初始化种群
double gaussrand();//产生正态分布随机数
int randpa(int t, double ispa);//随机分配等待乘客
void netpro(population* p);//计算净利润
void fit(population* first);//计算适应值
population* select(population* first);//选择
population* exchange(population* first, int a, int b, int min, int max);//交换染色体
void cross(population* first);//交叉操作
void mutation(population* first);//变异操作
population* findmax(population* first);//寻找最优解操作

#endif

