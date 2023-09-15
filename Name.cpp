#pragma once
#include "Name.h"
#include <iostream>
using namespace std;

Name::Name() { //constructor
	nextName = 0;
	for (int i = 0; i < SIZE_OF_ARRAY; i += 1) {
		namePair[i] = nullptr;
	}
}

Name::Name(const Name &obj) { //copy constructor
	nextName = obj.nextName;
	if (nextName > 0) {
		nextName = obj.nextName;
		for (int count = 0; count < nextName; count += 1)
			namePair[count] = obj.namePair[count];
	}
}

Name::~Name() { //destructor
	if (nextName > 0)
		for (int i = 0; i < nextName; i += 1)
			delete namePair[i];
}

void Name::addName(CommonName * pair) {
	namePair[nextName] = pair;
	nextName += 1;
}

//uses the quicksort algorithm
void Name::sortNames(int start, int end) {
	int pivotPoint = 0;
	if (start < end) {
		pivotPoint = partition(start, end);
		sortNames(start, pivotPoint - 1);
		sortNames(pivotPoint + 1, end);
	}
}

int Name::findLinear(string name) {
	int index = 0;
	int position = -1;
	int ord = -1;
	bool found = false;
	string currentEntry = "";
	string exceptionString = name + " is not on the list";

	while (index < (nextName) && !found) {
		currentEntry = namePair[index]->getName();
		//if the name is found
		if (currentEntry == name) {
			found = true;
			position = index;
		}
		index += 1;
	}

	if (position == -1) {
		throw exceptionString;
	}
	else {
		ord = namePair[position]->getOrdinal();
	}

	return ord; //will return -1 if name is not found
}

int Name::findBinary(string name) {
	int position = -1;
	int ord = -1;
	string exceptionString = name + " is not on the list";

	position = findRecursive(name, 0, nextName - 1);

	if (position == -1) {
		throw exceptionString;
	}
	else {
		ord = namePair[position]->getOrdinal();
	}

	return ord; //will return -1 if name is not found
}

CommonName * &Name::operator[] (const int &sub) { //overloaded [] operator
	if (sub < 0 || sub >= nextName) {
		cout << "ERROR: Subscript out of range\n";
		exit(0);
	}
	return namePair[sub];
}

const Name Name::operator=(const Name &right) { //overloaded = operator
	if (this != &right) {
		if (nextName > 0) {
			for (int i = 0; i < nextName; i += 1)
				delete namePair[i];
			nextName = right.nextName;
			for (int count = 0; count < nextName; count += 1)
				namePair[count] = right.namePair[count];
		}
	}
	return *this;
}

/*private member functions after this point*/

int Name::findRecursive(string name, int low, int high) {
	int position = -1;
	int middle = 0;
	string middleValue = "";

	if (low > high) {
		return position;
	}

	middle = (low + high) / 2;
	middleValue = namePair[middle]->getName();
	if (middleValue == name) {
		return middle;
	}
	else if (middleValue < name) {
		return findRecursive(name, middle + 1, high);
	}
	else {
		return findRecursive(name, low, middle - 1);
	}

	return position; //here in case of error
}

//the following two functions exist for the QuickSort function
void Name::swap(CommonName* &val1, CommonName* &val2) {
	CommonName* temp = val1;
	val1 = val2;
	val2 = temp;
}

int Name::partition(int start, int end) {
	int pivotIndex = 0, midIndex = 0;
	string pivotValue = "", scanValue = "";

	midIndex = (start + end) / 2;
	swap(namePair[start], namePair[midIndex]);
	pivotIndex = start;
	pivotValue = namePair[start]->getName();

	for (int scan = start + 1; scan <= end; scan++) {
		scanValue = namePair[scan]->getName();

		if (scanValue < pivotValue) {
			pivotIndex += 1;
			swap(namePair[pivotIndex], namePair[scan]);
		}
	}
	swap(namePair[start], namePair[pivotIndex]);
	return pivotIndex;
}