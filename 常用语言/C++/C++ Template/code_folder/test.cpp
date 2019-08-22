#include "vector"
#include "stdexcept"
#include "iostream"
using namespace std;

template <typename T>
class Stack{
    private: vector<T> elems;

    public:
        void push(T e){
            elems.push_back(e);
        }
        void pop(){
            elems.pop_back();
        }
        T top() const{
            return elems.back();
        }
        bool empty(){
            return elems.empty();
        }
};

int main(){
    Stack<int> int_stack;
    int_stack.push(1);
    cout<<int_stack.top()<<endl;
    int_stack.push(2);
    cout<<int_stack.top()<<endl;
    return 0;
}
