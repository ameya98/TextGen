// Markov Chains
// Author : Ameya Daigavane

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>
using namespace std;

// Each class instance represents a string of fixed length. Transitions occur between these strings.  
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

// Add transition
void markovchain::add_transition(markovchain *Y)
{
	adjlist.push_back(Y);
}

// Setter for the text property
void markovchain::set_text(string s)
{
	text = s;
}

// Returns the list of pointers to the next strings to which we can transition randomly.
list<markovchain *> markovchain::next_list()
{
	return adjlist;
}

// Convert markovchain object back to string.
string markovchain::to_string()
{
	return text;
}

// The actual random transition
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
	string inputfilename, outputfilename;

	cout << "Enter the input filename: ";
	cin >> inputfilename;

 	input.open(inputfilename);

	if(!input.good())
	{
		std::cout << "Input file not found in current directory." << '\n';
		exit(1);
	}

	ofstream output;
	outputfilename = inputfilename;
	outputfilename.replace(outputfilename.end() - 8, outputfilename.end(), "_out.txt");
 	output.open(outputfilename);


 	// inputting from file - m stores all the file text.
 	m = "";

 	for(string line; getline(input, line); )
	{
		m += line + "\n";

	}

	// k is the order of the Markov model
	cout << "Order of Markov Model: ";
	cin >> k;

	cout<< "\n" << "Training Markov Chain of order "<< k <<"...\n";

	// to ensure that we have k equal sized words
	string m_large = m;
	markovchain s[m.length()];
	int count = 0;

	while(m_large.size() < k + m.size())
	{
		m_large += m;
	}

	// hashmap to map the input substrings of length k
	for(int i = 0; i < m.length(); ++i)
	{
		// input substring
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

		// add transition
		s[j1].add_transition(&(s[j2]));
	}

	// all transitions added - now generate the random walk through the states
	string gen = s[0].to_string();
	markovchain * mc = &s[0];

	for(int i = 0; i < m.length() - k; ++i)
	{
		mc = (*mc).next();
		gen += ((*mc).to_string()).back();

	}

	output << "Generated text:\n" << gen <<"\n";
	cout << "Modified " << outputfilename << "\n";

}
