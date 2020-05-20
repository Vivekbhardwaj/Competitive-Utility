#include<bits/stdc++.h>
using namespace std;

const int MOD=3;

template<class T> struct modular {
    T val;
    explicit operator T() const { return val; }
    modular() { val = 0; }
    modular(const long long& v) {
    val = (-MOD <= v && v <= MOD) ? v : v % MOD;
    if (val < 0) val += MOD;
    }

    friend istream& operator>>(istream& in, modular& a){ return in >> a.val; }          //Better use read re;or simply create object using long long value
    friend ostream& operator<<(ostream& os, const modular& a){ return os << a.val; }    //After the input make sure you add 0 to it so that input is in MOD form
    // friend void pr(const modular& a) { pr(a.val); }
    friend void re(modular& a) { long long x; cin>>x; a = modular(x); }
    friend bool operator==(const modular& a, const modular& b) {  return a.val == b.val; }
    friend bool operator!=(const modular& a, const modular& b) {return !(a == b); }
    friend bool operator<(const modular& a, const modular& b)  { return a.val < b.val; }
    modular operator-() const { return modular(-val); }
    modular& operator+=(const modular& m) { if ((val += m.val) >= MOD) val -= MOD; return *this; }
    modular& operator-=(const modular& m) { if ((val -= m.val) <0) val += MOD; return *this; }
    modular& operator*=(const modular& m) { val = (long long)val*m.val%MOD; return *this; }
    friend modular pow(modular a, long long p) {modular ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *=a;return ans;}
    friend modular inv(const modular& a) { assert(a != 0); return pow(a,MOD-2); }
    modular& operator/=(const modular& m) { return (*this) *= inv(m); }
    friend modular operator+(modular a, const modular& b) {return a += b; }
    friend modular operator-(modular a, const modular& b) {return a -= b; }
    friend modular operator*(modular a, const modular& b) {return a *= b; }
    friend modular operator/(modular a, const modular& b) {return a /= b; }
};

int main(){
    modular<long long> a;re(a);
    a*=4;
    modular<long long>b;
    b=a;
    cout<<b<<"\n";
}