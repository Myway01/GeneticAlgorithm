#ifndef _GA2Bus_
#define _GA2Bus_
#include "GA.h"
#define timetable 209 //��վʱ�����С���5���ӣ�����209������ʱ��㣬����һ�೵�����һ�೵���뷢����
#define mininter 5 //��С�������ʱ��

static int N = 18;//վ����
static int M = 50;//��ʼ��Ⱥ��
static int C = 1000;//�������������������ʱ���ѡһ�������㷨������
static int T = 30;//��������ʱ��
static int m = 2.5;//��Ӧֵ��һ����̭����ָ��
static double Pc = 0.6;//�������
static double Pmutation = 0.15;//�������

static double pcost = 53187.0 / (365 * 24 * 60);//ÿλ�˿͵ȴ�ÿ���ӵĳɱ�
static double ccost = 150;//ÿ�˳��ɱ�
static int fare = 2;//����

//������վʱ���
static int arrtime[18] = { 0, 1, 3, 4, 8, 10, 11, 14, 17, 19, 21, 22, 24, 26, 28, 34, 39, 45 };
//��վ��ÿ�����Ƿ���з��䵽վ�ȴ��˿͵ĸ�������
static double ispassenger[18] = { 0.3, 0.8, 0.4, 0.4, 0.4, 0.6, 0.6, 0.7, 0.5, 0.6, 0.8, 0.5, 0.4, 0.4, 0.4, 0.3, 0.3, 0.3 };

//����Ⱦɫ��ṹ
struct population {
	struct population* next = NULL;
	bool isDep[timetable];//��վʱ���
	double fitness;//��Ӧ��
	double np;//������
};

population* newpop();//�����¸���
void inspopm(population* first, population* p);//����������
void delpopm(population* first);//ɾ����Ⱥ

void netpro(population* p);//������
void fit(population* first);//��Ӧֵ

void inipopm(population* first, int M);//��ʼ����Ⱥ
double gaussrand();//������̬�ֲ������
int randpa(int t, double ispa);//�������ȴ��˿�
void netpro(population* p);//���㾻����
void fit(population* first);//������Ӧֵ
population* select(population* first);//ѡ��
population* exchange(population* first, int a, int b, int min, int max);//����Ⱦɫ��
void cross(population* first);//�������
void mutation(population* first);//�������
population* findmax(population* first);//Ѱ�����Ž����

#endif

