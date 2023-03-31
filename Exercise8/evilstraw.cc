#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
int sn(string s){
    int sw=0;
    map<char,int>cA;
    for (auto c:s)
        cA[c]++;
    int odd=0;
    for (auto i:cA) 
        if (i.second%2) 
            ++odd;
    if(odd>1)
        return-1;
    int l2=0,r2=s.size()-1;
    while(l2<r2){
        int l=l2,r=r2;
        while(s[l]!=s[r])
            --r;
        if(l2 == r){
            swap(s[r],s[r+1]);
            ++sw;
        }else{
            while(r<r2){
                swap(s[r], s[r+1]);
                ++sw;
                ++r;
            }
            ++l2,--r2;
        }
    }
    return sw;
}
int main(){
    int n;
    cin>>n;
    string s;
    for(int i=0;i<n;++i){
        cin>>s;
        int ns=sn(s);
        if (ns<0) {
            cout<<"Impossible\n";
        } else {
            cout<<ns<<"\n";
        }
    }
    return 0;
}