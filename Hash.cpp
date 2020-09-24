long long powerModulo(long long base,long long power,long long mod){
    long long ans = 1;
    while(power){

        if(power&1) {
            ans = (ans*base)%mod;
        }

        base = (base*base) %mod;
        power>>=1;

    }

    return ans;
}

class Hash {

    //seed = {31,101} and mod = {1e9+7,1e9+7} 
    array<long long,2> seed = {31,101};
    array<long long,2> MOD = {(long long)1e9+7,(long long)1e9+7};
    vector<vector<long long>> powerMod , inversePowerMod;

    public:

    Hash(long long n){
         
        powerMod.resize(n,vector<long long>(2));  inversePowerMod.resize(n,vector<long long>(2));

        array<long long,2> aInvMod;

        for(long long j=0;j<2;j++)
            aInvMod[j] = powerModulo(seed[j],MOD[j]-2,MOD[j]);
        
        for(long long j=0;j<2;j++) 
            powerMod[0][j] = inversePowerMod[0][j] = 1;

        for(long long i=1;i<n;i++){

            for(long long j=0;j<2;j++){

                powerMod[i][j] = (powerMod[i-1][j]*seed[j])%MOD[j];
                inversePowerMod[i][j] = (inversePowerMod[i-1][j]*aInvMod[j])%MOD[j];

            }

        }

    }

    vector<int> hashof(string &s){
        long long n;
        n = s.size();

        vector<int> pref(2);

        pref[0] = pref[1] = s[0] - 'a' + 1;

        for(long long i=1 ; i<n ; i++){
            for(long long j=0;j<2;j++){
                pref[j] = (pref[j] + (s[i] - 'a' + 1)*powerMod[i][j])%MOD[j];
            }
        }

        return pref;
    }

    vector<vector<long long>> prefixHash(string &s){
        long long n;
        n = s.size();

        vector<vector<long long>> pref(n,vector<long long>(2));

        pref[0][0] = pref[0][1] = s[0] - 'a' + 1;

        for(long long i=1 ; i<n ; i++){
            for(long long j=0;j<2;j++){
                pref[i][j] = (pref[i-1][j] + (s[i] - 'a' + 1)*powerMod[i][j])%MOD[j];
            }
        }

        return pref;
    }


    inline vector<long long> getHash(long long l,long long r,vector<vector<long long>> &prefix){
        if(l == 0) return prefix[r];
        else {
            vector<long long> h(2);
            for(long long j=0;j<2;j++){
                h[j] = (((prefix[r][j] - prefix[l-1][j])%MOD[j] + MOD[j])*inversePowerMod[l][j])%MOD[j];
            }

            return h;
        }
    }

};
