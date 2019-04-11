#include "network.h"

using namespace std;

int main(){

    Network *net = new Network();

    net->addPerson(Person("Mike", "Ze", 0,180));
    net->addPerson(Person("Joe", "Ze",1,170));
    net->addPerson(Person("Larry", "S'ux",2,150));
    net->addPerson(Person("Bo", "Izeer2",3,150));
    net->addPerson(Person("Bo", "Izeer3",4,150));

    Person *Mike = net->getPerson("Mike","Ze");
    Person *Joe = net->getPerson("Joe","Ze");
    Person *Larry = net->getPerson("Larry","S'ux");
    Person *Bo = net->getPerson("Bo","Izeer2");
    Person *Bo3 = net->getPerson("Bo","Izeer3");


    net->addRelationship(Mike,Joe);
    net->addRelationship(Larry,Joe);
    net->addRelationship(Bo,Joe);
    net->addRelationship(Bo,Bo3);

    net->printNetwork();
    net->write("s:/data/networkdata.bin");

    delete net;

    Network *NEWnet = new Network();
    NEWnet->read("s:/data/networkdata.bin");
    NEWnet->printNetwork();

    delete NEWnet;

}
