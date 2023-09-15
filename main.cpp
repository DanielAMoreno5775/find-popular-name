#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Name.h"
using namespace std;



void openInputFile(fstream &);
int readFile(fstream &, Name &);
void getUserInput(Name &);

int main() {
	fstream dataFile;
	Name listOfNamesAndRankings;
	int numOfEntries;

	openInputFile(dataFile);

	numOfEntries = readFile(dataFile, listOfNamesAndRankings);

	listOfNamesAndRankings.sortNames(0, (numOfEntries - 1));
	cout << "The names have been sorted" << endl;

	getUserInput(listOfNamesAndRankings);

	dataFile.close();

	return 0;
}

void openInputFile(fstream& inFile) {
	string filename = "";
	cout << "Please enter the filename and/or the filepath: ";
	cin >> filename;
	inFile.open(filename, ios::in);

	//run if and until the user enters a valid filename/filepath
	while (inFile.fail()) {
		cout << endl << "======================" << endl << "That filename/filepath was invalid." << endl;
		cout << "Please enter the filename and/or the filepath: ";
		cin >> filename;
		inFile.open(filename, ios::in);
	}

	cout << "The names have been read" << endl;
}

int readFile(fstream& file, Name &list) {
	int ranking;
	int numOfEntries = 0;
	string name;
	CommonName* anEntry;

	//reset position in file to beginning
	file.clear();
	file.seekg(0);

	while (file >> ranking) {
		file >> name;
		anEntry = new CommonName(ranking, name);
		list.addName(anEntry);
		numOfEntries++;
	}

	return numOfEntries;
}

void getUserInput(Name &listOfNames) {
	string inputName = "";
	int ordLinear, ordBinary;

	auto startTimeLinear = chrono::high_resolution_clock::now();
	auto endTimeLinear = chrono::high_resolution_clock::now();
	auto startTimeBinary = chrono::high_resolution_clock::now();
	auto endTimeBinary = chrono::high_resolution_clock::now();

	do {
		cout << "Enter a female name, enter STOP to end: ";
		cin >> inputName;

		for (int i = 0; i < inputName.length(); i += 1) {
			inputName[i] = toupper(inputName[i]);
		}

		//don't waste time searching the list if STOP was entered
		if (inputName != "STOP") {
			try {
				//time the linear search
				startTimeLinear = chrono::high_resolution_clock::now();
				ordLinear = listOfNames.findLinear(inputName);
				endTimeLinear = chrono::high_resolution_clock::now();

				//time the binary search
				startTimeBinary = chrono::high_resolution_clock::now();
				ordBinary = listOfNames.findBinary(inputName);
				endTimeBinary = chrono::high_resolution_clock::now();

				//print results
				cout << "Linear search took " << chrono::duration_cast<chrono::microseconds>(endTimeLinear - startTimeLinear).count() << " microseconds" << endl;
				cout << "Binary search took " << chrono::duration_cast<chrono::microseconds>(endTimeBinary - startTimeBinary).count() << " microseconds" << endl;
				cout << inputName << " is the number " << ordBinary << " most popular female name" << endl;

				/*lines do work but aren't useful
				cout << listOfNames[0]->getName() << endl; //overloaded [] operator to grab specific names in the list
				listOfNames = secondListOfNames + 5; //uses overloaded = operator to copy over values
				*/
			}
			catch (string exceptionString) {
				cout << exceptionString << endl;
			}
		}
	} while (inputName != "STOP");
}