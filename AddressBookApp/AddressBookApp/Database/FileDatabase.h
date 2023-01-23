#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include "Database.h"
#include "../DataFormat/DataFormat.h"
#include "../AddressBook/Contact.h"

template <typename T>
class FileDatabase : public Database<T>
{
private:
	fstream m_fileStream;
	DataFormatPtr<T> m_dataFormatPtr;

	bool openDatabase() {
		std::stringstream buffer;
		buffer << m_fileStream.rdbuf();
		m_dataFormatPtr->loadData(buffer.str());
		return false;
	}

public:
	FileDatabase(const string& filename, DataFormatPtr<T>& dataFormat) :
		m_fileStream(filename),
		m_dataFormatPtr(dataFormat) {
		openDatabase();
	}

	~FileDatabase() {
		m_fileStream.close();
	}

	bool addData(const T& data) {
		return m_dataFormatPtr->addData(data.serialize());
	}

	bool deleteData(const T& data) {
		return m_dataFormatPtr->deleteData(data.serialize());
	}

	bool commitData() {
		string data;
		m_dataFormatPtr->serialize(data);
		m_fileStream.write(data.c_str(), data.length());
		return true;
	}

	virtual list<T> getAllData() {
		list<T> objects;
		m_dataFormatPtr->deserialize(objects);
		return objects;
	}
};

