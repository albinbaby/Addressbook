#include "AddressBookApp.h"
#include "../DataFormat/JsonDataFormat.h"
#include "../DataFormat/JsonSerializer.h"
#include "../Database/FileDatabase.h"

template <typename AddressBookT>
AddressBookApp<AddressBookT>::AddressBookApp(
	ContactDatabasePtr& contactDatabasePtr, ContactSerializerPtr& contactSerializerPtr, AddressBookPtr<AddressBookT> addressBookPtr) :
	m_contactDatabasePtr(contactDatabasePtr),
	m_contactSerializerPtr(contactSerializerPtr),
	m_addressBookPtr(addressBookPtr)
{
}

AddressBookAppPtr<AddressBook> AddressBookApp<AddressBook>::create(const string& filename)
{
	AddressBookPtr<AddressBook> addressBookPtr(new AddressBook);
	DataFormatPtr<Contact> dataFormatPtr(new JsonDataFormat<Contact>());
	ContactDatabasePtr contactDatabasePtr(new FileDatabase<Contact>(filename, dataFormatPtr));
	ContactSerializerPtr contactSerializerPtr(new JsonSerializer);
	return AddressBookAppPtr<AddressBook>(new AddressBookApp(contactDatabasePtr, contactSerializerPtr, addressBookPtr));
}

AddressBookAppPtr<AddressBookThreadSafe> AddressBookApp<AddressBookThreadSafe>::createThreadSafe(const string& filename)
{
	auto addressBookPtr = make_unique<AddressBook>();
	AddressBookPtr<AddressBookThreadSafe> addressBookThreadSafePtr(new AddressBookThreadSafe(addressBookPtr));

	DataFormatPtr<Contact> dataFormatPtr(new JsonDataFormat<Contact>());
	ContactDatabasePtr contactDatabasePtr(new FileDatabase<Contact>(filename, dataFormatPtr));
	ContactSerializerPtr contactSerializerPtr(new JsonSerializer);
	return AddressBookAppPtr<AddressBookThreadSafe>(new AddressBookApp(contactDatabasePtr, contactSerializerPtr, addressBookThreadSafePtr));
}

template <typename AddressBookT>
bool AddressBookApp<AddressBookT>::load()
{
	m_contactDatabasePtr->openDatabase();
	m_addressBookPtr->initialize(m_contactDatabasePtr->getAllData());
	return true;
}

template <typename AddressBookT>
bool AddressBookApp<AddressBookT>::addContact(const string& firstName, const string& lastName, const string& phoneNumber)
{
	Contact contact(firstName, lastName, phoneNumber, m_contactSerializerPtr);
	m_addressBookPtr->addContact(contact);
	m_contactDatabasePtr->addData(contact);
	return true;
}

template <typename AddressBookT>
bool AddressBookApp<AddressBookT>::deleteContact(const string& firstName, const string& lastName)
{
	Contact contact(firstName, lastName, "", m_contactSerializerPtr);
	m_addressBookPtr->deleteContact(contact);
	m_contactDatabasePtr->deleteData(contact);
	return true;
}

template <typename AddressBookT>
list<string> AddressBookApp<AddressBookT>::getContactsOrderbyFirstname()
{
	return m_addressBookPtr->getContactsOrderbyFirstname();
}
template <typename AddressBookT>
list<string> AddressBookApp<AddressBookT>::getContactsOrderbyLastname()
{
	return m_addressBookPtr->getContactsOrderbyLastname();
}

template <typename AddressBookT>
list<string> AddressBookApp<AddressBookT>::getContactsStartsWith(const string& prefix)
{
	return m_addressBookPtr->getContactsStartsWith(prefix);
}
