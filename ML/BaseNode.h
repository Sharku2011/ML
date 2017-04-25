#pragma once
#include <iostream>

template<class T>
class BaseNode
{
public:
	BaseNode();
	~BaseNode();

	BaseNode(const T& V);
	BaseNode(T&& V);

	T GetData() const;

public:
	

protected:

	BaseNode<T>* NextNode;
	BaseNode<T>* PrevNode;

private:

	T Data;

};

