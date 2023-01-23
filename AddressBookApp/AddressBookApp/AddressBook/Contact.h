#pragma once

#include <string>
#include <list>
#include <memory>
#include "../DataFormat/Serializer.h"

using namespace std;

struct Contact {
	string firstName;
	string lastName;
	string phoneNumber;
	
	using SerializerClass = shared_ptr<Serializer<Contact>>;
	SerializerClass m_serializer;

	Contact(const string& firstName, const string& lastName, const string& phoneNumber, SerializerClass& serializer) :
		firstName(firstName),
		lastName(lastName),
		phoneNumber(phoneNumber),
		m_serializer(serializer)
	{
	}

	string serialize() const {
		return m_serializer->serialize(*this);
	}
};

using ContactList = list<Contact>;
