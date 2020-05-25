//The concept of suffix array is based on sorting cyclic shifts

//Suffix array is the data structure which stores suffixes in sorted order
#include<bits/stdc++.h>
using namespace std;


vector<int> createSuffixArray(const string &s){
    int n=s.size();
    map<char,int> mp;
    for(auto i : s)mp[i]++;

    int counter=0;
    for(auto &i : mp){
        i.second=counter++;
    }

    //at every instant it keeps the ordering of the suffixes of starting at index i
    //we do the ordering in multiples of 2 first we find what will be the position if we compare first characters,then we compare first two characters,then first four and so on
    //fortunately we can compare first 2^k characters fo two suffixes if we know comparasion 2^k-1 by the method below of making tuples of current order of sum=ffix and order the 2^(k-1) th next suffix
    //and we give them new ordering accordingly 
    vector<int> suffixArray(n);
    for(int i=0;i<n;i++) suffixArray[i]=mp[s[i]];       //giving order to suffix starting at i-th index based on its first character suffixes having same first character are given same value

    // for(auto i : suffixArray) cerr<<i<<" ";cerr<<"\n";

    for(int i=2;i<=log2(n)+2;i++){
        vector<pair<int,int>> tuple_to_be_sorted(n);
        for(int j=0;j<n;j++){
            tuple_to_be_sorted[j].first=suffixArray[j];
            tuple_to_be_sorted[j].second=(j+i-1<n?suffixArray[j+i-1]:-1);
        }

        //map here is used to find the order of the pair
        map<pair<int,int>,int> m;
        for(auto i : tuple_to_be_sorted) m[i]++;
        counter=0;
        for(auto &i : m){
            i.second=counter++;
        }
         

        for(int j=0;j<n;j++){
            suffixArray[j]=m[tuple_to_be_sorted[j]];        //giving order to suffix starting at i-th index based on first 2^k characters suffixes having same first 2^k characters are given same value
        }

        // for(auto i : suffixArray) cerr<<i<<" ";cerr<<"\n";


    }
    
    //this is not the suffix array same as what the definition says though it is similar and we can get the suffix array of our definition by single pass
    //this suffix array gives the information that if we sort the suffixes what will be the index of suffix starting at i in our string
    // return suffixArray;


    vector<pair<int,int>> x(n);
    for(int i=0;i<n;i++){
        x[i].first=suffixArray[i];
        x[i].second=i;
    }
    sort(x.begin(),x.end());

    vector<int> sortedSuffixArray(n);
    for(int i=0;i<n;i++)sortedSuffixArray[i]=x[i].second;


    //suffix array which gives the index of starting of suffix in a sorted manner
    return sortedSuffixArray;


}

int main(){
    vector<int> x = createSuffixArray("aabbaabbaabb");
    for(auto i : x) cerr<<i<<" ";cerr<<"\n";

    return 0;
}