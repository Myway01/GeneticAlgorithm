#include "GA2Bus.h"

using namespace std;

/////////���в�����������GA2Bus.h�ļ�������/////////
int main() {
	//��ʼ������
	time_t start, end;
	double dif = 0;
	int num = 0;//��������
	time(&start);
	population* popm = newpop();
	inipopm(popm, M);
	population* max = NULL;
	int n = C;
	while (dif <= T) {
		popm = select(popm);//ѡ��
		cross(popm);//����
		mutation(popm);//����
		fit(popm);//������Ӧ��
		max = findmax(popm);//Ѱ�����Ÿ���
		if (num % 5 == 0)  //�������ֵ��Ƶ��
			cout << "������" << max->np << '\t' << "fitnes��" << max->fitness << endl;
		time(&end);
		dif = difftime(end, start);
		num++;
	}
	//�������ʱ���
	cout << "����ʱ���" << endl;
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
	cout << endl << "����ʱ�䣺" << dif << "s" << endl << "����������" << num << endl << "��������" << max->np << endl;
	cout << "��������˳�..." << endl << endl << endl << endl << endl;
	getchar();
}
