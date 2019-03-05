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
        //go from one pointer to the next deleting each one
        element <t>*toDelete = first;
        for (int i=0;i<this->size();i++){
            element <t>*temp = toDelete->ptr;
            delete toDelete;
            toDelete = temp;
        }
        delete toDelete;
        delete length;
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
        return temp->val;
    }
    void erase(int index){
        //TODO: make this work with first and last value
        element <t> *temp = first;
        for (int i=0;i<index-1;i++)
            temp = temp->ptr;
        
        if (index == 0){
            first = temp->ptr;
            delete temp;
        }else if (index == this->size() - 1){
            delete &temp->ptr;
            temp->ptr = NULL;
            last = temp;
        }else{
            //connect the one before to the one after
            temp->ptr = temp->ptr->ptr;
            delete &temp->ptr->ptr;
        }
        length--;
    }
    
};
int main(){
    list <int> *L = new list<int>();
    for (int i=0;i<10;i++)
        L->push_back(i);
    delete L;

}
