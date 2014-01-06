#pragma once
#include<iostream>
#include<string>
#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\operation.hpp>
#include<boost\numeric\ublas\io.hpp>
#include<boost\numeric\ublas\lu.hpp>
#include"dataEater.h"
#include <math.h>

#define ADVDATAFROM "advData.txt"
#define ADVTARGFROM "advTarget.txt"
#define ADVPTNFROM "advPattern.txt"
#define ADVCOL 5
#define ADVROW 6
#define ADVLEN ADVCOL*ADVROW
#define ADVR 10
class numToLet
{
public:
	numToLet(void);
	~numToLet(void);
	void doMapping();
	void makeMPMatrix(matrix<double>& mt, matrix<double>& mtMp);

	template<class T>
	bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse);
	template<class T> 
	int getSign(T num);
private:
	int errorFlag;
	dataEater de;
	matrix<double> inputData;
	matrix<double> inputDataMP;
	matrix<double> targetPtn;
	matrix<double> targetPtnT;
	matrix<double> weight;
	matrix<double> inputPtn;
	matrix<double> pattern;
	matrix<double> output;
	matrix<double> recgPtn;
};

template<class T>
bool numToLet::InvertMatrix(const matrix<T>& input, matrix<T>& inverse){
	using namespace boost::numeric::ublas;
    typedef permutation_matrix<std::size_t> pmatrix;
    // create a working copy of the input
    matrix<T> A(input);
    // create a permutation matrix for the LU-factorization
    pmatrix pm(A.size1());

    // perform LU-factorization
    int res = lu_factorize(A,pm);
    if( res != 0 ) return false;

    // create identity matrix of "inverse"
    inverse.assign(identity_matrix<T>(A.size1()));
	
    // backsubstitute to get the inverse
    lu_substitute(A, pm, inverse);

    return true;
}

template<class T>
int numToLet::getSign(T num){
	if(num > 0)
		return 1;
	else if(num < 0)
		return -1;
}



