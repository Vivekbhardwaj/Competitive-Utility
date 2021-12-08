 /**
  * @brief : Given an array A of length N. Count all possible pairs (i,j) such that:
            (Ai | Aj) <=max (Ai,Aj)
            Constraints: 1<=N<=10^6, 1<=Ai<=10^6
  * @author : Vivek Bhardwaj
  * @date  : 8 Dec 2021
  */
 

#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
using namespace std;

int solve(vector<int> &v){

    /*  
        IMP : OR of two elements can never be less than the max element 
        so effectively we needed to find the pair of elements whose OR is equal to max of the two elements
    */


    int N = *max_element(v.begin(),v.end());
    unordered_map<int,int> freq;
    for(int i : v) freq[i]++;

    /*
    Consider two numbers A and B and consider j as the index of j-th bit from L.S.B
    Now A[0...j] refers to all the bits from 0 till jth bit in A
    For example : 
        A = 35 
                        543210
    => (A) in Base 2 =  110011      (from L.S.B to M.S.B)
    => now A[0...j] for j = 2 is = 110

    Let me define subset for this kind of condition
    A[0...j] is a subset of B[0...j] iff 
    (i) all the bits that are 0(unset) in B[0..j] are also 0 in A[0...j] 
    (ii) all the bits that are 1(set) in  B[0..j] can either be set or unset in A[0..j]

    give 10101   
    subset -> 10001
    not subset -> 10011

    */


    //dp[i][j] <- defines number of elements that are a subset of i[0..j] and have exactly same i[j+1...20] in their binary representation
    vector< vector<long long> > dp(N+1,vector<long long>(21,0));

    //writing the base case => j = 0
    for(int i=0;i<=N;i++){ 
        dp[i][0] = freq[i];

        if(i&(1<<0)){
            dp[i][0] += dp[i^(1<<0)][0];
        }
    }


    for(int j=1;j<=20;j++){

        for(int i=0;i<=N;i++){

            if(i&(1<<j)){   //j-th bit is set
                //j-th index can be 0 (unset) or 1 (set) in the numbers we are interested in
                dp[i][j] = dp[i][j-1];  //j-th bit is set
                dp[i][j] += dp[i^(1<<j)][j-1]; //j-th bit is unset
            }
            else{   //j-th bit is not set
                //since j-th bit is not set its value is deffered from (j-1)th value since we need to put 0 
                //in this case at j-th position in numbers we are interested in
                dp[i][j] = dp[i][j-1];
            }

        }

    }


    for(int i=0;i<=N;i++){
        cout<<i<<" -> ";
        for(int j=0;j<=5;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    


    //now dp[i][20] stores all the frequency of all the subsets of i (it'll include i as well) 
    long long ans = 0;
    for(int i=0;i<=N;i++){
        if(freq[i] != 0){
            
            long long equal_to_i = freq[i];
            long long other = dp[i][20] - equal_to_i;

            cout<<i<<" ";
            cout<<equal_to_i<<" "<<other<<endl;

            ans += equal_to_i *  other;
            ans += equal_to_i * (equal_to_i-1) / 2;       //nC2 for choosing two of equal elements

        }
    }

    return ans;
   
}


int main(){

    vector<int> v = {1,2,2,4,8,8,10,9,11,11};

    cout<<solve(v)<<endl;

    return 0;
}


    /*

    i = 101010101 1
    j = 0

    101010101 1
    101010100 0

    dp[i][j] = 2

    */

   /*

    i = 10101010 11
    j = 1

    10101010 11
    10101010 01
    10101010 00
    10101010 10

    dp[i][j] = 4

    */

   /*
   i = 1010101 011
   j = 2

   1010101 011
   1010101 001
   1010101 000
   1010101 010

   dp[i][j] = 4
   */
