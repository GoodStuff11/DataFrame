#include <string>
#include <iostream>
#include "list.cpp"

using namespace std;

struct Person{
private:
public:
    string firstName;
    string surname;
    int age;
    double height;

    int numContacts = 0;
    //array of pointers which point to an instance stores in 
    //Network's people list
    Person **contacts;

    void addContact(Person *p){
        
        Person **newContacts = new Person*[numContacts + 1];

        for (int i=0;i<numContacts;i++){
            newContacts[i] = contacts[i];
        }
        newContacts[numContacts] = p;

        if (contacts != NULL)
            delete contacts;
        contacts = newContacts;
        numContacts++;
    }
    void removeContact(Person *p){
        int i;
        for (i = 0; i < numContacts || contacts[i] == p;i++);
        if (i == numContacts)
            return;

        Person **newContacts = new Person*[numContacts - 1];

        {
            int j;
            int k;
            for (j=0,k=0; j < numContacts - 1;j++){
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
    const bool operator==(const Person *other) const{
        if (this->surname == other->surname &&
            this->firstName == other->firstName &&
            this->contacts == other->contacts)
            return true;
        return false;
    }
    bool operator==(Person *other){
        if (this->surname == other->surname &&
            this->firstName == other->firstName &&
            this->contacts == other->contacts)
            return true;
        return false;
    }

    ~Person(){
        delete contacts;
    }
};


class Network{
private:
    list <Person> *contactPath(const Person *p0, const Person *pf,list <Person> *contacted, list <Person> contactOrder,list<int> turnList, int turn){
        turn++;
        cout<<p0->firstName<<" "<< p0->numContacts<< endl;
        contactOrder.push_back(*p0);
        if (!(*p0 == pf)){
            contacted->push_back(*p0);
            turnList.push_back(turn);
            for (int i = 0;i<p0->numContacts;i++){
                //dont go to a place that we've already been to
                cout<<turn<<"->>"<< p0->contacts[i]->firstName<<endl;
                if (!in(p0->contacts[i],contacted,turn+1,turnList)){
                    list <Person> *temp = contactPath(p0->contacts[i],pf, contacted, contactOrder,turnList,turn);
                    if (temp != NULL)
                        return temp;  
                }
                cout<<"out"<<endl;
            }
        }else{
            //convert contactOrder into a pointer
            list <Person> *order = new list <Person>();
            for (int i =0;i<order->size();i++)
                order->push_back(order->at(i)); 
            return order;
        }
        return nullptr;
    }
    
public:
    list <Person> *people;
    Network(){
        people = new list <Person>();
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
                people->erase(i);
        }
    }
    void addRelationship(Person *p1,Person *p2){
        p1->addContact(p2);
        p2->addContact(p1);
    }
    
    void contactPath(const Person *p0,const Person *pf){
        //vector <Person> contacted;
        list <Person> *contacted = new list <Person>();
        //vector <Person> contactOrder;
        list <Person> contactOrder;
        list <int> turnList;
        int turn = 0;

        list <Person> *path = contactPath(p0,pf, contacted, contactOrder, turnList, turn);
        for (int i =0;i<path->size();i++){
            cout << path->at(i).firstName << " " << path->at(i).surname << endl;
        }

    }
    bool in(const Person *val, const list <Person> *personList,const int turn, const list <int> turnList){
        //dont look at the last one
        for (int i = 0 ; i < personList->size()-1;i++){
            if(personList->at(i) == val && turn > turnList.at(i))
                return true;
        }
        return false;
    }
    Person* getPerson(string firstName,string surname){
        for (int i =0 ;i<people->size();i++){
            if (people->at(i).firstName == firstName && people->at(i).surname == surname)
                return &people->at(i);
        }
    }
};
int main(){
    Network *net = new Network();

    net->addPerson(new Person {"Mike", "Ze", 0,180});
    net->addPerson(new Person {"Joe", "Ze",1,170,0});
    net->addPerson(new Person {"Larry", "S'ux",2,150});
    net->addPerson(new Person {"Bo", "Izeer2",3,150});
    net->addPerson(new Person {"Bo", "Izeer3",4,150});

    Person *Mike = net->getPerson("Mike","Ze");
    Person *Joe = net->getPerson("Joe","Ze");
    Person *Larry = net->getPerson("Larry","S'ux");
    Person *Bo = net->getPerson("Bo","Izeer2");
    Person *Bo3 = net->getPerson("Bo","Izeer3");

    net->addRelationship(Mike,Joe);
    net->addRelationship(Larry,Joe);
    net->addRelationship(Bo,Joe);
    net->addRelationship(Bo,Bo3);

    net->contactPath(Mike,Bo3);
    delete net;  
}
