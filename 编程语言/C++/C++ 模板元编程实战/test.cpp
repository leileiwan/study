#include "iostream"
using namespace std;

struct A;
struct B;

template<typename T>
constexpr size_t Fun=0;

 //parse error in template argument list constexpr size_t Fun<A>=1;
 //template<>
 //constexpr size_t Fun<A>=1;


template<>
constexpr size_t Fun<A> = 1;

template<>
constexpr size_t Fun<B> = 2;

size_t h=Fun<B>;


int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

