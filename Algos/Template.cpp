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

int fact[1000005],inverseFactorials[1000005];
void pre() {
	fact[0]=1;
	for(int i=1;i<1000005;i++) {
		fact[i]=(fact[i-1]*i)%MOD;
	}
    for(int i=0;i<1000005;i++){
        inverseFactorials[i]=powerMODulo(fact[i],MOD-2);
    }
}


inline int nCr(int n,int r){
    if(n<r) return 0;
    return (((fact[n]*inverseFactorials[r])%MOD)*inverseFactorials[n-r])%MOD;
}

int main(){
    
   return 0;
}
