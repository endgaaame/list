/*
 * list_test.cpp
 *
 *  Created on: 2017年4月22日
 *      Author: root
 */

#include "list.hpp"
#include"list.cpp"
#include<functional>
int main()
{
	JJ::list<int> a;
	a.push_back(2);
	a.push_back(3);
	a.push_back(9);
	a.push_back(1);
	std::cout<<a;
	a.reverse();
	std::cout<<a;
	a.sort();
	std::cout<<a;
	a.insert(a.begin(),7);
	std::cout<<a;
	auto b=a;
	b.sort();
  a.splice(a.rbegin(),b);
  std::cout<<a;
}
