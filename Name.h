#pragma once
#include "CommonName.h"
#include <string>
using namespace std;

class Name {
private:
	static const int SIZE_OF_ARRAY = 1000; //can hardcode 1000 elements as always that many

	CommonName *namePair[SIZE_OF_ARRAY];
	int nextName;

	int findRecursive(string, int, int);
	void swap(CommonName* &, CommonName* &);
	int partition(int, int);
public:
	Name();
	Name(const Name &);
	~Name();
	void addName(CommonName *);
	void sortNames(int, int);
	int findLinear(string);
	int findBinary(string);

	const Name operator=(const Name &);
	CommonName * &operator[] (const int &);
};

