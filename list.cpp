#include "element.cpp"
#include <string>
using namespace std;
class list{
private:
	template <class T>
	void addItem(T x){
		if (*first == NULL){
			element<T> newElement = new element<T>(x);
			*first = &newElement;
		}else if (*last == NULL){
			element<T> newElement = new element<T>(x);
			*last = &newElement;
			first->pointer = &last;
		}else{
			element<T> newElement = new element<T>(x);
			(*last)->pointer = &newElement;
			*last = &newElement;
		}
	}
public:
	element *first;
	element *last;
	list();
	void addString(string str){
		addItem<string>(str);
	}
	void addDouble(double num){
		addItem<double>(num);
	}
	void addInt(int num){
		addItem<int>(num);
	}
};
