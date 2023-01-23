#pragma once

#include <list>
#include <map>
#include <mutex>
#include "Contact.h"

using namespace std;

class AddressBook
{
private:
	ContactList m_contactList;
	using ContactListEntry = ContactList::iterator;
	using FirstName = string;
	using LastName = string;
	using FullName = string;
	map<FullName, ContactListEntry> m_contactNameMap;
	template <typename T>
	list<string> getContactsOrderby(T compare);

public:
	void initialize(const ContactList& contactList);
	bool addContact(const Contact& contact);
	bool deleteContact(const Contact& contact);
	list<string> getContactsOrderbyFirstname();
	list<string> getContactsOrderbyLastname();
	list<string> getContactsStartsWith(const string& prefix);
};

