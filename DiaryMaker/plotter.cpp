#include "plotter.h"

Plotter::Plotter()
{
    windowSize = 1;
}

int Plotter::smooth0(QVector<double>& inp, QVector<double>& out)
{
    int size = windowSize < (inp.size()/4) ? windowSize : inp.size()/4;
    if (size == 1) {
        out = inp;
        return 0;
    }
    if (size % 2)
        size += 1;

    double sum = 0.0;
    for ( int i = 0 ; i < size ; i ++ ) {
        sum += inp[i];
    }
    out.push_back(sum/size);

    for ( int i = size ; i < inp.size() ; i ++ ) {
        sum = sum + inp[i] - inp[i-size];
        out.push_back(sum/size);
    }
    return 0;
}

double getMean(QVector<double> values)
{
        double sum = 0.0;
        for (int i = 0 ; i < values.size() ; i ++ ) {sum+= values[i];}
        return sum / values.size();
}

double getDeviation(QVector<double> values, double mean)
{
        double devSqr = 0.0;
        for (int i = 0 ; i < values.size() ; i ++ ) {devSqr += SQR(values[i]-mean);}
        // TODO: return squareRoot of the following
        return devSqr / values.size();
}

int Plotter::smooth1(QVector<double>& inp, QVector<double>& out)
{
    int size = windowSize < (inp.size()/4) ? windowSize : inp.size()/4;
    if (size == 1) {
        out = inp;
        return 0;
    }
    if (size % 2)
        size += 1;

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
