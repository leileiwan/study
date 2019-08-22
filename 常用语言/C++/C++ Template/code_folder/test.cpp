#include "iostream"
using namespace std;

template <typename T>

T const& t_max(T const& a,T const& b){
    return a>b?a:b;
}

int main(){
    int a=0;
    float b=1.2;
    cout << t_max<float>(a,b)<<"\n";
    return 0;
}