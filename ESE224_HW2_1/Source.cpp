/*
Given an arbitrary ransom note, consisting of 15 − 20 words and several magazines, write a
function that will return a true, if the ransom note can be constructed from the words in
the magazines, otherwise it will return a false. Each word in the magazines can only be
used once in your ransom note. The algorithm should work efficiently, such as, utilizing
hash tables for storing and looking up strings. An example hash function maybe the sum
of the ascii values of all the characters in the string, modulus an appropriate positive
integer. For testing the code, utilize the ransom note and the magazines provided on
Blackboard in files RansomNote.dat, Magazine1.dat, Magazine2.dat, Magazine3.dat,
Magazine4.dat, Magazine5.dat and Magazine6.dat.

In this problem, you will utilize the built in string class, its constructors, some of its
methods and operators. For more on the string class, please refer to Prata, Chapter 16
and the link http : //www.cplusplus.com/reference/string/string/ (6 points)

Choose the number of words to print to screen, set the variable PrintWordCount = 200 (for example). Print words to the screen at each of the following steps:
	After reading words from magazines in the files.
	After removing punctuation
	If you are using vector and sort, then print the first 200 or so words after sorting. If you are using a hash map, then print the first 200 or so words in the map.
	For each word in the ransom note, found or not found.
*/

//Erik Bracamonte - 111230826 - ESE 224
#define _crt_secure_no_warnings
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<string, int>::iterator it;
bool constructedNote(vector<string> ransom, vector<string> magazine);
int storeFilewords(string fileName, vector<string>& storage, int &counter);
void RemovePunctuations(string &st);

//-------------------------------------------------------------------------
int main() {
	string magazines, ransom = "RansomNote.dat";
	vector<string> ransomWords, magazineWords;

	int printWordCount = 200;	//Changing the amount will change the amount of words that will be shown in the output
	int *pWC = &printWordCount;
	
	cout << "Reading words from magazines in the file (only " << printWordCount << " words outputted)" << endl;
	for (int i = 1; i < 7; i++) {
		magazines = "Magazine" + to_string(i) + ".dat";
		storeFilewords(magazines, magazineWords, printWordCount);
	}

	cout << "\n\nWithout punctuation" << endl;
	for (int i = 0; i<200; i++) {
		cout << magazineWords[i] << " ";
	}
	
	storeFilewords(ransom, ransomWords, printWordCount);

	if (constructedNote(ransomWords, magazineWords)) {
		cout << "Its possible to construct ransom note with the given magazines." << endl;
	}
	else {
		cout << "Cant construct ransom note with given magazines." << endl;
	}
	system("pause");
	return 0;
}

/*---------------------------------------------------------------------
Used to store each word in their respective vector "storage" location. The ransom note is stored
into a vector consisting only of its words. Magazine words are stored into its own vector.
---------------------------------------------------------------------*/
int storeFilewords(string fileName, vector<string>& storage, int &pWC) {
	string words;
	ifstream file(fileName);
	if (!file) {
		cout << "File unable to open.\n";
		return 0;
	}

	while (file >> words) {
		--pWC;
		if (pWC >= 0) {
			cout << words << " ";
		}
		RemovePunctuations(words);
		storage.push_back(words);
	}
	return 1;
}

/*---------------------------------------------------------------------
Map each magazine strings as our key value and use the int value as the number of times the magazine
word can be used. We use the strings in ransom to locate the words in our map.
---------------------------------------------------------------------*/
bool constructedNote(vector<string> ransom, vector<string> magazine) {
	unordered_map<string, int> map;
	int canConstruct = 1;
	int printWordCounter = 200;
	if (magazine.size() < ransom.size()) {
		cout << "\nER0" << endl;
		return false;
	}

	for (int i = 0; i < magazine.size(); i++) {
		it = map.find(magazine[i]);     //Locates the word
		if (it == map.end()) {          //If not found, create a new element and initilize to 1
			map.insert(pair<string, int>(magazine[i], 1));
		}
		else {
			map[magazine[i]]++;         //If the word is found in the map, increment it
		}
	}

	cout << "\n\nOutputting the first 200 words of the map" << endl;
	for (it = map.begin(); it != map.end(); ++it) {
		if (printWordCounter >= 0) {
			cout << it->first << " ";
			--printWordCounter;
		}
	}

	cout << "\n" << endl;
	for (int i = 0; i < ransom.size(); i++) {
		it = map.find(ransom[i]);   //Locate the word from our ransom note in the map
		cout << "'" << ransom[i];
		if (it == map.end()) {      //if not found, return false
			cout <<"' not found." << endl;
			--canConstruct;
			continue;
		}
		else if (it->second == 0) { //If the word is found but has been used up already,
			cout << "' found but was already used up." << endl;
			--canConstruct;
			continue;           //then return false
		}
		else {
			cout << "' found." << endl;
			map[ransom[i]]--;       //If the word is found and its not empty, decrement it
		}
	}
	if (canConstruct != 1) { return false; }
	else { return true; }
}

/*-------------------------------------------------------------------------
Removing all punctuation from a word
-------------------------------------------------------------------------*/
void RemovePunctuations(string &st) {
	int ASCIIVal;
	for (ASCIIVal = 33; ASCIIVal <= 46; ASCIIVal++) {
		st.erase(remove(st.begin(), st.end(), ASCIIVal), st.end());
	}
	for (ASCIIVal = 58; ASCIIVal <= 64; ASCIIVal++) {
		st.erase(remove(st.begin(), st.end(), ASCIIVal), st.end());
	}
	for (ASCIIVal = 91; ASCIIVal <= 96; ASCIIVal++) {
		st.erase(remove(st.begin(), st.end(), ASCIIVal), st.end());
	}
	for (ASCIIVal = 123; ASCIIVal <= 126; ASCIIVal++) {
		st.erase(remove(st.begin(), st.end(), ASCIIVal), st.end());
	}

}