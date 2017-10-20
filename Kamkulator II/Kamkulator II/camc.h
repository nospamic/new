#pragma once

class camc
{
public:
camc(){}//constructor



double skobki(string exe)
{
int inside=1;
string frag;
bool start=1;
string vskobkah="0";
while (inside!=0 || vskobkah!="")
	{
	inside=0;
	frag="";
	start=0;
	vskobkah="";
	//cout <<"\n";
	for(int i=0;i<exe.size();i++)
		{
		if (exe[i]=='(' && start==1){inside++;frag="";continue;}
		if (exe[i]==')' && start==1)
			{
			//cout<<"\n"<<frag; 
			vskobkah=double_to_str(calc(frag));//cout<<"\n vskobkah = "<<vskobkah;
			exe.erase(exe.begin()+i-frag.size()-1,exe.begin()+i+1);
			exe.insert(i-frag.size()-1,vskobkah);
			//cout<<"\n exe = "<< exe<<"  frag.size = "<<frag.size();
			start=0;frag="";
			break;
			}
		if (start==1){frag+=exe[i];}
		if (exe[i]=='('){start=1;}

		}
	//cout <<"\n inside = "<<inside<<" vskobkah = "<<vskobkah;
	}

return calc(exe);
}



private:


double calc(string exe)
{

vector<double>cyfra;//chisla
vector<string>chlen;//znaki+chisla (string)

//cout <<"\nExemple:";cin >> exe;

//make chlen
string fragm="";
for(int i=0;i<exe.size();i++)
	{
		if (exe[i]!='+' && exe[i]!='-' && exe[i]!='*' && exe[i]!='/'){fragm+=exe[i];}
		else
		{if(fragm!=""){chlen.push_back(fragm);}
		fragm=exe[i];chlen.push_back(fragm);fragm="";
		}
	}
chlen.push_back(fragm);//last chlen

//cout<<"\n";
//for(int i=0;i<chlen.size();i++){cout <<"\n"<<i<<"--"<<chlen[i];}

//------------make cyfra(double)----------------------
//cout<<"\n\n";
for(int i=0;i<chlen.size();i++)
	{
	if (chlen[i]!="+" && chlen[i]!="-" && chlen[i]!="*" && chlen[i]!="/"){cyfra.push_back (str_to_double(chlen[i]));}
	else {cyfra.push_back (0.0);}
	//cout <<"\t"<<cyfra[i];
}

//---------------------/ s prava na levo ------------------------------------
//cout<<"\n\n umnojenie \t";

double mnoj;
string smnoj;
bool ready=0;
while (ready==0)
	{
	
	ready=1;
	for(int i=0;i<chlen.size();i++)
		{
		if (chlen[i]=="/")
			{
			ready=0;
			if(cyfra[i+1]!=0){mnoj=cyfra[i-1]/cyfra[i+1];}else{cout<<"\n\n Divizion by zero!\n\n";system("pause");}
			smnoj=double_to_str(mnoj);
			cyfra[i-1]=mnoj;
			cyfra.erase(cyfra.begin()+i,cyfra.begin()+i+2);
			chlen[i-1]=smnoj;
			chlen.erase(chlen.begin()+i,chlen.begin()+i+2);
			break;
			}
		}
	}
//---------------------* s prava na levo ------------------------------------

ready=0;
while (ready==0)
	{
	
	ready=1;

	for(int i=0;i<chlen.size();i++)
		{
		if (chlen[i]=="*")
			{
			ready=0;
			mnoj=cyfra[i-1]*cyfra[i+1];
			smnoj=double_to_str(mnoj);
			cyfra[i-1]=mnoj;
			cyfra.erase(cyfra.begin()+i,cyfra.begin()+i+2);
			chlen[i-1]=smnoj;
			chlen.erase(chlen.begin()+i,chlen.begin()+i+2);
			}
		}
	}
//cout<<"\n";
//for(int i=0;i<chlen.size();i++){cout <<"\t"<<chlen[i];}
//cout<<"\n";
//for(int i=0;i<cyfra.size();i++){cout <<"\t"<<cyfra[i];}

//-------------------"+-" s leva na pravo--------------------------------------
double summa=0;
if (chlen[0]!="-"){summa+=cyfra[0];}
for(int i=0;i<chlen.size();i++)
	{
		if (chlen[i]=="+"){summa+=cyfra[i+1];}
		if (chlen[i]=="-"){summa-=cyfra[i+1];}
	}
if (chlen.size()==1){summa=cyfra[0];}
if (chlen.size()==2){summa=cyfra[1]*(-1);}
return summa;
//cout<<"\n\n"<<exe<<" = "<<summa;


}

double str_to_double(string s)
{
double d=0.0;
stringstream ss(s);
ss>>d;
return d;
}

string double_to_str(double a)
{

string s;
ostringstream ss;
ss<<a;
s=ss.str();
return s;
}
	
};
