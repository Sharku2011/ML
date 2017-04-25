#include "BaseNode.h"

template<class T>
BaseNode<T>::BaseNode()
{
	PrevNode = NextNode = nullptr;
}

template<class T>
BaseNode<T>::~BaseNode()
{

}

template<class T>
BaseNode<T>::BaseNode(const T& V)
{
	Data = V;
}

template<class T>
BaseNode<T>::BaseNode(T&& V)
{
	Data = V;
}

template<class T>
T BaseNode<T>::GetData() const
{
	return Data;
}