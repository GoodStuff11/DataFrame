#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Person{
private:
public:
    string firstName;
    string surname;
    int age;
    double height;

    int numContacts = 0;

    double *contactFrequency;
    Person *contacts;

    void addContact(Person *p, double frequency){
        double *newContactFrequency = new double[numContacts + 1];
        Person *newContacts = new Person[numContacts + 1];

        for (int i=0;i<numContacts-1;i++){
            newContactFrequency[i] = contactFrequency[i];
            newContacts[i] = contacts[i];
        }
        newContactFrequency[numContacts] = frequency;
        newContacts[numContacts] = *p;

        delete contacts;
        delete contactFrequency;

        contactFrequency = newContactFrequency;
        contacts = newContacts;

        delete newContactFrequency;
        delete newContacts;

        numContacts++;
    }
    void removeContact(Person *p){
        int i;
        for (i = 0; i < numContacts || contacts[i] == p;i++);
        if (i == numContacts)
            return;

        double *newContactFrequency = new double[numContacts - 1];
        Person *newContacts = new Person[numContacts - 1];

        {
            int j;
            int k;
            for (j=0,k=0; j < numContacts - 1;j++){
                //skip over deleted values
                if (j == i)
                    k++;
                newContactFrequency[j] = contactFrequency[k];
                newContacts[j] = contacts[k];
            }
        }
        delete contacts;
        delete contactFrequency;

        contactFrequency = newContactFrequency;
        contacts = newContacts;

        delete newContactFrequency;
        delete newContacts;

        numContacts--;
    }
    bool operator==(Person *other){
        if (this->surname == other->surname &&
            this->firstName == other->firstName &&
            this->contactFrequency == other->contactFrequency &&
            this->contacts == other->contacts)
            return true;
        return false;
    }
    ~Person(){
        delete contactFrequency;
        delete contacts;
    }
};


class Network{
private:
    vector <Person> *people;
public:
    Network(){
        people = new vector <Person>();
    }
    ~Network(){
        delete people;
    }
    void addPerson(Person *p){
        people->push_back(*p);
    }
    void removePerson(Person *p){
        for(int i = 0;i<people->size();i++){
            people->at(i).removeContact(p);
            if (people->at(i) == p)
                people->erase(people->begin() + i);
        }
    }
    void addRelationship(Person *p1,Person *p2, double frequency){
        p1->addContact(p2,frequency);
        p2->addContact(p1,frequency);
    }

    
};
int main(){
    Network *net = new Network();

    Person Mike = {"Mike", "Ze", 50,180};
    Person Joe = {"Joe", "Ze",30,170,0};
    Person Larry = {"Larry", "S'ux",13,150};

    net->addPerson(&Mike);
    net->addPerson(&Joe);
    net->addPerson(&Larry);

    net->addRelationship(&Mike,&Joe,1);

    delete net;  
}
