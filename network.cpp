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
		cout << "HEYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"<< endl;
		return order;
	}
	return nullptr;
}

Network::Network() {
	people = new list<Person>();
	relationships = 0;
}
Network::~Network() {
	delete people;
}
void Network::addPerson(Person p) {
	p.id = people->size();
	people->push_back(p);
}
void Network::removePerson(Person *p) {
	for (int i = 0; i < people->size(); i++) {
		people->refAt(i)->removeContact(p);
		if (people->valAt(i) == p)
			people->erase(i);
	}
}
int Network::size(){
	return people->size();
}
void Network::addRelationship(Person *p1, Person *p2) {
	p1->addContact(p2);
	p2->addContact(p1);
	relationships.push_back(p1->id);
	relationships.push_back(p2->id);
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
void Network::write(char *filename){
	ofstream file (filename,ios::binary);

	//writing people in
	int n = size();
	file.write((char*)&n, sizeof(int));
	for (int i=0;i<n;i++){
		Person p = people->valAt(i);
		file.write(p.firstName,sizeof(people->valAt(i).firstName));
		file.write(p.surname,sizeof(p.surname));
		file.write((char*)&p.age,sizeof(p.age));
		file.write((char*)&p.height,sizeof(p.height));
	}
	file.write((char*)&numrelationships,sizeof(int));


}

#endif /* SRC_NETWORK_CPP_ */
