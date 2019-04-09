#ifndef thing
#define thing

#include <iostream>

struct Person {
	char *firstName;
	char *surname;
	int age;
	double height;

	int numContacts = 0;
	//array of pointers which point to an instance stores in
	//Network's people list
	Person **contacts;
	Person(char *first,char *last,int age,double height);
	void addContact(Person *p);
	void removeContact(Person *p);
	const bool operator==(const Person *other) const;
	bool operator==(Person *other);

	virtual ~Person();
};
#endif
