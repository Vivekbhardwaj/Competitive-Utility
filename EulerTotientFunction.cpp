#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e7+5;
vector<int> primes;
int smallest_prime_div[MAXN];
int phi[MAXN];

void sieve(){
    for(int i=0;i<MAXN;i++){
        phi[i]=smallest_prime_div[i]=i;
    }

    for(int i=2;i*i<MAXN;i++){
        if(smallest_prime_div[i]==i){
            phi[i]=i-1;
            for(int j=i+i;j<MAXN;j+=i){
                phi[j]=(phi[j]/i)*(i-1);
                if(smallest_prime_div[j]==j) smallest_prime_div[j]=i;
            }
        }
    }

    for(int i=2;i<MAXN;i++){
        if(smallest_prime_div[i]==i) primes.push_back(i);
    }
}

int main(){
    sieve();
    for(int i=2;i<100;i++) cout<<"Smallest prime divisor of "<< i <<" is "<<smallest_prime_div[i]<<"\n";cout<<"\n";
    for(int i=2;i<100;i++) cout<<"Number of integers coprie to " << i <<" are "<<phi[i]<<"\n";cout<<"\n";
    for(int i=0;i<100;i++) cout<<primes[i]<<" ";cout<<"\n";

    return 0;
}

/*
Few Properties
- if gcd(a,b)==1 =====> phi(a*b)=phi(a)*phi(b)
- phi(p^k) = p^k-p^(k-1)  , where p is prime
- Sum of values of totient functions of all divisors of n is equal to n.
- a^phi(n)%n = 1 ====> which boils down to Fermats Little Theorm [a^(p-1)]%p = 1
*/
