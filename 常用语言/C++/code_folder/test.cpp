#include "iostream"
using namespace std;

template <typename T>

T const& t_max(T const& a,T const& b){
    return a>b?a:b;
}

int main(){
    char a='0';
    char b='1';
    cout << int(t_max(a,b))<<"\n";
    return 0;
}