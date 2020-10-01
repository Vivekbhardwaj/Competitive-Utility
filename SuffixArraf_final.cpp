// Written By Dheeraj Maurya
// Btech Student IET LUCKNOW(2018 - 2022)
// Suffix array
// Applications : lcp of two substrings ,number of different substrings , finding a substring...

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct suf{
  ll id, rank[2];
};

bool comp(struct suf & a ,struct suf &b){
  if(a.rank[0]==b.rank[0]) return (a.rank[1] < b.rank[1]);
  return (a.rank[0] < b.rank[0]);
}

vector<ll> build(string s){
  ll n=s.size() ; ++n; struct suf arr[n]; ll id[n];

  for(ll i=0;i<n;i++){
     arr[i].id =i;
     arr[i].rank[0]=s[i]-'a';
     arr[i].rank[1]=( (i+1)<n )? (s[i+1]-'a'): -1; 
  }
   
  sort(arr ,arr+ n ,comp);  // first we sort all suffixes according to first two characters

  for(ll k=4;k<2*n;k*=2){
    // now we sort all suffiexes according to next k/2 characters
    ll prev_rank = arr[0].rank[0] ,rank=0;
    id[arr[0].id] = 0 ; 
    arr[0].rank[0] = 0;
    
    
    for(ll i=1;i<n;i++){
      if(arr[i].rank[0] == prev_rank && arr[i].rank[1] == arr[i-1].rank[1] ) arr[i].rank[0] = rank; 
      else  { prev_rank = arr[i].rank[0] ;  arr[i].rank[0] = ++rank; }
      id[arr[i].id] =i;
    }

    for(ll i=0;i<n;i++){
      ll next = arr[i].id + k/2;
      arr[i].rank[1] = ((next<n))? (arr[id[next]].rank[0]):-1;
    }
    sort(arr ,arr+n, comp); // sort suffixes according to first sorted k/2 characters and next k/2 characters 

  }
   vector<ll> v(n);
   for(ll i=0;i<n;i++)
    v[i] = arr[i].id;
   return v; 
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  
  string s= "aagsmrvafyqwxq"; 

  vector<ll> suffix_array = build(s); // calling build function for suffix array
  
  for(auto k:suffix_array)
    cout<<k<<" ";  
}
