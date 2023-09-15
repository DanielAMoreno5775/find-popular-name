#pragma once
#include "CommonName.h"
#include <cctype>

CommonName::CommonName(int ord, string aName) {
	ordinal = ord;
	for (int i = 0; i < aName.length(); i += 1) {
		aName[i] = toupper(aName[i]);
	}
	name = aName;
}

int CommonName::getOrdinal() {
	return ordinal;
}

string CommonName::getName() {
	return name;
}