#pragma once
#include <string>
using namespace std;

class CommonName {
private:
	int ordinal;
	string name;
public:
	CommonName(int, string);
	int getOrdinal();
	string getName();
};

