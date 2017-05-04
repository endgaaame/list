/*
 * list_reverse_iterator.hpp
 *
 *  Created on: 2017年4月24日
 *      Author: root
 */

#ifndef LIST_REVERSE_ITERATOR_HPP_
#define LIST_REVERSE_ITERATOR_HPP_
#include"list_iterator.hpp"
using namespace std;
using namespace JJ;
template<typename T>
class _list_reverse_iterator:public JJ::_list_iterator<T>
{
public:
	typedef _list_reverse_iterator<T> iterator;
	typedef typename _list_iterator<T>::link_type link_type;
public:
	_list_reverse_iterator():_list_iterator<T>(nullptr){}
	_list_reverse_iterator(link_type& x):_list_iterator<T>(x){}
	_list_reverse_iterator(const link_type& x):_list_iterator<T>(x){}
	iterator& operator++();
	iterator operator++(int);
	iterator& operator--();
	iterator operator--(int);
};
template<typename T>
typename _list_reverse_iterator<T>::iterator& _list_reverse_iterator<T>::operator ++()
{
	this->node=this->node->next;
	return *this;
}
template<typename T>
typename _list_reverse_iterator<T>::iterator _list_reverse_iterator<T>::operator ++(int)
{
	auto old=*this;
	--*this;
	return old;
}
template<typename T>
typename _list_reverse_iterator<T>::iterator& _list_reverse_iterator<T>::operator --()
{
	this->node=this->node->next;
	return *this;
}
template<typename T>
typename _list_reverse_iterator<T>::iterator _list_reverse_iterator<T>::operator --(int)
{
	auto old=*this;
	++*this;
	return old;
}


#endif /* LIST_REVERSE_ITERATOR_HPP_ */
