#ifndef FRIEND_H
#define FRIEND_H
#include <string>

const int NUM_FRIENDS = 5;
const std::string EMPTY_STRING = "EMPTY";
struct Friend {
	int age = 0;
	std::string screen_name = EMPTY_STRING;
	std::string interests = EMPTY_STRING;
};

void AddFriend(Friend friends[], int size);
void RemoveFriend(Friend friends[], int size);
void SearchInterest(Friend friends[], int size);
void DisplayFriends(Friend friends[], int size);
void ListFriends(Friend friends[], int size);
float ReportAge(Friend friends[], int size);

bool IsBefore(Friend &friend1, Friend &friend2);
void BubbleSort(Friend array[], int size);
void Swap(Friend &a, Friend &b);

bool IsEmpty(Friend &a_friend);
void Empty(Friend &a_friend);
std::string tolower(std::string convert);
#endif