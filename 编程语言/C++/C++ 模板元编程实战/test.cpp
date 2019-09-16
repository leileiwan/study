#include "iostream"
using namespace std;

template <bool check>
auto fun(){
    if constexpr(check){
        return 1;
    }else{
        return 0;
    }
}

auto h=fun<false>();


int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

