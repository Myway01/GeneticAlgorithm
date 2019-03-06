#include "GA2Bus.h"

//产生新个体
population* newpop() {
	population* p = (population*)malloc(sizeof(population));
	p->next = NULL;
	return p;
}
//插入个体操作
void inspopm(population* first, population* p) {
	while (first->next)
		first = first->next;
	first->next = p;
}
//删除种群
void delpopm(population* first) {
	population* next = first->next;
	while (next) {
		free(first);
		first = next;
		next = first->next;
	}
	free(first);
}
void netpro(population* p);//净利润
void fit(population* first);//适应值


void inipopm(population* first, int M) {
	population* p = first;
	population* n;
	srand(time(0));
	while (M--) {
		//第一班车和最后一班车必须发车
		p->isDep[0] = true;
		p->isDep[timetable - 1] = true;
		for (int i = 1; i < timetable - 1; i++) {
			p->isDep[i] = rand() % 3 == 0 ? true : false;//此处可优化？？？
		}
		netpro(p);
		//if (M == 0)
		//for (int i = 0; i < timetable; i++)
		//{
		//	cout << first->isDep[i] << endl;
		//}
		//cout << M << endl;
		if (M == 0) break;
		n = newpop();
		p->next = n;
		p = n;
	}
	fit(first);
}
double gaussrand()
{
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X;
}
int randpa(int t, double ispa) {
	double prob = 0;//分配等待乘客概率
	if (t <= 120) prob = 0.25 * ispa;
	else if (t <= 300) prob = 0.4 * ispa;
	else if (t <= 600) prob = 0.55 * ispa;
	else if (t <= 900) prob = 0.75 * ispa;
	else prob = 0.4 * ispa;
	double x = (double)(rand() % 1001) / 1000;//随机精度为千分之一
	int pa = 0;
	if (x < prob) {
		while (pa <= 0)
			pa = gaussrand() * 2 + 1;//方差为2，期望为1的正态分布
	}
	return pa;
}
void netpro(population* p) {
	double w = 0, pc = 0, cc = 0;//收益、乘客等待成本、发车成本
	for (int i = 0;i < N;i++) {
		int num_p = 0;//乘客数目
		int index_time = 0;
		for (int j = 1 - mininter;j < timetable * mininter;j++) {
			pc += pcost * num_p;
			num_p += randpa(j + arrtime[i], ispassenger[i]);
			if (j % mininter == 0) {
				if (p->isDep[index_time] == true) {
					w += (num_p * fare);
					num_p = 0;
				}
				index_time += 1;
			}
		}
	}
	for (int i = 0;i < timetable;i++) {
		if (p->isDep[i] == true) cc += ccost;
	}
	p->np = w - pc - cc;
}
void fit(population* first) {
	double max = first->np, min = first->np, sum = 0;
	population* p = first;
	while (p) {
		if (p->np > max) max = p->np;
		if (p->np < min) min = p->np;
		p = p->next;
	}
	p = first;
	while (p) {
		p->fitness = pow(((p->np - min) / (max - min) + 0.0001), m);
		p = p->next;
	}
	p = first;
	while (p) {
		sum += p->fitness;
		p = p->next;
	}
	p = first;
	while (p) {
		p->fitness = p->fitness / sum;
		p = p->next;
	}
}

population* select(population* first) {
	population* selpopm = newpop();
	*selpopm = *first;
	population* p = first;
	double max_fitness = first->fitness;
	//保留最大适应度个体
	while (p) {
		if (p->fitness > max_fitness) {
			*selpopm = *p;
			max_fitness = p->fitness;
		}
		p = p->next;
	}
	p = first;
	srand(time(0));
	population* selp = selpopm;
	while (p) {
		if (p->fitness > double(rand() % 1001) / 1000 * 0.1) {
			population* s = newpop();
			*s = *p;
			selp->next = s;
			selp = s;
		}
		p = p->next;
	}
	selp->next = NULL;
	delpopm(first);
	return selpopm;
}

population* exchange(population* first, int a, int b, int min, int max) {
	population* A = newpop();
	population* B = newpop();
	population* p = first;
	int index = 0;
	while (p) {
		if (index == a) {
			for (int i = 0; i < min; i++) {
				A->isDep[i] = p->isDep[i];
			}
			for (int i = min; i < max; i++) {
				B->isDep[i] = p->isDep[i];
			}
			for (int i = max; i < timetable; i++) {
				A->isDep[i] = p->isDep[i];
			}
		}
		if (index == b) {
			for (int i = 0; i < min; i++) {
				B->isDep[i] = p->isDep[i];
			}
			for (int i = min; i < max; i++) {
				A->isDep[i] = p->isDep[i];
			}
			for (int i = max; i < timetable; i++) {
				B->isDep[i] = p->isDep[i];
			}
		}
		index++;
		p = p->next;
	}
	netpro(A);
	netpro(B);
	A->next = B;
	return A;
}
void cross(population* first) {
	population* p = first;
	int num_popm = 0;
	srand(time(0));
	while (p) {
		num_popm += 1;
		p = p->next;
	}
	for (int i = 0; i < Pc * num_popm; i++) {
		int a = rand() % num_popm;
		int b = rand() % num_popm;
		while (b == a) b = rand() % num_popm;
		int m = rand() % timetable;
		int n = rand() % timetable;
		while (n == m) n = rand() % timetable;
		if (n < m) {
			int e = m; m = n; n = e;
		}
		p = exchange(first, a, b, m, n);
		inspopm(first, p);
	}
}

void mutation(population* first) {
	population* p = first;
	srand(time(0));
	while (p) {
		if ((double)(rand() % 1001) / 1000 < Pmutation) {
			int n = 1 + rand() % (int)(timetable / 10);//最多%10基因突变
			for (int i = 0; i < n; i++) {
				int index = 1 + rand() % (timetable - 2);
				p->isDep[index] = (p->isDep[index] == true ? false : true);
			}
			netpro(p);
		}
		p = p->next;
	}
}

population* findmax(population* first) {
	population* p = first;
	population* max = first;
	double max_fitness = first->fitness;
	while (p) {
		if (p->fitness > max_fitness) {
			max_fitness = p->fitness;
			max = p;
		}
		p = p->next;
	}
	return max;
}