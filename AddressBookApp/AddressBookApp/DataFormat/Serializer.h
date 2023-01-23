#pragma once
#include <string>
#include <list>

using namespace std;

template <typename T>
class Serializer
{
public:
	virtual string serialize(const T&) = 0;
	virtual list<T> deserialize(const string&) = 0;
};

