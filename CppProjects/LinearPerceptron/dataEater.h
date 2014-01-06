#pragma once
#include <string>
#include <iomanip>
#include <boost\filesystem.hpp>
#include <boost\filesystem\path.hpp>
#include <boost\numeric\ublas\matrix.hpp>
#include <boost\numeric\ublas\io.hpp>
//#define COL 5
//#define ROW 6
//#define LEN COL*ROW
//#define R 10

using namespace std;
using namespace boost::numeric::ublas;

class dataEater
{
public:
	dataEater(void);
	~dataEater(void);
	template<class T>
	void print2Matrix(int col, matrix<T> &inputData);
	template<class T>
	void coldDish(matrix<T> &inputData, int len, int row, string filename);
};



