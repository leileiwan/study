#include "iostream"
using namespace std;

template <bool B,typename T,typename F>
class conditional_test
{   public:
        using type=T;
};

template<typename T,typename F>
struct conditional_test<false,T,F>
{   public:
        using type=F;
};

template<bool B,typename T,typename F>
using conditional_test_t=typename conditional_test<B,T,F>::type;

conditional_test_t<true,int,float> h=4;



int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

