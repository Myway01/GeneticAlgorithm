#include "GA2Bus.h"

using namespace std;

/////////所有参数均可以在GA2Bus.h文件中设置/////////
int main() {
	//初始化操作
	time_t start, end;
	double dif = 0;
	int num = 0;//迭代次数
	time(&start);
	population* popm = newpop();
	inipopm(popm, M);
	population* max = NULL;
	int n = C;
	while (dif <= T) {
		popm = select(popm);//选择
		cross(popm);//交叉
		mutation(popm);//变异
		fit(popm);//计算适应度
		max = findmax(popm);//寻找最优个体
		if (num % 5 == 0)  //输出过程值的频率
			cout << "净利润：" << max->np << '\t' << "fitnes：" << max->fitness << endl;
		time(&end);
		dif = difftime(end, start);
		num++;
	}
	//输出发车时间表
	cout << "发车时间表：" << endl;
	for (int i = 0; i < timetable; i++) {
		if (max->isDep[i] == true) {
			int h = 5 + i / 12;
			int m = (i % 12) * 5;
			if (h < 10)cout << '0' << h;
			else cout << h;
			cout << ':';
			if (m < 10)cout << '0' << m;
			else cout << m;
			cout << '\t';
		}
	}
	cout << endl << "运行时间：" << dif << "s" << endl << "迭代次数：" << num << endl << "最优利润：" << max->np << endl;
	cout << "按任意键退出..." << endl << endl << endl << endl << endl;
	getchar();
}
