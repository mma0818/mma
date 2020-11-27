#include <iostream>
#include <ctime>
using namespace std;
const double pi = 3.141592653589793;
const int Size = 50;
const double pcross = 0.850;
const double pmutate = 0.050;
const int G = 500;
const int length = 22;
double bestval;
typedef struct node {
	bool chromo[length];
}node;
node bestchromo;
node group[Size];
node temp[Size];
void gouzao(node& c) {
	for (int i = 0; i < length; i++) {
		c.chromo[i] = rand() % 2;
	}
}
void decode(node& c, double& x) {
	double num = 4194394;
	double tem = 0;
	for (int i = 0; i < length;i++) {
		tem += c.chromo[i] * pow(2, i);
	}
	x = (3 / num * tem) - 1.0;
}
double f(double x) {
	return x * sin(10 * pi * x) + 2.0;
}
double fitness(node& c) {
	double x;
	decode(c, x);
	return f(x);
}
void cross(node& c1, node& c2, int point) {
	node c3 = c1;
	for (int i = 0; i < length - point; i++) {
		c1.chromo[point + i] = c2.chromo[point + i];
	}
	for (int j = 0; j < length - point; j++) {
		c2.chromo[point + j] = c3.chromo[point + j];
	}
}
void mutate(node& c) {
	int i = rand() % length;
	c.chromo[i] = !c.chromo[i];
}
double inline rand0() {
	return rand() % 10000 / 10000.0;
}
void select(node group[Size]) {
	double fitnessval[Size];
	double sum = 0;
	double avgfitness[Size];
	int id[Size];
	for (int i = 0; i < Size; i++) {
		fitnessval[i] = fitness(group[i]);
	}
	for (int i = 0; i < Size; i++) {
		sum += fitnessval[i];
	}
	for (int i = 0; i < Size; i++) {
		avgfitness[i] = fitnessval[i] / sum;
	}
	for (int i = 1; i < Size; i++) {
		avgfitness[i] += avgfitness[i - 1];
	}
	for (int i = 0; i < Size; i++) {
		double rannum = rand0();
		int j;
		for (j = 0; j < Size - 1; j++) {
			if (rannum < avgfitness[j]) {
				id[i] = j;
				break;
			}
		}
		if (j == Size - 1) {
			id[i] = j;
		}
	}
	for (int i = 0; i < Size; i++) {
		temp[i] = group[i];
	}
	for (int i = 0; i < Size; i++) {
		group[i] = temp[id[i]];
	}
}
int getBest(node group[Size], double& x, double& number) {
	double fitnessval[Size];
	for (int i = 0; i < Size; i++) {
		fitnessval[i] = fitness(group[i]);
	}
	int id = 0;
	for (int i = 1; i < Size; i++) {
		if (fitnessval[i] > fitnessval[id]) {
			id = i;
		}
	}
	decode(group[id], x);
	number = f(x);
	return id;
}
void GA(double& x, double& number) {
	for (int i = 0; i < Size; i++) {
		gouzao(group[i]);
	}
	bestchromo = group[getBest(group, x, bestval)];
	for (int i = 0; i < G; i++) {
		select(group);
		int p = rand() % length;
		for (int j = 0, pre = -1; j < Size; j++) {
			if (rand0() < pcross) {
				if (pre == -1)
					pre = j;
				else {
					cross(group[pre], group[j], p);
					pre = -1;
				}
			}
		}
		for (int k = 0, pre = -1; k < Size; k++) {
			if ((rand0() < pmutate)) {
				mutate(group[k]);
			}
		}
		getBest(group, x, number);
		cout << "µü´ú´ÎÊý" << i + 1<<  " " " " " " << "x=" << x <<" "" "" ""f(x)=" << f(x) << endl;
	}
}
int main() {
	srand((unsigned)time(0));
	double x;
	double max;
	GA(x, max);
	system("pause");
	return 0;
}