// AddressBookApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AddressBook/AddressBookApp.h"

#define THREAD_SAFE 0

void displayContacts(const list<string> contacts)
{
    for (auto const& contact : contacts) {
        cout << contact << "\n";
    }
}

int main()
{
#if THREAD_SAFE
    auto addressBookAppPtr = AddressBookApp<AddressBookThreadSafe>::createThreadSafe("ContactsDatabase.json");
#else
    auto addressBookAppPtr = AddressBookApp<AddressBook>::create("ContactsDatabase.json");
#endif

    addressBookAppPtr->addContact("Albin", "Baby");
    addressBookAppPtr->addContact("Dlbin", "Baby");
    addressBookAppPtr->addContact("Clbin", "Baby");
    addressBookAppPtr->addContact("Wlbin", "Baby");
    addressBookAppPtr->addContact("Glbin", "Baby");
    addressBookAppPtr->addContact("Albert", "Einstein", "+49 556622");

    auto contacts = addressBookAppPtr->getContactsOrderbyFirstname();
    displayContacts(contacts);

    cout << "\nOne contact deleted\n";
    addressBookAppPtr->deleteContact("Glbin", "Baby");
    contacts = addressBookAppPtr->getContactsOrderbyFirstname();
    displayContacts(contacts);

    cout << "\nNon existent contact deleted\n";
    addressBookAppPtr->deleteContact("Glbin", "Baby");
    contacts = addressBookAppPtr->getContactsOrderbyFirstname();
    displayContacts(contacts);

    cout << "\nNon contact ordered by last name\n";
    contacts = addressBookAppPtr->getContactsOrderbyLastname();
    displayContacts(contacts);

    cout << "\nContacts starts with a prefix Alb\n";
    contacts = addressBookAppPtr->getContactsStartsWith("alb");
    displayContacts(contacts);

    cout << "\nContacts starts with a prefix Ein\n";
    contacts = addressBookAppPtr->getContactsStartsWith("Ein");
    displayContacts(contacts);

    cout << "\nContacts starts with a prefix Iamnotinthelist\n";
    contacts = addressBookAppPtr->getContactsStartsWith("Iamnotinthelist");
    displayContacts(contacts);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
