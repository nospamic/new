#include <iostream>
#include <vector>


int main()

{
	char a='1';
	char *ptr_a;
	ptr_a=&a;
	std::cout<<"ptr_a="<<ptr_a<<"   *ptr_a="<<*ptr_a;

	double s=1;
	std::cout<<"\n &s="<<&s;
	double *ptrs=new double;
	double *ptrss=new double;

	std::cout<<"\n ptrs="<<ptrs<<"   *ptrs="<<*ptrs;
	std::cout<<"\n ptrss="<<ptrs<<"   *ptrss="<<*ptrs;

	*ptrs=10;
	*ptrss=20;

	int distance=ptrss-ptrs;
	std::cout<<"\n\n ptrss-ptrs="<<ptrss-ptrs;

	for (int i=0;i<distance;i++,ptrs++)
	{
		std::cout<<"\n ptrs="<<ptrs<<"   *ptrs="<<*ptrs;
	}
	//ptrs--;
	std::cout<<"\n\n ptrs="<<ptrs<<"   *ptrs="<<*ptrs;
	std::cout<<"\n ptrss="<<ptrs<<"   *ptrss="<<*ptrs;

	std::vector<int>vec;
	int*ptr;
	for (int i=0; i<5;i++){vec.push_back(i);std::cout<<"\t"<<vec[i];}

	for (int i=0; i<vec.size();i++)
	{
		ptr=&vec[i];
		
		std::cout<<"\n ptr="<<ptr<<"   *ptr="<<*ptr;
	}
	*ptr=20;
	std::cout<<"\n ptr="<<ptr<<"   *ptr="<<*ptr;
	ptr++;
	*ptr=30;
	std::cout<<"\n ptr="<<ptr<<"   *ptr="<<*ptr;
	system("pause");




}