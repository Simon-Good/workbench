#pragma once
#include<iostream>
#include<string>
#include<boost\numeric\ublas\matrix.hpp>
#include<boost\numeric\ublas\operation.hpp>
#include<boost\numeric\ublas\io.hpp>
#include"dataEater.h"

#define DATAFROM "verifyData.txt"
#define PTNFROM "verifyPattern.txt"
#define COL 5
#define ROW 6
#define LEN COL*ROW
#define R 3

class verifyThrNum
{
public:
	verifyThrNum(void);
	~verifyThrNum(void);
	void doJob();

private:
	int errorFlag;
	dataEater de;
	matrix<int> inputData;//input data from txt file, each number inmage a line
	matrix<int> mm;//each number image at once
	matrix<int> mt;//transform of mm
	matrix<int> weight;//final weight matrix we need
	matrix<int> ptnData;//pattern matrix
	matrix<int> pattern;//pattern to recognize
	matrix<int> output;//a temp matrix to store result of pattern * weight
	matrix<int> recgPtn;//result of hardline output
};

