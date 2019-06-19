/*
 * @Author : Alexandre Behling        - 13200626
 * @Author : Gustavo Tarciso da Silva - 14100833
 */

#include "tests.h"
#include <iostream>

using namespace std;

Test::Test() {
	this->_stat = new Statistic();
}

Test::Test(Statistic *stat) {
	this->_stat = stat;
}

void Test::run(){
	int tests_passed = 0;
	tests_passed += testNumElements();
	tests_passed += testMin();
	tests_passed += testMax();
	tests_passed += testAverage();
	tests_passed += testVariance();
	tests_passed += testStdVar();
	tests_passed += testVarcoef();
	tests_passed += testHalfWidthConfInterval();
	tests_passed += testNewSampleSize();

	cout << "Passed in " << (tests_passed)*100/9 <<"% of the tests" << endl;
}

int Test::testNumElements(){
	cout << "Test: Number of elements in sample" << endl;

	if(this->_stat->numElements() == _n_e) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "N: " << this->_stat->numElements() << endl;
		cout << "Should be: " << _n_e << "\n" << endl;
		return 0;
	}

}

int Test::testMin(){
	cout << "Test: Min element value in sample" << endl;

	if(this->_stat->min() == _min_e) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Min: " << this->_stat->min() << endl;
		cout << "Should be: " << _min_e << "\n" << endl;
		return 0;
	}

}

int Test::testMax(){
	cout << "Test: Max element value in sample" << endl;

	if(this->_stat->max() == _max_e) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Max: " << this->_stat->max() << endl;
		cout << "Should be: " << _max_e << "\n" << endl;
		return 0;
	}

}

int Test::testAverage(){
	cout << "Test: Sample mean" << endl;

	// the max error possible
	double _err = _avg_e * _error_max;

	if(this->_stat->average() >= _avg_e - _err && this->_stat->average() <= _avg_e + _err) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Mean: " << this->_stat->average() << endl;
		cout << "Should be: " << _avg_e << "\n" << endl;
		return 0;
	}

}

int Test::testVariance(){
	cout << "Test: Sample variance" << endl;

	double _err = _var_e * _error_max;

	if(this->_stat->variance() >= _var_e - _err && this->_stat->variance() <= _var_e + _err) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Variance: " << this->_stat->variance() << endl;
		cout << "Should be: " << _var_e << "\n" << endl;
		return 0;
	}

}

int Test::testStdVar(){
	cout << "Test: Sample Standard deviation" << endl;

	double _err = _std_var_e * _error_max;

	if(this->_stat->stddeviation() >= _std_var_e - _err && this->_stat->stddeviation() <= _std_var_e + _err) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Standard deviation: " << this->_stat->stddeviation() << endl;
		cout << "Should be: " << _std_var_e << "\n" << endl;
		return 0;
	}

}

int Test::testVarcoef(){
	cout << "Test: Sample coefficient of variation" << endl;

	double _err = _var_coef_e * _error_max;

	if(this->_stat->variationCoef() >= _var_coef_e - _err && this->_stat->variationCoef() <= _var_coef_e + _err) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Coefficient of variation: " << this->_stat->variationCoef() << endl;
		cout << "Should be: " << _var_coef_e << "\n" << endl;
		return 0;
	}

}

int Test::testHalfWidthConfInterval(){
	cout << "Test: Sample half width confidence interval" << endl;

	double _err = _hf_wid_e * _error_max;
	double _coef = this->_stat->halfWidthConfidenceInterval(_conf_test);

	if(_coef >= _hf_wid_e - _err && _coef <= _hf_wid_e + _err) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "Half width interval: " << this->_stat->halfWidthConfidenceInterval(_conf_test) << endl;
		cout << "Should be: " << _hf_wid_e << "\n" << endl;
		return 0;
	}

}

int Test::testNewSampleSize(){
	cout << "Test: New sample size" << endl;

	double _new_sample = this->_stat->newSampleSize(_conf_test, _hw_test);

	if(_samp_size_e == _new_sample) {
		cout << "Passed\n" << endl;
		return 1;
	} else {
		cout << "Failed\n" << "New sample size: " << this->_stat->newSampleSize(_conf_test, _hw_test) << endl;
		cout << "Should be: " << _samp_size_e << "\n" << endl;
		return 0;
	}

}
