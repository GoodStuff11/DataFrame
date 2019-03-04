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
        //modify
    }
    int size(){
        return length;
    }
    void push_back(t val){
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
        return temp->val; //wont work
    }
};
