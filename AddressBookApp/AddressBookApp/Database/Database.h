#pragma once
#include <list>

using namespace std;

template <typename T>
class Database
{
public:
	virtual ~Database() {};
	virtual bool openDatabase() = 0;
	virtual bool addData(const T&) = 0;
	virtual bool deleteData(const T&) = 0;
	virtual bool commitData() = 0;
	virtual list<T> getAllData() = 0;
};
