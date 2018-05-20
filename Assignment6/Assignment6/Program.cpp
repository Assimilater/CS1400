//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Assignment 6: C-String and String                                               |
//---------------------------------------------------------------------------------+
#include "Program.h"
using namespace std;

int main() {
	extern char **environ; // needed to access your execution environment
	const char* SEPARATOR = "------------------------------------------------------------";
	
	// Variables for managing textual data
	typedef map<string, Word*>::iterator word_iterator;
	map<string, Word*> words;
	vector<string> lines;
	stringstream parser, buffer;
	char c;

	// Dump the environment
	int k = 0;
	while (environ[k] != NULL) {
		lines.push_back(string(environ[k]));
		cout << environ[k] << endl;
		k++;
	}

	// Parse words from the environment
	for (unsigned int i = 0; i < lines.size(); i++) {
		buffer.str(string());
		parser.str(lines[i]);
		while (!parser.eof()) {
			parser >> c;
			if (isalnum(c) || c == '_') {
				// This is a legal word-character, add it to the buffer
				buffer << (char)tolower(c);
			}
			else {
				// We have reached a word-delimiting character, add the word to the map if valid
				addWord(words, buffer.str(), i);
				buffer.str(string());
			}
		}

		// We have reached the end of the line, add the word to the map if valid
		addWord(words, buffer.str(), i);
		buffer.str(string());
		parser.clear();
	}

	// Report analysis of environment
	cout << endl
		<< endl
		<< SEPARATOR
		<< endl
		<< endl
		<< "Textual Population Density Analysis: " << endl
		<< endl;

	// Variables for counting sums
	int word_cnt = 0, unique_cnt = 0;

	// Show the number of occurrences of each word
	for (word_iterator i = words.begin(); i != words.end(); i++) {
		// Increment counters
		unique_cnt++;
		word_cnt += i->second->occurs;

		// Output information for this word
		cout << i->first << ": " << i->second->occurs << " occurrence"
			<< (i->second->occurs != 1 ? "s" : "")
			<< endl;
	}
	cout << endl
		<< "Total number of words: " << word_cnt << endl
		<< "Total number of unique words: " << unique_cnt << endl
		<< endl;

	// Prompt the user for search queries with "END" as an exit flag
	string Query;
	cout << SEPARATOR << endl << endl;
	cout << "Enter a search query: "; getline(cin, Query); cout << endl;
	transform(Query.begin(), Query.end(), Query.begin(), ::toupper);
	while (Query != string("END")) {
		doSearch(lines, Query);

		cout << SEPARATOR << endl << endl;
		cout << "Enter a search query: "; getline(cin, Query); cout << endl;
		transform(Query.begin(), Query.end(), Query.begin(), ::toupper);
	}
	
	// Clean up dynamically allocated memory
	for (word_iterator i = words.begin(); i != words.end(); i++) {
		delete i->second;
		i->second = NULL;
	}

	system("pause");
	return 0;
}

//---------------------------------------------------------------------------------+
// bool hasLetter                                                                  |
// Return true if a string has at least letter (regex: [a-zA-Z])                   |
//---------------------------------------------------------------------------------+
bool hasLetter(string s) {
	for (unsigned int i = 0; i < s.length(); i++) {
		if (isalpha(s[i])) {
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------+
// void addWord                                                                    |
// Determine if s is a word, add it to the map and record the line it occurs on    |
//---------------------------------------------------------------------------------+
void addWord(map<string, Word*>& words, string s, int line) {
	if (s.length() > 1 && hasLetter(s)) {
		// We have found a valid word
		if (words.find(s) == words.end()) {
			// Key not found, create new word
			Word *w = new Word;
			w->text = s;
			w->lines.push_back(line);
			w->occurs = 1;

			// Insert new word into the map
			words[s] = w;
		}
		else {
			// Increase the occurrence count of this word
			words[s]->occurs += 1;

			// Add this line occurrence to the list if not already added
			if (find(words[s]->lines.begin(), words[s]->lines.end(), line) != words[s]->lines.end()) {
				words[s]->lines.push_back(line);
			}
		}
	}
}

//---------------------------------------------------------------------------------+
// void doSearch                                                                   |
// Go through each line and find all occurences of Query, case-insensitive         |
//---------------------------------------------------------------------------------+
void doSearch(const vector<string> &lines, const string &Query) {
	string upper; int cnt, pos; bool found = false;
	for (unsigned int i = 0; i < lines.size(); i++) {
		cnt = 0; pos = 0; upper = lines[i];
		transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

		pos = upper.find(Query);
		while (pos != string::npos) {
			cnt++;

			upper = upper.substr(pos + 1, string::npos);
			pos = upper.find(Query);
		}

		if (cnt != 0) {
			found = true;
			cout << "Line " << i + 1 << " - Found " << cnt << " Match" << (cnt > 1 ? "es" : "") << ":" << endl
				<< lines[i] << endl
				<< endl;
		}
	}
	if (!found) { cout << "No matches found..." << endl << endl; }
}
