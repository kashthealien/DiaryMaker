#ifndef PLOTTER_H
#define PLOTTER_H
#include <QVector>

#define MAX_WINDOW_SIZE 50
#define SQR(x) ((x)*(x))
#define ABS(x) (x)>0?(x):(-x)
#define LARGE 100000000000000.0

class Plotter
{
public:
    Plotter();
    int smooth0(QVector<double>& in, QVector<double>& out);
    int smooth1(QVector<double>& in, QVector<double>& out);
    int setWindowSize(int value)
    {if (value > 1 && value < MAX_WINDOW_SIZE+1) {windowSize = value;} return 0;}
private:
    int windowSize;


};

#endif // PLOTTER_H
