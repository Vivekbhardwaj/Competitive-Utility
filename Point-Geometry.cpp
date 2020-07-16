#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define FAST ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

struct point { 
    int x, y; 
}; 
  
const int RIGHT = 1, LEFT = -1, ZERO = 0; 
  
int directionOfPoint(point A, point B, point P) 
{ 
    //The directions of vector is A->B
    //So we convert points A and B to vector AB , AB = OB + (-OA) , where OB is the position vector of B and OA is position vector of A
    //Similarly we find vector AP
    B.x -= A.x; 
    B.y -= A.y; 
    P.x -= A.x; 
    P.y -= A.y; 
  
    //Now we take cross product AB x AP
    int cross_product = B.x * P.y - B.y * P.x; 
  
    if (cross_product > 0) 
        return RIGHT; 
  
    if (cross_product < 0) 
        return LEFT; 
  
    return ZERO;  
} 

//Check if the point c lies between a and b if all three are collinear
bool check(point a,point b,point c){
    
    int dotproduct = (c.x - a.x) * (b.x - a.x) + (c.y - a.y)*(b.y - a.y);
    if(dotproduct < 0)
        return false;

    int squaredlengthba = (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
    if(dotproduct > squaredlengthba)
        return false;

    return true;
}

