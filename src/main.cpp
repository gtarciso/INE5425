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

/*
	cout << "N: " << stat->numElements() << endl;
	cout << "Média: " << stat->average() << endl;
	cout << "Variancia: " << stat->variance() << endl;
	cout << "Desvio padrão: " << stat->stddeviation() << endl;
	cout << "Max: " << stat->max() << endl;
	cout << "Min: " << stat->min() << endl;
	cout << "Coeficiente de variação: " << stat->variationCoef() << endl;
	cout << "Intervalo de confiança: " << stat->halfWidthConfidenceInterval(0.95) << endl;
	cout << "Tamanho da amostra: " << stat->newSampleSize(0.95, 4) << endl; // testando com o dobro do intervalo de confiança

*/
	return 0;

}