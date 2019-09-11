#include "iostream"
using namespace std;
template <typename T>
struct Fun_
{
    using type=T;
};

//这里可以定义所有的类型
template<typename T>
using Fun=typename Fun_<T>::type;

Fun<int> h=3;

int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

