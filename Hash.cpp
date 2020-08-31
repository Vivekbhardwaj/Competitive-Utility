class Hash{
    private :
    string s;
    int sz;
    int numberOfHashes;
    vector<vector<int>> v;
    vector<vector<int>> reverse_v;
    vector<int> MOD;
    vector<int> BASE;
    const int MAXN = 5e6;
    vector<vector<int>> powers;
    vector<vector<int>> inversePowers;

    int powerModulo(int base,int power,int mod){
        int res=1;
        while(power){
            if(power&1) res=(res*base)%mod;
            base=(base*base)%mod;
            power>>=1;
        }

        return res;
    }

    void compute(){
        for(int i=0;i<numberOfHashes;i++) powers[i][0] =1;
        for(int i=0;i<numberOfHashes;i++) for(int j=1;j<MAXN;j++) powers[i][j] = (powers[i][j-1]*BASE[i])%MOD[i];
        for(int i=0;i<numberOfHashes;i++) for(int j=1;j<MAXN;j++) inversePowers[i][j] = powerModulo(powers[i][j],MOD[i]-2,MOD[i]);
    }

    void createPrefixHash(){
        for(int i=0;i<numberOfHashes;i++){
            for(int j=0;j<sz;j++){
                v[i][j] = ((j>0?v[i][j-1] : 0) + (s[j]-'a'+1) * powers[i][j])%MOD[i];
            }
        }
    }

    public : 
    Hash(vector<int> b,vector<int> m){
        assert(b.size()==m.size());
        this->numberOfHashes = b.size();
        this->BASE = b;
        this->MOD = m;
        powers.resize(numberOfHashes,vector<int>(MAXN));
        inversePowers.resize(numberOfHashes,vector<int>(MAXN));
        compute();
    }


    Hash(string s,vector<int> b,vector<int> m){
        assert(b.size()==m.size());
        this->s = s;
        this->sz = s.size();
        this->numberOfHashes = b.size();
        this->BASE = b;
        this->MOD = m;
        v.resize(numberOfHashes,vector<int>(sz));
        powers.resize(numberOfHashes,vector<int>(MAXN));
        inversePowers.resize(numberOfHashes,vector<int>(MAXN));
        compute();
        createPrefixHash();
    }


    void createSuffixHash(){
        reverse_v.resize(numberOfHashes,vector<int>(sz));
        for(int i=0;i<numberOfHashes;i++){
            for(int j=sz-1;j>=0;j--){
                reverse_v[i][j] = ((j<sz-1?reverse_v[i][j+1] : 0) + (s[j]-'a'+1) * powers[i][sz-1-j])%MOD[i];
            }
        }
    }


    vector<int> get_hash(int l,int r){
        vector<int> ans;
        if(l==0){
            for(int i=0;i<numberOfHashes;i++) ans.push_back(v[i][r]);
        }
        else{
            for(int i=0;i<numberOfHashes;i++) ans.push_back(((v[i][r]-v[i][l-1] + MOD[i])*inversePowers[i][l])%MOD[i]);
        }
        return ans;
    }

    vector<int> get_reverse_hash(int l,int r){
        vector<int> ans;
        if(r==sz-1){
            for(int i=0;i<numberOfHashes;i++) ans.push_back(reverse_v[i][l]);
        }
        else{
            for(int i=0;i<numberOfHashes;i++) ans.push_back(((reverse_v[i][l]-reverse_v[i][r+1] + MOD[i])*inversePowers[i][sz-1-r])%MOD[i]);
        }
        return ans;
    }

    vector<int> hash_Of(string &s){
        vector<int> ans;
        for(int i=0;i<numberOfHashes;i++){
            int curr = 0;
            for(int j=0;j<sz;j++){
                curr = (curr + (s[j]-'a'+1) * powers[i][j])%MOD[i];
            }
            ans.push_back(curr);
        }
        return ans;
    }
};
