#include<bits/stdc++.h>
using namespace std;

void kmparray(string s){
    int n = s.size();
    vector<int> border(n);

    for(int i=1;i<n;i++){
        border[i] = border[i-1];
        while(border[i] > 0 && s[border[i]] != s[i]){
            border[i] = border[border[i]-1];        //remember border[i] = border[border[i]] won't work because there might be two consecutive same no. and it'd be stuck in an infinite loop
        }
        border[i]+=(s[i] == s[border[i]]);
    }


    for(auto i : border) cout<<i<<" ";cout<<"\n";
}

int main(){
    kmparray("xyzyxabba#abbaxyzyx");
    return 0;
}
