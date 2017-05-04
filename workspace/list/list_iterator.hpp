/*
 * list_iterator.hpp
 *
 *  Created on: 2017年4月22日
 *      Author: root
 */

#ifndef LIST_ITERATOR_HPP_
#define LIST_ITERATOR_HPP_
#include<iterator>
#include<iostream>
#include<new>
#include<memory>
using namespace std;
namespace JJ{
template<typename T> class _list_node;
template<typename T>
class _list_iterator:public std::iterator<bidirectional_iterator_tag,T>
{
	public:
	typedef _list_iterator<T> iterator;
	typedef _list_node<T>* link_type ;//迭代器的底层实现
	typedef typename std::iterator<bidirectional_iterator_tag,T>::pointer pointer;
	typedef typename std::iterator<bidirectional_iterator_tag,T>::reference reference;
	link_type node;
	public:
	_list_iterator():node(nullptr){}
	_list_iterator(link_type& x):node(x){}
	_list_iterator(const link_type& x):node(x){}
	virtual ~_list_iterator(){}
	reference operator*();
	pointer operator->();
	iterator& operator++();
	iterator operator++(int);
	iterator operator+(int i);
	iterator& operator--();
	iterator operator--(int);
	iterator operator-(int i);
	virtual bool operator==(const iterator& item);
	virtual bool operator!=(const iterator& item);
	virtual bool operator>(const iterator& item);
	virtual bool operator<(const iterator& item);
};
template<typename T>
typename _list_iterator<T>::reference _list_iterator<T>::operator *()
{
	return node->data;
}
template<typename T>
typename _list_iterator<T>::pointer _list_iterator<T>::operator ->()
{
	return &(operator*());
}
template<typename T>
typename _list_iterator<T>::iterator& _list_iterator<T>::operator++()
{
	node=node->next;
	return *this;
}
template<typename T>
typename _list_iterator<T>::iterator _list_iterator<T>::operator++(int)
{
	auto old=*this;
	++*this;
	return old;
}
template<typename T>
typename _list_iterator<T>::iterator& _list_iterator<T>::operator--()
{
	node=node->prev;
	return *this;
}
template<typename T>
typename _list_iterator<T>::iterator _list_iterator<T>::operator--(int)
{
	auto old=*this;
	--*this;
	return old;
}
template<typename T>
typename _list_iterator<T>::iterator _list_iterator<T>::operator-(int i)
{
	auto j=this;
	for(auto n=0;n!=i;++n)
		--j;
	return *j;
}
template<typename T>
typename _list_iterator<T>::iterator _list_iterator<T>::operator+(int i)
{
	auto j=this;
	for(auto n=0;n!=i;++n)
		++j;
	return *j;
}
template<typename T>
bool _list_iterator<T>::operator==(const iterator& item)
{
	return node==item.node;
}
template<typename T>
bool _list_iterator<T>::operator!=(const iterator& item)
{
	return !(node==item.node);
}
template<typename T>
bool _list_iterator<T>::operator>(const iterator& item)
{
	if(*this==item)
		return false;
	for(auto i=*this;i.node!=nullptr;++i)
	{
		if(i==item)
			return false;
	}
	for(auto i=*this;i.node!=nullptr;--i)
	{
		if(i==item)
			return true;
	}
}
template<typename T>
bool _list_iterator<T>::operator<(const iterator& item)
{
	if(*this==item)
		return false;
	for(auto i=*this;i.node!=nullptr;++i)
	{
		if(i==item)
			return true;
	}
	for(auto i=*this;i.node!=nullptr;--i)
	{
		if(i==item)
			return false;
	}
}
}

#endif /* LIST_ITERATOR_HPP_ */
