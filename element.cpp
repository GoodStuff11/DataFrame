template <class T>
class element{
public:
	T val;
	element *pointer;
	element(T val){
		this->val = val;
	}
	element(T val, element *pointer){
		this->val = val;
		this->pointer = &pointer;
	}
};
