#pragma once

#include <map>
#include <vector>

class Graph
{
public:
	Graph(size_t Dim);
	~Graph();

	size_t GetDimension() { return Dimension; }

	void Add(std::vector<double>& NewCoord);
	void Add_Implementation(std::vector<double>& NewCoord);
	void Add_Implementation(std::vector<double>* NewCoord);

	std::vector<std::vector<double>>* GetCoords() const;

	void Update();

	friend std::ostream& operator<<(std::ostream& c, const Graph& g);

protected:

private:

	std::vector<std::vector<double>>* Coords;

	size_t Dimension;

	// Mean of X
	double MeanX;
	// Variation of X
	double VarX;
	// Mean of Y
	double MeanY;
	// Variation of Y
	double VarY;

	double Sxx;
	double Sxy;
	double Syy;


};

