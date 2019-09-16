#include "iostream"
using namespace std;

template <size_t ID,typename TDummy=void>
struct imp{
    constexpr static size_t value = ID + imp<ID-1>::value;
};

template<typename TDummy>
struct imp<0,TDummy>{
    constexpr static size_t value=0;
};

template <size_t A>
struct Wrap_{
    template <size_t ID>
    constexpr static size_t value=imp<A+ID>::value;
};

size_t h=Wrap_<3>::value<2>;
size_t h1=Wrap_<10>::value<2>;


int main(){

    cout<<"hello"<<endl;
    cout<<h<<endl;
    cout<<h1<<endl;
    return 0;
}

