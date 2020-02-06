#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

// Prepares list for keys of map
list<string> ListPrepare(int thresh) {
	list<string> prep;
	for (int i = 0; i < thresh; i++) {
		prep.push_back("");
	}
	return prep;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Not enough outputs: ./text-predictor [training filename] [Output length (Ex: 100)]" << endl;
		return 0;
	}
	vector<string> tokens;
	map<list<string>, vector<string>> wordmap;
	list<string> state;
	stringstream str1;
	str1 << argv[2];
	int NUMBER_OF_WORDS;
	str1 >> NUMBER_OF_WORDS;
	int THRESHOLD = 3;
	string next_line;
	ifstream in(argv[1]);
	while (getline(in, next_line)) {
		istringstream iss(next_line);
		string token;
		while (iss >> token) {
			string nopunct = "";
			for (auto &c : token) {
				if (isalpha(c)) {
					nopunct +=c;
				}
			}
			tokens.push_back(nopunct);
		}
	}
	
	state = ListPrepare(THRESHOLD); 
	for (vector<string>::iterator it=tokens.begin(); it!=tokens.end(); it++) {
		wordmap[state].push_back(*it);
		state.push_back(*it);
		state.pop_front();
	}
	srand(time(NULL));
	state.clear();
	state = ListPrepare(THRESHOLD);
	for (int i = 0; i < NUMBER_OF_WORDS; i++) {
		int ind = rand() % wordmap[state].size();
		cout << wordmap[state][ind] << " ";
		state.push_back(wordmap[state][ind]);
		state.pop_front();
	}
	cout << endl;	

}
