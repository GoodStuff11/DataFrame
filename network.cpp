#ifndef SRC_NETWORK_CPP_
#define SRC_NETWORK_CPP_
#include "network.h"

list<Person*> *Network::contactPath(Person *p0, Person *pf,
		list<Person*> *contacted, list<Person*> contactOrder,
		list<int> turnList, int turn) {
	turn++;

	cout << p0->firstName << " " << p0->numContacts << endl;
	contactOrder.push_back(p0);
	if (!(*p0 == pf)) {

		contacted->push_back(p0);
		turnList.push_back(turn);

		for (int i = 0; i < p0->numContacts; i++) {

			//dont go to a place that we've already been to
			cout << turn << "->>" << p0->contacts[i]->firstName << endl;

			if (!in(p0->contacts[i], contacted, turn + 1, &turnList)) {
				list<Person*> *temp = contactPath(p0->contacts[i], pf,
						contacted, contactOrder, turnList, turn);
				if (temp != NULL)
					return temp;
			}
			cout << "out" << endl;
		}
	} else {
		//convert contactOrder into a pointer
		list<Person*> *order = new list<Person*>();

		for (int i = 0; i < order->size(); i++)
			order->push_back(contactOrder.valAt(i));
		cout << "HEYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY" << endl;
		return order;
	}
	return nullptr;
}

Network::Network() {
	people = new list<Person>();
	relationships = new list<int>();
}
Network::~Network() {
	delete people;
	delete relationships;
}
void Network::addPerson(Person p) {
	p.id = people->size();
	people->push_back(p);
}
//doesn't rewrite id's, so wont work with writing to file
void Network::removePerson(Person *p) {
	for (int i = 0; i < people->size(); i++) {
		people->refAt(i)->removeContact(p);
		if (people->valAt(i) == p)
			people->erase(i);
	}
}
int Network::size() {
	return people->size();
}
void Network::addRelationship(int id1, int id2) {
	Person *p1 = people->refAt(id1);
	Person *p2 = people->refAt(id2);
	addRelationship(p1, p2);
}
void Network::addRelationship(Person *p1, Person *p2) {
	p1->addContact(p2);
	p2->addContact(p1);
	relationships->push_back(p1->id);
	relationships->push_back(p2->id);
}
void Network::contactPath(Person *p0, Person *pf) {
	list<Person*> *contacted = new list<Person*>();
	list<Person*> *contactOrder = new list<Person*>();
	list<int> *turnList = new list<int>();
	int turn = 0;

	list<Person*> *path = contactPath(p0, pf, contacted, *contactOrder,
			*turnList, turn);

	for (int i = 0; i < path->size(); i++) {
		cout << path->valAt(i)->firstName << " " << path->valAt(i)->surname
				<< endl;
	}

}
bool Network::in(Person *val, list<Person*> *personList, int turn,
		list<int> *turnList) {
	//dont look at the last one

	cout << turnList->valAt(0) << endl;
	for (int i = 0; i < personList->size() - 1; i++) {

		if (personList->valAt(i) == val && turn > turnList->valAt(i))
			return true;
	}

	return false;
}
Person* Network::getPerson(string firstName, string surname) {
	for (int i = 0; i < people->size(); i++) {
		Person* p = people->refAt(i);
		if (p->firstName == firstName && p->surname == surname)
			return p;
	}
	return nullptr;
}
/*
 * This function does NOT write a struct into the binary file because the
 * struct holds pointers, which become invalid when addresses change in file
 * reading. Rather, it writes all of the contents in order
 * to recreate the commands used to define each person.
 */
void Network::write(char *filename) {
	ofstream file(filename, ios::binary);

	//writing people in
	int n = size();
	file.write((char*) &n, sizeof(int));
	for (int i = 0; i < n; i++) {
		Person p = people->valAt(i);
		file.write(p.firstName, sizeof(p.firstName));
		file.write(p.surname, sizeof(p.surname));

		int age = p.age;
		int height = p.height;
		file.write((char*) &age, sizeof(int));
		file.write((char*) &height, sizeof(int));
	}
	int size = relationships->size();
	file.write((char*) &size, sizeof(int));
	for (int i = 0; i < relationships->size(); i++) {
		int relationship_num = relationships->valAt(i);
		file.write((char*) &relationship_num, sizeof(int));
	}
	file.close();

}
//appends people from binary file to existing network
void Network::read(char* filename) {
	ifstream file(filename, ios::binary);

	int initial_size = people->size();
	//read person from file
	int n;
	file.read((char*) &n, sizeof(int));
	for (int i = 0; i < n; i++) {
		char* first;
		char* last;
		int age;
		int height;

		file.read(first, 10);
		file.read(last, 10);
		file.read((char*) &age, sizeof(int));
		file.read((char*) &height, sizeof(int));

		addPerson(Person(first, last, age, height));
	}
	//read relationship from file
	file.read((char*) &n, sizeof(int));
	for (int i = 0; i < n; i++) {
		int id1;
		int id2;
		file.read((char*) &id1, sizeof(int));
		file.read((char*) &id2, sizeof(int));

		addRelationship(id1 + initial_size, id2 + initial_size);
	}
	file.close();
}

void Network::printNetwork(){
	for (int i=0;i<people->size();i++){
		Person person = people->valAt(i);
		cout << "Name: " << person.firstName << " " << person.surname << endl;
		cout << "Age: " << person.age << endl;
		cout << "Height: " << person.height << endl;
		cout << "Contacts: " << endl;
		for (int j =0;j<person.numContacts;j++){
			Person *contact = person.contacts[j];
			cout << "\t" << contact->firstName << " " << contact->surname << endl;
		}
	}
}
#endif /* SRC_NETWORK_CPP_ */
