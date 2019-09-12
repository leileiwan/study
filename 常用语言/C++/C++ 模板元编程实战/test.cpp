#include "iostream"
using namespace std;

template <typename TW>
struct Wrapper{
    template <typename T,typename TD>
    struct Fun_{
        constexpr static size_t value=0;
    };

    template<typename TD> 
    struct Fun_<int,TD>{
        constexpr static size_t value=1;
    };
    
};

template<typename T,typename TD>
using Fun=typename Wrapper<int>::Fun_<T,TD>;

size_t h=Fun<int,int>::value;



int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

