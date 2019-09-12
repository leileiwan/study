#include "iostream"
using namespace std;







// template <bool AddorRemove> struct Fun_;

// template <>
// struct Fun_<true>{
//     template<typename T>
//     using type=std::add_lvalue_reference<T>;
// };

// template <>
// struct Fun_<false>{
//     template<typename T>
//     using type=std::remove_reference<T>;
// };

// template <typename T>
//     template <bool AddorRemove>
//     using Fun= typename Fun_<AddorRemove>::template type<T>;

// template <typename T>
// using Res_=Fun<false>;

// Res_<int&>::type h=3;



int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

