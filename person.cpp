#include "person.h"

Person::Person(char *first,char *last,int age,double height){
	firstName = first;
	surname = last;
	this->age = age;
	this->height = height;
	contacts = NULL;
}

void Person::addContact(Person *p) {

	Person **newContacts = new Person*[numContacts + 1];

	for (int i = 0; i < numContacts; i++) {
		newContacts[i] = contacts[i];
	}
	newContacts[numContacts] = p;

	if (contacts != NULL)
		delete contacts;
	contacts = newContacts;
	numContacts++;
}

void Person::removeContact(Person *p) {
	int i;
	for (i = 0; i < numContacts || contacts[i] == p; i++)
		;
	if (i == numContacts)
		return;

	Person **newContacts = new Person*[numContacts - 1];

	{
		int j;
		int k;
		for (j = 0, k = 0; j < numContacts - 1; j++) {
			//skip over deleted values
			if (j == i)
				k++;
			newContacts[j] = contacts[k];
		}
	}
	if (contacts != NULL)
		delete contacts;
	contacts = newContacts;

	numContacts--;
}
const bool Person::operator==(const Person *other) const {
	if (this->surname == other->surname && this->firstName == other->firstName
			&& this->contacts == other->contacts)
		return true;
	return false;
}
bool Person::operator==(Person *other) {
	if (this->surname == other->surname && this->firstName == other->firstName
			&& this->contacts == other->contacts)
		return true;
	return false;
}
Person::~Person() {
	delete contacts;
}
