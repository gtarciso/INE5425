class Statistic;

using namespace std;

class Statistic {
private:
	unsigned int _n;
	double _avg;
	long double _avg_sum;
	double _min;
	double _max;
	double _variance;
	long double _variance_sum;
	double _stddev;

public:
	Statistic();
	void addValue(double value); // insere um novo dado, a partir do qual as estatísticas são atualizadas
	void clear(); // limpa os dados e estatísticas
	unsigned int numElements();
	double min();
	double max();
	double average();
	double variance();
	double stddeviation();
	double variationCoef();
	double halfWidthConfidenceInterval(double confidencelevel);
	unsigned int newSampleSize(double confidencelevel, double halfWidth);
	double calculateZ(double confidencelevel); // da pra sumir com isso
	double erf_inv(double x);

};