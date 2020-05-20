#include<bits/stdc++.h>
using namespace std;

void kmparray(string s){
    vector<int> border((int)s.size());

    int curr_border=0;
    for(int i=1;i<(int)s.size();i++){
        if(s[i]==s[curr_border]){
            curr_border++;
            border[i]=curr_border;
        }
        else if(curr_border==0){
            border[i]=0;
        }
        else{
            i--;
            curr_border=s[curr_border-1];
        }
    }

    for(auto i : border) cout<<i<<" ";cout<<"\n";
}

int main(){
    kmparray("xyzyxabba#abbaxyzyx");
    return 0;
}