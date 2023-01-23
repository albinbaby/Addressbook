#pragma once
#include <string>
#include <list>
#include "../AddressBook/Contact.h"
#include "Serializer.h"

using namespace std;

class JsonSerializer : public Serializer<Contact>
{
public:
	string serialize(const Contact& contact) {
		string out;
		out = " Contact { First Name : " + contact.firstName + ", " +
			"Last Name : " + contact.lastName + ", " +
			"Phone Number : " + contact.phoneNumber + " }";
		return out;
	}

	list<Contact> deserialize(const string&) {
		return {};
	}
};

