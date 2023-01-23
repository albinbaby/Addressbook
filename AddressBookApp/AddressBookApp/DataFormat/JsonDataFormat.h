#pragma once
#include <string>
#include "DataFormat.h"

using namespace std;

template <typename T>
class JsonDataFormat : public DataFormat<T>
{
public:
	~JsonDataFormat() {}

	bool loadData(const string& data) {
		return true;
	}

	bool addData(const string& data) {
		return true;
	}

	bool deleteData(const string& data) {
		return true;
	}

	bool serialize(string& data) {
		return true;
	}
	
	bool deserialize(list<T>&) {
		return true;
	}
};

