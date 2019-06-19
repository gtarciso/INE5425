/*
 * @Author : Alexandre Behling        - 13200626
 * @Author : Gustavo Tarciso da Silva - 14100833
 */

#include "tests.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	Statistic *stat = new Statistic();
	int n;
	double x;
	cout << "Insert data amount" << endl;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cout << "Insert new data" << endl;
		cin >> x;
		stat->addValue(x);
	}

	cout << endl;

	Test *t = new Test(stat);
	t->run();

	double halfwidth = stat->halfWidthConfidenceInterval(0.95);

	return 0;

}