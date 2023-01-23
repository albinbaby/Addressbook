#include <algorithm>
#include "AddressBook.h"

void to_upper(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void AddressBook::initialize(const ContactList& contactList)
{
	m_contactList = contactList;
}

bool AddressBook::addContact(const Contact& contact)
{
	FullName fullName = contact.firstName + contact.lastName;

	if (m_contactNameMap.find(fullName) != m_contactNameMap.end()) {
		m_contactList.erase(m_contactNameMap[fullName]);
	}

	m_contactList.push_back(contact);
	m_contactNameMap[fullName] = prev(m_contactList.end());
	return true;
}

bool AddressBook::deleteContact(const Contact& contact)
{
	FullName fullName = contact.firstName + contact.lastName;

	if (m_contactNameMap.find(fullName) != m_contactNameMap.end()) {
		m_contactList.erase(m_contactNameMap[fullName]);
		m_contactNameMap.erase(fullName);
	}

	return true;
}

template <typename T>
list<string> AddressBook::getContactsOrderby(T compare)
{
	m_contactList.sort(compare);

	list<string> contacts;
	for (const auto& contact : m_contactList)
	{
		contacts.push_back(contact.serialize());
	}
	return contacts;
}

list<string> AddressBook::getContactsOrderbyFirstname()
{	
	return getContactsOrderby(
		[](Contact contact1, Contact contact2) {
			return contact1.firstName < contact2.firstName;
		});
}

list<string> AddressBook::getContactsOrderbyLastname()
{
	return getContactsOrderby(
		[](Contact contact1, Contact contact2) {
			return contact1.lastName < contact2.lastName;
		});
}

list<string> AddressBook::getContactsStartsWith(const string& prefixStr)
{
	string prefix = prefixStr;
	to_upper(prefix);

	list<string> contacts;
	for (const auto& contact : m_contactList) {
		string firstName = contact.firstName;
		string lastName = contact.lastName;
		to_upper(firstName);
		to_upper(lastName);
		if(firstName.substr(0, prefix.length()) == prefix || lastName.substr(0, prefix.length()) == prefix) {
			contacts.push_back(contact.serialize());
		}
	}
	return contacts;
}
