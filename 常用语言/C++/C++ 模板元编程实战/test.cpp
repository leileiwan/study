#include "iostream"
using namespace std;


template <template <typename> typename T1,typename T2>
struct Fun_
{
    using type=typename T1<T2>::type;
    /* data */
};

template <template <typename> typename T1,typename T2>
using Fun=typename Fun_<T1,T2>::type;

Fun<std::remove_reference,int&> h=3;


int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

