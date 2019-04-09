#include "list.h"

template<class t>
list<t>::list() {
	length = 0;
	first = nullptr;
	last = nullptr;
	current = nullptr;
	cindex = 0;
}
template<class t>
list<t>::~list() {
	//go from one pointer to the next deleting each one
	element<t>*toDelete = first;
	for (int i = 0; i < this->size(); i++) {
		element<t>*temp = toDelete->next;
		delete toDelete;
		toDelete = temp;
	}
	delete toDelete;
	delete current;
}
template<class t>
int list<t>::size() {
	return length;
}
template<class t>
int list<t>::size() const {
	return length;
}
template<class t>
void list<t>::push_back(t val) {
	if (first == nullptr) {
		first = new element<t> { val };
		current = first;
	} else if (last == nullptr) {
		last = new element<t> { val };
		first->next = last;
	} else {
		element<t>*temp = last;
		last = new element<t> { val };
		temp->next = last;
	}
	length++;
}
template<class t>
void list<t>::swap(int i1, int i2) {
	if (i1 == i2)
		return;
	if (i2 < i1) {
		int i = i2;
		i2 = i1;
		i1 = i;
	}
	if (i1 == 0 && i2 != size() - 1) {
		go(0);
		element<t>*e1 = current;

		go(i2 - 1);
		element<t>*e2 = current;

		element<t>*temp = e1->next;
		e1->next = e2->next->next;
		e2->next->next = temp;

		first = e2->next;
		e2->next = e1;
	} else if (i2 == size() - 1 && i1 != 0) {
		go(i1 - 1);
		element<t>*e1 = current;

		go(i2 - 1);
		element<t>*e2 = current;

		last = e1->next;
		e2->next->next = e1->next->next;

		element<t>*temp = e1->next;
		e1->next = e2->next;
		e2->next = temp;


	} else if (i1 == 0) {
		element<t>*temp = first;
		first = last;
		last = temp;

		go(0);
		element<t>*e1 = current;

		go(i2 - 1);
		element<t>*e2 = current;

		e2->next->next = e1->next;
		e2->next = e1;
	} else {
		go(i1 - 1);
		element<t>*e1 = current;

		go(i2 - 1);
		element<t>*e2 = current;

		element<t>*temp = e1->next->next;
		e1->next->next = e2->next->next;
		e2->next->next = temp;

		element<t>*temp2 = e1->next;
		e1->next = e2->next;
		e2->next = temp2;
	}
}

template<class t>
t* list<t>::refAt(int index) {
	go(index);
	return &(current->val);
}

template<class t>
t list<t>::valAt(int index) {
	go(index);
	return current->val;
}
/*
template<class t>
t list<t>::valAt(int index) const {
	if (index < cindex) {
		current = first;
		cindex = 0;
	}
	for (int i = cindex; i < index; i++) {
		cindex = cindex + 1;
		current = current->next;
	}
	return current->val;
}
*/
//TODO: debug special cases
template<class t>
void list<t>::erase(int index) {
	element<t> *temp = first;
	for (int i = 0; i < index - 1; i++)
		temp = temp->next;

	if (index == 0) {
		first = temp->next;
		delete temp;
	} else if (index == this->size() - 1) {
		delete &temp->next;
		temp->next = NULL;
		last = temp;
	} else {
		//connect the one before to the one after
		temp->next = temp->next->next;
		delete &temp->next->next;
	}
	length--;
}
/*
 * Moves current to index i
 */
template<class t>
void list<t>::go(int i) {
	if (i < cindex) {
		current = first;
		cindex = 0;
	}
	for (; cindex < i; cindex++) {
		current = current->next;
	}
}
