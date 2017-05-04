/*
 * list.h
 *
 *  Created on: 2017年4月22日
 *      Author: root
 */

#ifndef LIST_HPP_
#define LIST_HPP_
#include<iostream>
#include<new>
#include<memory>
#include"list_iterator.hpp"
#include"list_reverse_iterator.hpp"
namespace JJ {
using namespace std;
template<typename T>
class _list_node
{
public:
	typedef _list_node<T>* link_type;
	typedef T value_type;
	T data;
	link_type prev;
	link_type next;
};
template<typename T,typename ALLOC=allocator<T> >
class simple_allocator
{
	typedef T* pointer;
	typedef size_t size_type;
public:
	static pointer allocate()
	{
		ALLOC a;
		auto result=a.allocate(1);
		return result;
	}
	static void deallocate(pointer ptr)
	{
		ALLOC a;
		a.deallocate(ptr,1);
	}
	static void deallocate(pointer ptr1,pointer ptr2)
	{
		ALLOC a;
		auto p=ptr1;
		while(p!=ptr2)
		{
			a.deallocate(p,1);
			p=p->next;
		}
		a.deallocate(ptr2,1);
	}
	static void construct(pointer ptr,const typename T::value_type& x)
	{
		ALLOC a;
		a.construct(&ptr->data,x);
	}
	static void destroy(pointer ptr)
	{
		ALLOC a;
		a.destroy(&ptr->data);
	}
	static void destroy(pointer ptr1,pointer ptr2)
	{
		ALLOC a;
		auto p=ptr1;
		while(p!=ptr2)
		{
			a.destroy(&p->data);
			p=p->next;
		}
		a.destroy(&ptr2->data);
	}
};
template<typename T,typename ALLOC1=simple_allocator<_list_node<T>>> class list;
template<typename T,typename ALLOC1>
ostream& operator<<(ostream& out,list<T,ALLOC1>& list);

template<typename T,typename ALLOC1>
class list
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef _list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef _list_iterator<T> iterator;
	typedef _list_reverse_iterator<T> reverse_iterator;
	typedef list<T,ALLOC1> self;
public:
	list();
	list(const self& rhs);
	list(self&& rhs);
	list(size_type num);
	list(size_type num,const T& elem);
	template<typename InputIterator>
	list(InputIterator first,InputIterator last);
	virtual ~list();
//element access
	self& operator=(const self& rhs);
	self& operator=(self&& rhs);
	void assign(size_type n,const T& elem);
	void assign(iterator first,iterator last);
	void swap(self& rhs);
	value_type& front();
	value_type& back();
//iterator function
	iterator begin();
	iterator end();
	const iterator cbegin() const;
	const iterator cend() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const reverse_iterator rcbegin() const;
	const reverse_iterator rcend() const;
//Inserting and removing
	void push_back(const T& elem);
	void pop_back();
	void push_front(const T& elem);
	void pop_front();
	iterator insert(iterator pos,const T& elem);
	iterator insert(iterator pos,size_type n,const T& elem);
	iterator insert(iterator pos,iterator first,iterator last);
	iterator erase(iterator pos);
	iterator erase(iterator first,iterator last);
	void remove(const T& elem);
	template<typename Y>
	void remove_if(Y OP);
	void resize(size_type num);
	void resize(size_type num,const T& elem);
	void clear();
	//algorithm
	void unique();
	template <typename Y>
	void unique(Y OP);
	iterator splice(iterator pos,self& c2);
	iterator splice(iterator pos,self& c2,iterator c2_pos);
	iterator splice(iterator pos,self& c2,iterator c2_first,iterator c2_last);
	void sort();
	template<typename Y>
	void sort(Y OP);
	void merge(self& c2);
	template<typename Y>
	void merge(self& c2,Y OP);
	void reverse();
protected:
	link_type list_node;
	link_type create_node();//构造空的节点
	link_type create_node(const T& x);
	void destroy_node(link_type ptr);
	void destroy_link(link_type ptr1,link_type ptr2);
	void empty_initialize();
	void copy_construct_from_list(const self& rhs);
	size_type size();
	void copy_list(const self& rhs);
	void copy_list(size_type n,const T& elem);
	void copy_list(iterator first,iterator last);
	void transfer(iterator pos,iterator first,iterator last);
	void swap_node(iterator pos1,iterator pos2);
	friend ostream& operator<<(ostream& out,list<T,ALLOC1> list)
		{
		for(auto i=list.begin();i!=list.end();++i)
			out<<*i<<" ";
		out<<endl;
		return out;
		}
};

} /* namespace JJ */

#endif /* LIST_HPP_ */
