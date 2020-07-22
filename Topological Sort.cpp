vector<int> topological_sort(vector<set<int>> &g){
    int n=g.size();
    vector<int> in(26,0);
    for(int i=0;i<n;i++){
        for(const int &j : g[i]) in[j]++;
    }

    queue<int> q;
    vector<int> topologically_sorted;
    for(int i=0;i<n;i++){
        if(in[i]==0) {q.push(i);topologically_sorted.push_back(i);}
    }

    while(!q.empty()){
        int curr=q.front();
        q.pop();
        for(const int i: g[curr]){
            in[i]--;
            if(in[i]==0) {q.push(i);topologically_sorted.push_back(i);}
        }
    }

    return topologically_sorted;
}
