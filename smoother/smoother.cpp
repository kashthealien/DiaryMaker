/***************************************************************************************************
 * Author  : Kashyap R Puranik (kashthealien at gmail dot com)
 * Date    : 26/12/2010
 * 
 * Purpose : Takes numerical data as input and smooths the data for plotting
 * Compile : g++ smoother.cpp -o smoother
 * usage   : ./smoother <smoothing-mode> <window-size> < <input-data-file>
 * example : ./smoother 0 10 < plotData.csv
 *
 **************************************************************************************************/

#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

int getInput(vector<float>& inp)
{
	float x;
	while (cin >> x) {
		inp.push_back(x);
	}
	return 0;
}

int printOutput(vector<float>& inp)
{
	for ( int i = 0 ; i < inp.size() ; i ++) {
		cout << inp[i] << endl;
	}
	return 0;
}

vector<float> smooth0(vector<float>& inp, int size)
{
	vector<float> out;
	float sum = 0.0;
	for ( int i = 0 ; i < size ; i ++ ) {
		sum += inp[i];
	}
	out.push_back(sum/size);

	for ( int i = size ; i < inp.size() ; i ++ ) {
		sum = sum + inp[i] - inp[i-size];
		out.push_back(sum/size);
	}
	return out;
}

vector<float> smooth1(vector<float>& inp, int size)
{
	vector<float> out;
	float sum = 0.0;
	for ( int i = 0 ; i <= size ; i ++ ) {
		sum += inp[i];
		if (i>size/2) {
			out.push_back(sum/(i+1));
		}
	}

	for ( int i = size ; i < inp.size() ; i ++ ) {
		sum = sum + inp[i] - inp[i-size];
		out.push_back(sum/size);
	}
	
	for ( int i = inp.size() ; i <= inp.size() + size/2 ; i ++ ) {
		sum -= inp[i-size];
		out.push_back(sum/(inp.size() + size - i - 1));
	}
	return out;
}

int main(int argc, char** argv)
{
	int mode = 0;
	int size = 10;
	vector<float> values;
	vector<float> smooth;

	if (argc > 1) {
		mode = atoi(argv[1]);
		if (mode < 0 || mode > 1)
			mode = 0;
	}
	if (argc > 2) {
		size = atoi(argv[2]);
		if (size < 1 || size > 100)
			size = 10;
	}
	
	getInput(values);
	
	switch(mode) {
		case 0:
			smooth = smooth0(values, size);
			break;
		default:
			smooth = smooth1(values, size);
			break;
	}
	// cout << "size: " << smooth.size() << endl;
	printOutput(smooth);
}
