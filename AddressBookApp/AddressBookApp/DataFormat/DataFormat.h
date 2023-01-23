#pragma once
#include <string>

using namespace std;

template <typename T>

class DataFormat
{
public:
	~DataFormat() {}
	virtual bool loadData(const string&) = 0;
	virtual bool addData(const string&) = 0;
	virtual bool deleteData(const string&) = 0;
	virtual bool serialize(string&) = 0;
	virtual bool deserialize(list<T>&) = 0;
};

template <typename T>
using DataFormatPtr = shared_ptr<DataFormat<T>>;
