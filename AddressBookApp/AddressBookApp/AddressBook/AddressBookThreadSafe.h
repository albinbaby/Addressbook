#pragma once
#include <memory>
#include "AddressBook.h"

using namespace std;

class AddressBookThreadSafe
{
private:
	unique_ptr<AddressBook> m_addressBook;
	mutex m_mutex;
	using Lock = lock_guard<mutex>;

public:
	AddressBookThreadSafe(unique_ptr<AddressBook>& addressBook) :
		m_addressBook(std::move(addressBook))
	{	
	}

	void initialize(const ContactList& contactList) {
		Lock lock(m_mutex);
		m_addressBook->initialize(contactList);
	}

	bool addContact(const Contact& contact) {
		Lock lock(m_mutex);
		return m_addressBook->addContact(contact);
	}

	bool deleteContact(const Contact& contact) {
		Lock lock(m_mutex);
		return m_addressBook->deleteContact(contact);
	}

	list<string> getContactsOrderbyFirstname() {
		Lock lock(m_mutex);
		return m_addressBook->getContactsOrderbyFirstname();
	}

	list<string> getContactsOrderbyLastname() {
		Lock lock(m_mutex);
		return m_addressBook->getContactsOrderbyLastname();
	}

	list<string> getContactsStartsWith(const string& prefix) {
		Lock lock(m_mutex);
		return m_addressBook->getContactsStartsWith(prefix);
	}
};

