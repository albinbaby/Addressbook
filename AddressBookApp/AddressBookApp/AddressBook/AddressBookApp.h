#pragma once
#include "AddressBook.h"
#include "AddressBookThreadSafe.h"
#include "../Database/Database.h"
#include "../DataFormat/DataFormat.h"
#include "../DataFormat/Serializer.h"

using ContactDatabasePtr = shared_ptr<Database<Contact>>;
using ContactSerializerPtr = shared_ptr<Serializer<Contact>>;

template <typename AddressBookT>
class AddressBookApp;

template <typename AddressBookT>
using AddressBookAppPtr = shared_ptr<class AddressBookApp<AddressBookT>>;

template <typename AddressBookT>
using AddressBookPtr = shared_ptr<AddressBookT>;

template <typename AddressBookT>
class AddressBookApp {
private:
	
	ContactDatabasePtr m_contactDatabasePtr;
	ContactSerializerPtr m_contactSerializerPtr;
	DataFormatPtr<Contact> m_dataFormatPtr;
	AddressBookPtr<AddressBookT> m_addressBookPtr;

	AddressBookApp(ContactDatabasePtr& contactDatabase, ContactSerializerPtr& contactSerializer, AddressBookPtr<AddressBookT> addressBookPtr);

public:
	~AddressBookApp() {}

	static AddressBookAppPtr<AddressBook> create(const string& filename);
	static AddressBookAppPtr<AddressBookThreadSafe> createThreadSafe(const string& filename);
	bool load();
	
	bool addContact(const string& firstName, const string& lastName, const string& phoneNumber = string());
	bool deleteContact(const string& firstName, const string& lastName);
	list<string> getContactsOrderbyFirstname();
	list<string> getContactsOrderbyLastname();
	list<string> getContactsStartsWith(const string& prefix);
};

template class AddressBookApp<AddressBook>;
template class AddressBookApp<AddressBookThreadSafe>;
