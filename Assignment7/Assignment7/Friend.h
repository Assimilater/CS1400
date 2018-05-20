#ifndef FRIEND_H
#define FRIEND_H

// External dependencies
#include <iostream>
#include <fstream>
#include <string>

const int NUM_FRIENDS = 5, SCREENNAME_SIZE = 30, INTERESTS_SIZE = 100;
const char* const EMPTY_STRING = "EMPTY";
struct Friend {
	int age;
	char screen_name[SCREENNAME_SIZE];
	char interests[INTERESTS_SIZE];
};

void AddFriend(std::fstream&);
void RemoveFriend(std::fstream&);
void SearchInterest(std::fstream&);
void ModifyFriend(std::fstream&);
void DisplayFriends(std::fstream&);
void ListFriends(std::fstream&);
int CountFriends(std::fstream&);

void PrintFriend(Friend&, int);
bool IsEmpty(Friend&);
void Empty(Friend&);

std::string tolower(std::string);
#endif