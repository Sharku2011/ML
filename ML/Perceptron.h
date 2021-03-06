#pragma once
#include <iostream>
#include <vector>

#define SMALL_NUMBER 1e-9
#define MAX2(a,b) ((a) > (b) ? (a) : (b))

using namespace std;

class Graph;

#ifndef SHARKU
#define SHARKU
template <class T>
static vector<T>& operator<<(vector<T>& v, T d) { v.push_back(d); return v; };

template <class T>
static T& operator<<(T& d, vector<T>& v) { d = v.back(); return d; };
#endif //SHARKU

class Perceptron
{

public:

	size_t InputSize;
	
	vector<double> Weight; // weight of one input
	double Bias;		// bias

	vector<double> Input;
	double Output;

protected:

private:

public:

	Perceptron() : InputSize(0), Weight(vector<double>()), Bias(0.0) {};
	Perceptron(vector<double> NewWeight, double NewBias) : Weight(NewWeight), Bias(NewBias) { InputSize = NewWeight.size(); };

	double FeedForward(const vector<double> NewInput);

	double GetActivation(double&& X);

	double GetActivationGrad(double&& X, double(*pFunc)(const double&));
	double GetActivationGrad(double X, double(*pFunc)(double&&));

	void PropBackward(const double& Target, const double& LearningRate = 0.1);
	void PropBackward(const double& Target, double&& LearningRate = 0.1);
	void PropBackward(double&& Target, double&& LearningRate = 0.1);

	static double Sigmoid(double&& x) { return 1 / (1 + exp(-x)); };
	static double ReLU(double&& x) { return MAX2(0, x); };
	static double Correlation(double&& Sxx, double&& Sxy, double&& Syy) { return Sxy / (sqrt(Sxx)*sqrt(Syy)); };

	static double Sxx(const Graph& G);

	friend ostream& operator<<(ostream& c, const Perceptron& P);

	

protected:

private:

};


