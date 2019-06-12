//#include "statistic.h"
#include "tests.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	Statistic *stat = new Statistic();
	int n;
	double x;
	cout << "Insira a quantidade de dados" << endl;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cout << "Insira um novo dado" << endl;
		cin >> x;
		stat->addValue(x);
	}

	cout << endl;

	Test *t = new Test(stat);
	t->run();

	double halfwidth = stat->halfWidthConfidenceInterval(0.95);

	return 0;

}