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
#include <cassert>
#include <cmath>

#define SQR(x) ((x)*(x))
#define ABS(x) (x)>0?(x):(-x)
#define LARGE 100000000000000.0

using namespace std;

int mode = 0;
int size = 20;
int tresh = 10;
int kVal = 9;

// Inputs a vector
int getInput(vector<double>& inp)
{
	double x;
	while (cin >> x) {
		inp.push_back(x);
	}
	return 0;
}

// Outputs a vector
int printOutput(vector<double>& inp)
{
	for ( int i = 0 ; i < inp.size() ; i ++) {
		cout << inp[i] << endl;
	}
	return 0;
}

// Gets the mean of all values in a vector
double getMean(vector<double> values)
{
	double sum = 0.0;
	for (int i = 0 ; i < values.size() ; i ++ ) {sum+= values[i];}
	return sum / values.size();
}

// gets the standard deviation of a vector
double getDeviation(vector<double>& values, double mean)
{
	double devSqr = 0.0;
	for (int i = 0 ; i < values.size() ; i ++ ) {devSqr += SQR(values[i]-mean);}
	return sqrt(devSqr / values.size());
}

// Returns the smoothed points of a vector
int smooth1(vector<double>& inp, vector<double>& out)
{
	double sum = 0.0;
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
	return 0;
}

// Quantizes a vector and returns quantisation levels
int quantise(vector<double>& values, vector<double>& quant, double mean, double dev, int kVal)
{
	vector<double> clusters;

	for ( int i = 0 ; i < values.size() ; i ++ ) {
		quant.push_back(mean);
	}
	// define cluser medians
	if (kVal%2) {
		clusters.push_back(mean);
		double part = 4*dev/(kVal-1);
		for ( int i = 1 ; i <= (kVal-1)/2 ; i ++ ) {
			clusters.push_back(mean+i*part);
			clusters.push_back(mean-i*part);
		}
	} else {
		double part = 4*dev/(kVal);
		for (int i = 1 ; i <= kVal/2 ; i ++ ) {
			clusters.push_back(mean+i*part);
			clusters.push_back(mean-i*part);
		}
	}

	// Start the quantisation ( Each point is mapped to the closest level )
	for (int k = 0 ; k < values.size() ; k ++ ) {
		double min = LARGE;
		int index = 0;
		for (int j = 0 ; j < kVal ; j ++ ) {
			double diff = ABS(clusters[j]-values[k]);
			if( diff < min) {
				min = diff;
				index = j;
			}
		}
		quant[k] = clusters[index];
	}
	return 0;
}

// Expands a compressed array of <val, freq> to val, val, val ... (freq times)
// And performs a few minor modifications to remove spikes

int expand(vector<double>& val, vector<double>& count, vector<double>& expand)
{
	// Remove all the spikes (small intervals of differences)
	for(int i = 0 ; i < val.size() ; i ++ ) {
		if (count[i] < tresh) {
			if (i == 0 && i+1 < val.size()) {
				if (count[i+1] > count[i]) {
					val[i] = val[i+1];
				}
			} else if (i == val.size() - 1 && i > 0 ) {
				if (count[i-1] > count[i]) {
					val[i] = val[i-1];
				}
			} else {
				if (val[i+1] > val[i-1] && val[i+1]>val[i])
					val[i] = val[i+1];
				else if (val[i+1] <= val[i-1] && val[i-1]>val[i])
					val[i] = val[i-1];
			}
		}
	}
	for(int i = 0 ; i < val.size() ; i ++ ) {
		for (int j = 0 ; j < count[i] ; j ++ )
			expand.push_back(val[i]);
	}
	return 0;
}

int fixQuants(vector<double>& smooth, vector<double>& quant, vector<double>& outAv, vector<double>& outCo)
{
	// This function shrinks the quantisation level array to an array of average, count
	// a series of continuous points corresponding to the same quantisation level in input array
	// shrinks into a single point in the output array.	
	int i = 0;
	while(1) {
		double sum = 0.0;
		int count = 0;
		double type;

		if (i==smooth.size()) break;					// If done, break out
		else type = quant[i];							// get the next type
		while(i<smooth.size()) {						// while we have more datapoints
			if(quant[i] == type) {						// while we still have the same type
				sum += smooth[i];						// get sum (needed for averages)
				count ++;								// get the number of such types
				i ++;									// increment the counter
			} else {
				 break;									// Next type
			}
		}
		outAv.push_back(sum/count);						// Push the averages into the output array
		outCo.push_back(count);							// Push the counts into the output array
	}
	return 0;
}


int main(int argc, char** argv)
{
	vector<double> values;
	vector<double> smooth;
	vector<double> quants ;
	vector<double> averages;

	if (argc > 1) {
		size = atoi(argv[1]);
		if (size < 1 || size > 100)
			size = 10;
	} else if (argc > 2) {
		tresh = atoi(argv[2]);
		if (tresh < 5 || tresh > 50)
			tresh = 10;
	}
	
	
	getInput(values);									// Get Input
	smooth1(values, smooth);							// Smooth the input
	double mean = getMean(values);						// Get mean of the values
	double dev = getDeviation(values, mean);			// Get SD of smoothed values
	dev = dev > 2*mean ? dev : mean/2;					// Modify SD to suit quantize algo
	quantise(smooth, quants, mean, dev, kVal);				// Quantise the smoothed values
	assert(smooth.size()==quants.size());
	vector<double> outAv;								
	vector<double> outCo;
	fixQuants(smooth, quants, outAv, outCo);
	expand(outAv, outCo, averages);
	// printOutput(smooth);
	printOutput(averages);
}
