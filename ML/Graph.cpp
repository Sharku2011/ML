#include <iostream>
#include "Graph.h"
#include <algorithm>
#include <cstdio>

Graph::Graph(size_t Dim) : Dimension(Dim), MeanX(0.0), MeanY(0.0), VarX(0.0), VarY(0.0), Sxx(0.0), Sxy(0.0), Syy(0.0)
{
	Coords = new std::vector<std::vector<double>>();

	Coords->reserve(256);
}

Graph::~Graph()
{
	delete Coords;
}

void Graph::Add(std::vector<double>& NewCoord)
{
	Add_Implementation(NewCoord);

	Update();
}

void Graph::Add_Implementation(std::vector<double>& NewCoord)
{
	Coords->push_back(NewCoord);
}

void Graph::Add_Implementation(std::vector<double>* NewCoord)
{
	Coords->push_back(*NewCoord);
}

std::ostream& operator<<(std::ostream& c, const Graph& g)
{
	size_t NumOfCoords = g.Coords->size();

	//for (int i = 0; i < NumOfCoords; ++i)
	//{
	//	c << "x: " << (*g.Coords)[i][0] << ", y: " << (*g.Coords)[i][1] << std::endl;
	//}

	for (std::vector<double>& Coord : *g.Coords)
	{
		c << "x: " << Coord[0] << ", y: " << Coord[1] << std::endl;
	}

	// std::for_each 는 iterator 의 값만을 매개변수로 받는 함수만을 받는다(unary function - 단항 함수)
	//std::for_each(g.Coords->begin(), g.Coords->end(), [&c](std::vector<double>& Coord) {c << "x: " << Coord[0] << ", y: " << Coord[1] << std::endl; });

	c << "E_x : " << g.MeanX << ", E_y : " << g.MeanY << std::endl;
	c << "Sxx : " << g.Sxx << ", Sxy : " << g.Sxy << ", Syy : " << g.Syy << std::endl;

	c << "Linear Regression Slope : " << g.Sxy / g.Sxx << std::endl;

	return c;
}

std::vector<std::vector<double>>* Graph::GetCoords() const
{
	return Coords;
}

void Graph::Update()
{
	try
	{
		double SumX = 0;
		double SumY = 0;

		for (std::vector<double>& Coord : *Coords)
		{
			SumX += Coord[0];
			SumY += Coord[1];
		}

		MeanX = SumX / Coords->size();
		MeanY = SumY / Coords->size();

		for (std::vector<double>& Coord : *Coords)
		{
			Sxx += pow(MeanX - Coord[0], 2);
			Sxy += (MeanX - Coord[0])*(MeanY - Coord[1]);
			Syy += pow(MeanY - Coord[1], 2);
		}


		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;

		throw e;
	}


}