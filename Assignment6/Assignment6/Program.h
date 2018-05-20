#ifndef PROGRAM_H
#define PROGRAM_H

// External Dependencies
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// Struct Word for simplicity
struct Word {
	std::string text;
	std::vector<int> lines;
	int occurs;
};

// Prototypes
bool hasLetter(std::string);
void addWord(std::map<std::string, Word*>&, std::string, int);
void doSearch(const std::vector<std::string>&, const std::string &);

#endif