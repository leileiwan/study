#include "iostream"
using namespace std;

template <size_t... inputs>
constexpr size_t SumArray = 0;

template<size_t curr,size_t... inputs>
constexpr size_t SumArray<curr,inputs...> = curr + SumArray<inputs...>;

constexpr size_t  h = SumArray<1,2,3,4>;


int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

