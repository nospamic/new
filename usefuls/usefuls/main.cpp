#include <iostream>
#include <string>
#include <sstream>

int round(double);

double str_to_double(std::string);

std::string double_to_str(double);

char* spaceRemove(char*);

/////////////////////////////////////
int main()
{
	std::cout<<spaceRemove("hello world - w   w   w")<<"\n";
	std::cout<<round(0.7)<<"\n";
	system("pause");
}
/////////////////////////////////////

int round(double a)
{
	(a>=0) ? (a-int(a)>=0.5) ? a=int(a+1) : a=int(a) : true;
	(a<0)  ? (a-int(a)<-0.5) ? a=int(a-1) : a=int(a) : true;
	return int(a);
}


//#include <string>
//#include <sstream>
double str_to_double(std::string s)
{
	double d=0.0;
	std::stringstream ss(s);
	ss>>d;
	return d;
}


//#include <string>
//#include <sstream>
std::string double_to_str(double a)
{
	std::string s;
	std::ostringstream ss;
	ss<<a;
	s=ss.str();
	return s;
}


char* spaceRemove (char*str)
{
	int n=0;
	char str2[999];
	for(unsigned i=0; i<strlen(str);i++)
	{
		if (str[i]!=' ') {str2[n]=str[i]; n++;}
	}
	str2[n]='\0';
	return &str2[0];
}
