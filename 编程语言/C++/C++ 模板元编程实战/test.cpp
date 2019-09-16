#include "iostream"
using namespace std;

template <bool IsFeedBackOut,typename T,std::enable_if_t<IsFeedBackOut>* =nullptr>
auto FeedBackOut_(IsFeedBackOut,T){
    return 1;
}

template<bool IsFeedBackOut,typename T,std::enable_if_t<!IsFeedBackOut>* =nullptr>
auto FeedBackOut_(IsFeedBackOut,T){
    return 2;
}

auto h=FeedBackOut_(true,int);


int main(){
    cout<<"hello"<<endl;
    cout<<h<<endl;
    return 0;
}

