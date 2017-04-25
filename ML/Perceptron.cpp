#include "Perceptron.h"
#include <gsl\gsl>
#include <cmath>
#include "EnumLibrary.h"
#include "BaseNode.h"

double Perceptron::FeedForward(const vector<double> NewInput)
{

	double Sigma = 0.0;

	Input = NewInput;

	if (InputSize == NewInput.size())
	{
		for (size_t i = 0; i < InputSize; ++i)
		{
			Sigma += Weight[i] * Input[i];
		}
		Sigma += Bias;

		Output = GetActivation(std::move(Sigma));

		return Output;
	}

	return -1.0;
}

double Perceptron::GetActivation(double&& X)
{
	// for linear or identity activation function
	return X;

	// for ReLU activation function
	//return MAX2(0.0, X);
}

double Perceptron::GetActivationGrad(double&& X, double(*pFunc)(const double&) = nullptr)
{
	if (pFunc)
	{
		return pFunc(X);
	}
	
	return 1.0f;
}

double Perceptron::GetActivationGrad(double X, double(*pFunc)(double&&) = nullptr)
{
	if (pFunc)
	{
		return pFunc(std::move(X));
	}

	return 1.0f;
}

void Perceptron::PropBackward(const double& Target, const double& LearningRate /*= 0.1*/)
{

	const double Grad = (Output - Target) * GetActivationGrad(std::move(Output), &Perceptron::Sigmoid);

	for (size_t i = 0; i < InputSize; ++i)
	{
		Weight[i] -= LearningRate * Grad;
	}

	Bias -= LearningRate * Grad * 1.0;
	FeedForward(Input);
}

void Perceptron::PropBackward(const double& Target, double&& LearningRate /*= 0.1*/)
{

	const double Grad = (Output - Target) * GetActivationGrad(std::move(Output), &Perceptron::Sigmoid);

	for (size_t i = 0; i < InputSize; ++i)
	{
		Weight[i] -= LearningRate * Grad;
	}

	Bias -= LearningRate * Grad * 1.0;
	FeedForward(Input);
}

void Perceptron::PropBackward(double&& Target, double&& LearningRate /*= 0.1*/)
{

	const double Grad = (Output - Target) * GetActivationGrad(std::move(Output), &Perceptron::Sigmoid);

	for (size_t i = 0; i < InputSize; ++i)
	{
		Weight[i] -= LearningRate * Grad;
	}

	Bias -= LearningRate * Grad * 1.0;
	FeedForward(Input);
}


std::ostream& operator<<(std::ostream & c, const Perceptron& P)
{
	c << "Size : " << P.InputSize << endl;

	c << "Input : [";
	for (size_t i = 0; i < P.InputSize - 1; ++i)
	{
		c << P.Input[i] << ", ";
	}
	c << P.Input.back() << "]";

	c << ", ";

	c << "Output : " << P.Output << endl;


	c << "Weight : [";
	for (size_t i = 0; i < P.InputSize - 1; ++i)
	{
		c << P.Weight[i] << ", ";
	}
	c << P.Weight.back() << "]";

	c << ", ";

	c << "Bias : " << P.Bias;


	return c;
}

void Test();

double getElectronDensity(double T, double E_g = 1.792e-19, double K = 1.38e-23)
{
	return 5.2 * 1e15 * pow(T, 1.5) * exp(-E_g / (2 * K * T));
}

int main()
{
	// �Ҽ��� �� n��° �ڸ����� ���
	cout.precision(8);

	// �Ҽ��� ���� �ڸ��� 0�� �������� �ʰ� ���
	cout.setf(ios::showpoint);

	double a = getElectronDensity(300.0);
	double b = pow(1.08e10, 2) / 1e16;
	
	cout << a << endl << b << endl;

	return 0;
}

void Test()
{
	// �Ҽ��� �� n��° �ڸ����� ���
	cout.precision(11);

	// �Ҽ��� ���� �ڸ��� 0�� �������� �ʰ� ���
	cout.setf(ios::showpoint);

	vector<double> Init_Weight, Init_Input;

	Init_Weight.reserve(2);
	Init_Weight.push_back(0.5);
	Init_Weight.push_back(0.28);

	Init_Input.reserve(2);
	Init_Input.push_back(5.0);
	Init_Input.push_back(7.0);

	Perceptron MyPerceptron(Init_Weight, 1.0);

	MyPerceptron.FeedForward(Init_Input);
	cout << MyPerceptron << endl;

	double Target = 13.0;

	for (int i = 0; i < 100; ++i)
	{
		std::cout << "\nTraining" << i + 1 << std::endl;
		MyPerceptron.PropBackward(Target, 0.1f);

		cout << MyPerceptron << endl;

		if (abs(MyPerceptron.Output - Target) < SMALL_NUMBER)
		{
			break;
		}
	}

	std::cout << "\nTraining Complete" << std::endl;

	std::cout << MyPerceptron << std::endl;

	std::cout << std::endl << std::endl;

	vector<double> NewInput;

	NewInput.reserve(2);

	NewInput << 2.3 << 1.7;


	std::cout << MyPerceptron.FeedForward(NewInput) << std::endl;
}