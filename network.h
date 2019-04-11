#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include <string>
#include <iostream>
#include <fstream>
#include "list.h"
#include "person.h"

using namespace std;

class Network {
private:
	list<Person*> *contactPath(Person *p0, Person *pf, list<Person*> *contacted,
			list<Person*> contactOrder, list<int> turnList, int turn);
	void addRelationship(int id1, int id2); //a user wouldn't need this
public:
	list<Person> *people;
	list<int> *relationships;
	int size();

	Network();
	virtual ~Network();

	void addPerson(Person p);
	void removePerson(Person *p);

	void addRelationship(Person *p1, Person *p2);

	void contactPath(Person *p0, Person *pf);
	bool in(Person *val, list<Person*> *personList, int turn, list<int> *turnList);
	Person* getPerson(string firstName, string surname);
	void write(char* filename);
	void read(char* filename);
	void printNetwork();
};

#endif /* SRC_PERSON_H_ */
