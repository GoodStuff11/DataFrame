#include <iostream>
using namespace std;

template <class t>
struct element{
    t val;
    element* ptr;
};

template <class t>
class list{
private:
    int length;
    element <t>*first;
    element <t>*last;
public:
    ~list(){
        //TODO: modify
    }
    int size(){
        return length;
    }
    void push_back(t val){
        //TODO: remove last or add functionality
        if (first == NULL){
            first = new element <t>{val};
        }else if(last == NULL){
            last = new element <t>{val};
            first->ptr = last;
        }else{
            element <t>*temp = last;
            last = new element <t>{val};
            temp->ptr = last;
        }
        length++;
    }
    t at(int index){
        element <t> *temp = first;
        for (int i=0;i<index;i++){
            temp = temp->ptr;
        }
        return temp->val;
    }
    void erase(int index){
        //TODO: make this work with first and last value
        element <t> *temp = first;
        for (int i=0;i<index-1;i++){
            temp = temp->ptr;
        }
        //connect the one before to the one after
        temp->ptr = temp->ptr->ptr->ptr;
        delete temp->ptr->ptr;
        length--;
    }
};
int main(){
    list <int> *L = new list<int>();
    for (int i=0;i<10;i++)
        L->push_back(i);
    L->erase(5);
    //TODO: make iterator
    for (int i=0;i<9;i++)
}
