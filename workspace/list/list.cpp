/*
 * list.cpp
 *
 *  Created on: 2017年4月22日
 *      Author: root
 */

#include "list.hpp"

namespace JJ {
using namespace std;
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::link_type list<T,ALLOC1>::create_node()
{
	auto result=ALLOC1::allocate();
	ALLOC1::construct(result,T());
	return result;
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::link_type list<T,ALLOC1>::create_node(const T& x)
{
	auto result=ALLOC1::allocate();
	ALLOC1::construct(result,x);
	return result;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::destroy_node(link_type ptr)
{
	ALLOC1::destroy(ptr);
	ALLOC1::deallocate(ptr);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::destroy_link(link_type ptr1,link_type ptr2)
{
	ALLOC1::destroy(ptr1,ptr2);
	ALLOC1::deallocate(ptr1,ptr2);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::empty_initialize()
{
	list_node=ALLOC1::allocate();
	list_node->next=list_node;
	list_node->prev=list_node;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::copy_construct_from_list(const self& rhs)
{
	empty_initialize();
	auto i=this->list_node;
	auto j=rhs.list_node->next;
	while(j!=rhs.list_node)
	{
		auto result=create_node(j->data);
		result->prev=i;
		i->next=result;
		i=result;
		if(j->next==rhs.list_node)
		{
			i->next=this->list_node;
			this->list_node->prev=i;
			break;
		}
		j=j->next;
	}
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::size_type list<T,ALLOC1>::size()
{
	auto i=this->list_node->next;
	size_type index=1;
	while(i!=this->list_node)
	{
		i=i->next;
		++index;
	}
	return index;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::copy_list(const self& rhs)
{
	if(size()==rhs.size())
	{
		auto i=this->list_node->next;
		auto j=rhs.list_node->next;
		while(i!=this->list_node)
		{
			i->data=j->data;
			i=i->next;
			j=j->next;
		}
	}
	else if(size()>rhs.size())
	{
		auto i=this->list_node->next;
		auto j=rhs.list_node->next;
		while(j!=rhs.list_node)
		{
			i->data=j->data;
			if(j->next==rhs.list_node)
			{
				auto ptr=i->next;
				auto ptr1=this->list_node->prev;
				i->next=this->list_node;
				this->list_node->prev=i;
				ALLOC1::destroy(ptr,ptr1);
				ALLOC1::deallocate(ptr,ptr1);
			}
			i=i->next;
			j=j->next;
		}
	}
	else
	{
		auto size_list=rhs.size()-size();
		auto _i=this->list_node->prev;
		auto index=0;
		while(index!=size_list)
		{
			auto result=create_node();
			_i->next=result;
			result->prev=_i;
			_i=result;
			if(index+1==size_list)
			{
				_i->next=this->list_node;
				this->list_node->prev=_i;
			}
			++index;
		}
		auto i=this->list_node->next;
		auto j=rhs.list_node->next;
		while(i!=this->list_node)
		{
			i->data=j->data;
			i=i->next;
			j=j->next;
		}
	}
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::copy_list(size_type n,const T& elem)
{
	if(size()==n)
	{
		auto i=this->list_node->next;
		while(i!=this->list_node)
		{
			i->data=elem;
			i=i->next;
		}
	}
	else if(size()>n)
	{
		auto i=this->list_node->next;
		size_type index=0;
		while(i!=this->list_node)
		{
			i->data=elem;
			++index;
			if(index==n)
			{
				auto ptr=i->next;
				auto ptr1=this->list_node->prev;
				i->next=this->list_node;
				this->list_node->prev=i;
				ALLOC1::destroy(ptr,ptr1);
				ALLOC1::deallocate(ptr,ptr1);
			}
			i=i->next;
		}
	}
	else
	{
		auto size_list=n-size();
		auto _i=this->list_node->prev;
		auto index=0;
		while(index!=size_list)
		{
			auto result=create_node();
			_i->next=result;
			result->prev=_i;
			_i=result;
			if(index+1==size_list)
			{
				_i->next=this->list_node;
				this->list_node->prev=_i;
			}
			++index;
		}
		auto i=this->list_node->next;
		while(i!=this->list_node)
		{
			i->data=elem;
			i=i->next;
		}
	}
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::copy_list(iterator first,iterator last)
{
	size_type size_iterator=0;
	for(auto i=first;i!=last;++i)
		++size_iterator;
	if(size()==size_iterator)
	{
		auto i=this->list_node->next;
		auto j=first;
		while(i!=this->list_node)
		{
			i->data=*j;
			i=i->next;
			++j;
		}
	}
	else if(size()>size_iterator)
	{
		auto i=this->list_node->next;
		auto j=first;
		while(j!=last)
		{
			i->data=*j;
			if(j->next==last)
			{
				auto ptr=i->next;
				auto ptr1=this->list_node->prev;
				i->next=this->list_node;
				this->list_node->prev=i;
				ALLOC1::destroy(ptr,ptr1);
				ALLOC1::deallocate(ptr,ptr1);
			}
			i=i->next;
			++j;
		}
	}
	else
	{
		auto size_list=size_iterator-size();
		auto _i=this->list_node->prev;
		auto index=0;
		while(index!=size_list)
		{
			auto result=create_node();
			_i->next=result;
			result->prev=_i;
			_i=result;
			if(index+1==size_list)
			{
				_i->next=this->list_node;
				this->list_node->prev=_i;
			}
			++index;
		}
		auto i=this->list_node->next;
		auto j=first;
		while(i!=this->list_node)
		{
			i->data=*j;
			i=i->next;
		  ++j;
		}
	}
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::transfer(iterator pos,iterator first,iterator last)
{
	auto i=pos.node->prev;
	auto j=pos.node;
	auto _prev_first=first.node->prev;
	auto _next_last=last.node->next;
	i->next=first.node;
	j->prev=last.node;
	first.node->prev=i;
	last.node->next=j;
	_prev_first->next=_next_last;
	_next_last->prev=_prev_first;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::swap_node(iterator pos1,iterator pos2)
{
	auto temp=pos1.node->data;
	pos1.node->data=pos2.node->data;
	pos2.node->data=temp;
}
template<typename T,typename ALLOC1>
list<T,ALLOC1>::list()
{
	empty_initialize();
}
template<typename T,typename ALLOC1>
list<T,ALLOC1>::list(const self& rhs)
{
	copy_construct_from_list(rhs);
}
template<typename T,typename ALLOC1>
list<T,ALLOC1>::list(self&& rhs)
{
	copy_construct_from_list(rhs);
	rhs.~list();
}
template<typename T,typename ALLOC1>
list<T,ALLOC1>::list(size_type num)
{
	empty_initialize();
	auto i=this->list_node;
	for(auto j=0;j!=num;++j)
	{
		auto result=create_node();
		i->next=result;
		result->prev=i;
		i=result;
		if(i+1==num)
		{
			i->next=this->list_node;
			this->list_node->prev=i;
			break;
		}
	}
}
template<typename T,typename ALLOC1>
list<T,ALLOC1>::list(size_type num,const T& elem)
{
	empty_initialize();
	auto i=this->list_node;
	for(auto j=0;j!=num;++j)
	{
		auto result=create_node(elem);
		i->next=result;
		result->prev=i;
		i=result;
		if(i+1==num)
		{
			i->next=this->list_node;
			this->list_node->prev=i;
			break;
		}
	}
}
template<typename T,typename ALLOC1>
template<typename InputIterator>
list<T,ALLOC1>::list(InputIterator first,InputIterator last)
{
	empty_initialize();
	auto i=this->list_node;
	auto j=first;
	while(j!=last)
	{
		auto result=creat_node(*j);
		result->prev=i;
		i->next=result;
		i=result;
		if(++j==last)
		{
			i->next=this->list_node;
			this->list_node->prev=i;
		}
		else
		{
			--j;
		}
		++j;
	}
}
template<typename T,typename ALLOC1>
list<T,ALLOC1>::~list()
{
	ALLOC1::destroy(this->list_node->next,this->list_node);
	ALLOC1::deallocate(this->list_node->next,this->list_node);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::self& list<T,ALLOC1>::operator=(const self& rhs)
{
	copy_list(rhs);
	return *this;
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::self& list<T,ALLOC1>::operator=(self&& rhs)
{
	copy_list(rhs);
	rhs.~list();
	return *this;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::assign(size_type n,const T& elem)
{
	copy_list(n,elem);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::assign(iterator first,iterator last)
{
	copy_list(first,last);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::swap(self& rhs)
{
	auto temp=rhs.list_node;
	rhs.list_node=list_node;
	list_node=temp;
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::value_type& list<T,ALLOC1>::front()
{
	return list_node->next->data;
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::value_type& list<T,ALLOC1>::back()
{
	return list_node->prev->data;
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::begin()
{
	return _list_iterator<T>(list_node->next);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::end()
{
	return _list_iterator<T>(list_node);
}
template<typename T,typename ALLOC1>
const typename list<T,ALLOC1>::iterator list<T,ALLOC1>::cbegin() const
{
	return _list_iterator<T>(list_node->next);
}
template<typename T,typename ALLOC1>
const typename list<T,ALLOC1>::iterator list<T,ALLOC1>::cend() const
{
	return _list_iterator<T>(list_node);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::reverse_iterator list<T,ALLOC1>::rbegin()
{
	return _list_reverse_iterator<T>(list_node);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::reverse_iterator list<T,ALLOC1>::rend()
{
	return _list_reverse_iterator<T>(list_node->prev);
}
template<typename T,typename ALLOC1>
const typename list<T,ALLOC1>::reverse_iterator list<T,ALLOC1>::rcbegin() const
{
	return _list_reverse_iterator<T>(list_node);
}
template<typename T,typename ALLOC1>
const typename list<T,ALLOC1>::reverse_iterator list<T,ALLOC1>::rcend() const
{
	return _list_reverse_iterator<T>(list_node->prev);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::push_back(const T& elem)
{
	auto result=create_node(elem);
	auto _i=this->list_node->prev;
	_i->next=result;
	result->prev=_i;
	result->next=this->list_node;
        this->list_node->prev=result;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::pop_back()
{
	auto _i=this->list_node->prev;
	auto i=_i->prev;
	i->next=this->list;
	this->list_node->prev=i;
	destroy_node(_i);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::push_front(const T& elem)
{
	auto result=create_node(elem);
	auto i=this->list_node->next;
	i->prev=result;
	result->next=i;
	result->prev=this->list_node;
	this->list_node->next=result;
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::pop_front()
{
	auto _i=this->list_node->next;
	auto i=_i->next;
	i->prev=this->list;
	this->list_node->next=i;
	destroy_node(_i);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::insert(iterator pos,const T& elem)
{
	auto result=create_node(elem);
	auto i=pos.node->prev;
	auto j=pos.node;
	i->next=result;
	j->prev=result;
	result->prev=i;
	result->next=j;
	return _list_iterator<T>(result);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::insert(iterator pos,size_type n,const T& elem)
{
	if(n==0)
		return pos;
	link_type new_head;
	link_type prev;
	link_type new_tail;
	size_type index=0;
	for(;index!=n;++index)
	{
		auto result=create_node(elem);
		if(index==0)
			{
			  new_head=result;
			  prev=result;
			  continue;
			}
		if(index+1==n)
			new_tail=result;
		prev->next=result;
		result->prev=prev;
		prev=result;
	}
	auto i=pos.node->prev;
	auto j=pos.node;
	i->next=new_head;
	j->prev=new_tail;
	new_head->prev=i;
	new_tail->next=j;
	return _list_iterator<T>(new_tail);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::insert(iterator pos,iterator first,iterator last)
{
	auto i=pos.node->prev;
	auto j=pos.node;
	i->next=first.node;
	j->prev=last.node;
	first.node->prev=i;
	last.node->next=j;
	return _list_iterator<T>(last.node);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::erase(iterator pos)
{
	auto i=pos.node->prev;
	auto j=pos.node->next;
	i->next=j;
	j->prev=i;
	destroy_node(pos.node);
	return _list_iterator<T>(j);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::erase(iterator first,iterator last)
{
	auto i=first.node->prev;
	auto j=last.node->next;
	i->next=j;
	j->prev=i;
	destroy_link(first.node,last.node);
	return _list_iterator<T>(j);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::remove(const T& elem)
{
	for(auto i=begin();i!=end();++i)
	{
		auto tmp=i;
		if(*i==elem)
			  erase(i);
		i=tmp;
	}
}
template<typename T,typename ALLOC1>
template<typename Y>
void list<T,ALLOC1>::remove_if(Y OP)
{
	for(auto i=begin();i!=end();++i)
	{
		auto tmp=i;
		if(OP(*i))
			  erase(i);
		i=tmp;
	}
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::resize(size_type num)
{
	if(num<size())
	throw out_of_range("fuck u bitch out of range");
	insert(end(),num-size(),T());
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::resize(size_type num,const T& elem)
{
	if(num<size())
	throw out_of_range("fuck u bitch out of range");
	insert(end(),num-size(),elem);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::clear()
{
	erase(begin(),--end());
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::unique()
{
	auto first=begin();
	auto last=end();
	if(first==last)
		return ;
	while(first!=last)
	{
		auto next=first;
		++next;
		if(*first==*next)
			erase(first);
		first=next;
	}
}
template<typename T,typename ALLOC1>
template<typename Y>
void list<T,ALLOC1>::unique(Y OP)
{
	auto first=begin();
	auto last=end();
	if(first==last)
		return ;
	while(first!=last)
	{
		auto next=first;
		++next;
		if(OP(*first,*next))
			erase(first);
		first=next;
	}
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::splice(iterator pos,self& c2)
{
	transfer(pos,c2.begin(),--c2.end());
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::splice(iterator pos,self& c2,iterator c2_pos)
{
	transfer(pos,c2_pos,c2_pos);
}
template<typename T,typename ALLOC1>
typename list<T,ALLOC1>::iterator list<T,ALLOC1>::splice(iterator pos,self& c2,iterator c2_first,iterator c2_last)
{
	transfer(pos,c2_first,c2_last);
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::sort()
{
	for(auto i=begin();i!=end();++i)
	{
		for(auto j=--end();j!=i;--j)
			if(*j<*(j-1))
				swap_node(j,j-1);
	}
}
template<typename T,typename ALLOC1>
template<typename Y>
void list<T,ALLOC1>::sort(Y OP)
{
	for(auto i=begin();i!=end();++i)
	{
		for(auto j=end()-1;j!=i;--j)
			if(OP(*j,*(j-1)))
				swap_node(j,j-1);
	}
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::merge(self& c2)
{
	for(auto i=begin();i!=end();++i)
	{
		for(auto j=c2.begin();j!=c2.end();++j)
			{
			  if(*j<*i)
				  transfer(i,j,j);
			  else
				  break;
			}
	}
}
template<typename T,typename ALLOC1>
template<typename Y>
void list<T,ALLOC1>::merge(self& c2,Y OP)
{
	for(auto i=begin();i!=end();++i)
	{
		for(auto j=c2.begin();j!=c2.end();++j)
			{
			  if(OP(*j,*i))
				  transfer(i,j,j);
			  else
				  break;
			}
	}
}
template<typename T,typename ALLOC1>
void list<T,ALLOC1>::reverse()
{
	auto first=begin();
	++first;
	while(first!=end())
	{
		auto old=first;
		++first;
		transfer(begin(),old,old);
	}
}

} /* namespace JJ */
