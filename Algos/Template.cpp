#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ord_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define int long long


const int MOD=163577857;
int powerModulo(int a, int b) {
	int res=1;
	while(b) {
		if(b&1)
			res=(res*a)%MOD;
		a=(a*a)%MOD;
		b>>=1;
	}
	return res;
}

int fact[100005],inversefact[100005];
void pre() {
	fact[0]=1;
	fr(i,1,100000) {
		fact[i]=(fact[i-1]*i)%MOD;
	}
	ifact[100000]=powerModulo(fact[100000],MOD-2);
	for(int i=99999; i>=0; i--)
		inversefact[i]=(inversefact[i+1]*(i+1))%MOD;
}
inline int ncr(int n, int r) {
	return (((fact[n]*inversefact[r])%MOD)*inversefact[n-r])%MOD;
}

int main(){
    
   return 0;
}
