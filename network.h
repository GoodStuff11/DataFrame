#ifndef thing
#define thing

#include <iostream>

struct Person {
	int id;
	char firstName[10];
	char surname[10];
	int age;
	int height;

	int numContacts = 0;
	//array of pointers which point to an instance stores in
	//Network's people list
	Person **contacts;
	Person(char *first,char *last,int age,int height);
	void addContact(Person *p);
	void removeContact(Person *p);
	bool operator==(Person *other);

	virtual ~Person();
};
#endif
