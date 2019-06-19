/*
 * @Author : Alexandre Behling        - 13200626
 * @Author : Gustavo Tarciso da Silva - 14100833
 */

#include "statistic.h"

using namespace std;

// Expected values from tests
#define _n_e 40
#define _min_e 0.54043445
#define _max_e 89.09853855
#define _avg_e 49.0614254905
#define _var_e 727.5139177777
#define _std_var_e 26.97246592
#define _var_coef_e 0.5497693076
#define _hf_wid_e 8.358700193
#define _samp_size_e  175
#define _hw_test 4.0
#define _conf_test 0.95

// 0.00000001% de erro
#define _error_max 0.0000000001

class Test {
private:
	// Statistics object
	Statistic *_stat;

public:
	Test();
	Test(Statistic *stat);
	void run();
	int testNumElements();
	int testMin();
	int testMax();
	int testAverage();
	int testVariance();
	int testStdVar();
	int testVarcoef();
	int testHalfWidthConfInterval();
	int testNewSampleSize();
};