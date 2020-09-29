//set a range to certain value and then query sum over a range
class Seg{

    private :
    
    struct Node{
        int lazy,val;
        Node(){
            this->lazy = 0;
        }
        Node(int v){
            this->lazy = 0;
            this->val = v;
        }
    };

    int n;
    vector<Node> seg;

    public :

    Seg(){

    }

    Seg(int n){
        this->n = n;
        seg.resize(4*n,Node(0));
    }

    void resize_seg(int n){
        this->n = n;
        seg.resize(4*n,Node(0));
    }

    void propogate(int curr,int l,int r){
        if(l==r){
            seg[curr].val = seg[curr].lazy;
            seg[curr].lazy = 0;
            return;
        }
        seg[curr].val = seg[curr].lazy*(r-l+1);
        seg[2*curr].lazy = seg[2*curr+1].lazy = seg[curr].lazy;
        seg[curr].lazy = 0;

    }

    void set(int ul,int ur,int val,int l,int r,int curr = 1){
        if(l > r)   return ;
        
        if(seg[curr].lazy)  propogate(curr,l,r);

        if(l > ur || r < ul) return;

        if(l>=ul && r<=ur){
            if(l == r){
                seg[curr].val = val;
                return;
            }
            seg[curr].lazy = val;
            propogate(curr,l,r);
            return;
        }

        int mid = (l+r)/2;

        set(ul,ur,val,l,mid,2*curr);
        set(ul,ur,val,mid+1,r,2*curr+1);

        seg[curr].val = seg[2*curr].val + seg[2*curr+1].val;
        return;

    }

    int query(int ql,int qr,int l,int r,int curr=1){
        
        if(l > r) return 0;

        if(seg[curr].lazy)  propogate(curr,l,r);

        if(l > qr || r < ql) return 0;

        if(l>=ql && r<=qr)  return seg[curr].val;
        
        int mid = (l+r)/2;

        return 
        query(ql,qr,l,mid,2*curr) +
        query(ql,qr,mid+1,r,2*curr+1);

    }

};
