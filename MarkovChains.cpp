//Markov Chains

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>
using namespace std;


class markovchain
{
	private:
		string text;
		list<markovchain *> adjlist;

	public:
		void add_transition(markovchain *);
		void set_text(string);
		list<markovchain *> next_list();
		string to_string();
		markovchain * next();
			
};

void markovchain::add_transition(markovchain *Y)
{
	adjlist.push_back(Y);
}

void markovchain::set_text(string s)
{
	text = s;
}

list<markovchain *> markovchain::next_list()
{
	return adjlist;
}

string markovchain::to_string()
{
	return text;
}

markovchain * markovchain::next()
{
	long n = adjlist.size();
	long div = (RAND_MAX + 1)/n;
	
	long k;
	
	do
	{
		k = rand()/div;
	}
	while (k >= n);
	
	auto it = adjlist.begin();
	advance(it, k);
	
	return *it;
}

int main()
{
	string m, str;
	int k;
	map<string, int> map;

	ifstream input;
	string filename;
	
	cout<<"Enter input filename: ";
	cin>>filename;
 	input.open(filename + "_inp.txt");
 	
	ofstream output;
 	output.open(filename + "_out.txt");
 	
 	
 	//inputting from file
 	m = "";
 	
 	for(string line; getline(input, line); )
	{
		m += line + "\n";
		
	}
	
	//k : order of the Markov model
	cout<<"Order of Markov Model: ";
	cin>>k;
	
	cout<<"\nTraining Markov Chain of order "<<k<<"...\n";
	
	string m_large = m;
	markovchain s[m.length()];
	int count = 0;
	
	while(m_large.size() < k + m.size())
	{
		m_large += m;
	}
	
	for(int i = 0; i < m.length(); ++i)
	{			
		str = m_large.substr(i, k);
		
		if (map.count(str) == 0)
		{
			map[str] = i;
			s[count].set_text(str);
			
			count += 1;			
		}
			
	}
		
	int j1, j2;
	string str1, str2;
	
	for(int i = 0; i < m.length(); ++i)
	{
		str1 = m_large.substr(i, k);
		str2 = m_large.substr(i + 1, k);
		
		for (j1 = 0; j1 < count; ++j1)
		{
			if(s[j1].to_string() == str1)
			{
				break;
			}
		}
		
		for (j2 = 0; j2 < count; ++j2)
		{
			if(s[j2].to_string() == str2)
			{
				break;
			}
		}
		
		s[j1].add_transition(&(s[j2]));
	}
		
	string gen = s[0].to_string();
	markovchain * mc = &s[0];
	
	for(int i = 0; i < m.length() - k; ++i)
	{
		mc = (*mc).next();
		gen += ((*mc).to_string()).back();
		
		 
	}
	 
	output<<"Generated text:\n"<<gen<<"\n";
	
	cout<<"Modified "<<filename + "_out.txt. \n";
	
}
