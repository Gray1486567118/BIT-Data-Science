#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 10001;

void printchar(char c, int n);
char char_to_digit(char c); 
string standardise_number(const string& input);
bool is_valid(const string& input);


int main() {
	map<string, int> number_count;
	vector<string> errors;
	
	string input;
	while (getline(cin, input)) {
		if (input.empty()) break;
		
		if (!is_valid(input)) {
			errors.push_back(input);
		} else {
			string standard = standardise_number(input);
			number_count[standard] ++;
		}
	}
	
	// output
	cout << "Error:" << endl;
	if (errors.empty()) {
		cout << "Not found." << endl;
	} else {
		for (vector<string>::const_iterator it = errors.begin(); it != errors.end(); ++it) {
    		cout << *it << endl;
		}
	}
	cout << endl;
	
	vector<pair<string, int> > dupl;
	for (map<string, int>::const_iterator it = number_count.begin(); it != number_count.end(); ++it) {
	    if (it->second > 1) {
	        dupl.push_back(*it);
	    }
	}

	
	sort(dupl.begin(), dupl.end());
	
	cout << "Duplication:" << endl;
	if (dupl.empty()) {
		cout << "Not found." << endl;
	} else {
		for (vector<pair<string, int> >::iterator it = dupl.begin(); it != dupl.end(); ++it) {
		    cout << it->first << " " << it->second << endl;
		}
	}
	return 0;
}

string standardise_number(const string& input) {
	string result;
	int count = 0;
	for (string::const_iterator it = input.begin(); it != input.end(); ++it) {
        char c = *it;
        if (c == '-') continue;
        
		if (isalpha(c)) {
			result += char_to_digit(c);
		} else if (isdigit(c)){
			result += c;
		}
		count ++;
		if (count == 3) result += '-';
	}
	return result;
}

bool is_valid(const string& input) {
	if (input.find('Q') != string::npos || input.find('Z') != string::npos){
		return false;
	}
	
	string standard = standardise_number(input);
	return standard[0] == '3' || standard[0] == '6';
}


char char_to_digit(char c) {
    if ('A' <= c && c <= 'C') return '2';
    if ('D' <= c && c <= 'F') return '3';
    if ('G' <= c && c <= 'I') return '4';
    if ('J' <= c && c <= 'L') return '5';
    if ('M' <= c && c <= 'O') return '6';
    if ('P' == c || c == 'R' || c == 'S') return '7';
    if ('T' <= c && c <= 'V') return '8';
    if ('W' <= c && c <= 'Y') return '9';
    return c; 
}

void printchar(char c, int n) {
	int i;
	for (i = 0; i < n; i ++) {
		cout << c;
	}
}

