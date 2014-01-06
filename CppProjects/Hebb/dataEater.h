#pragma once
#include<boost\filesystem.hpp>
#include<boost\filesystem\path.hpp>
#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\io.hpp>

#define DATAFROM "vectorData.txt"
#define PATTERNFROM "pattern.txt"
#define COL 5
#define ROW 6
#define LEN COL*ROW
#define R 10

using namespace std;
using namespace boost::numeric::ublas;

class dataEater
{
public:
	dataEater(void);
	~dataEater(void);
	void coldDish(matrix<int> &inputData);
};

