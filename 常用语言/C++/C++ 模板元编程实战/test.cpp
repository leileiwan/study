#include "iostream"
using namespace std;

template <typename T>
struct RemoveReferenceConst_
{
    private:
        using inter_type=typename std::remove_reference<T>::type;
    public:
        using type=typename std::remove_const<inter_type>::type;
};

template<typename T>
using RemoveReferenceConst=typename RemoveReferenceConst_<T>::type;

RemoveReferenceConst<const int&> h=3;


int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

