#include "arr_expend.h"

typedef unsigned int v4ui __attribute__ ((vector_size (16)));

inline bool XOR(bool a, bool b){
    return a ? !b : b;
}

class ibi{
    public:
    bool isPositive = true;
    vecarr<unsigned int> integer_data;

    ibi() : isPositive(true)
    {
        integer_data.NULLState();
    }

    ibi(ibi& ref){
        isPositive = ref.isPositive;
        size_t ref_size = ref.integer_data.size();
        if(ref_size > integer_data.size())
            integer_data.Init(ref_size, integer_data.islocal);
        else
            integer_data.up = ref_size;
        for(int i=0;i<ref_size;++i)
            integer_data[i] = ref.integer_data[i];
    }

    ~ibi(){
    }

    void Init(){
        integer_data.Init(2, false);
    }

    void Release(){
        integer_data.release();
    }

    ibi& operator=(ibi& ref){
        isPositive = ref.isPositive;
        size_t ref_size = ref.integer_data.size();
        if(ref_size > integer_data.size())
            integer_data.Init(ref_size, integer_data.islocal);
        else
            integer_data.up = ref_size;
        for(int i=0;i<ref_size;++i)
            integer_data[i] = ref.integer_data[i];
    }

    inline bool cmp(ibi& A, bool left_big, bool include_same){
        if(isPositive && !A.isPositive) return left_big;
        if(isPositive == A.isPositive){
            if(integer_data.up > A.integer_data.up) return XOR(isPositive, left_big);
            else if(integer_data.up < A.integer_data.up) return XOR(!isPositive, left_big);
            else{
                for(int i=integer_data.up-1;i>=0;--i){
                    if(integer_data[i] > A.integer_data[i]) return XOR(isPositive, left_big);
                    else if(integer_data[i] < A.integer_data[i]) return XOR(!isPositive, left_big);
                }
                return include_same;
            }
        }
        else return left_big;
    }

    bool operator>(ibi& A){
        return cmp(A, true, false);
    }

    bool operator>=(ibi& A){
        return cmp(A, true, true);
    }

    bool operator<(ibi& A){
        return cmp(A, false, false);
    }

    bool operator<=(ibi& A){
        return cmp(A, false, true);
    }

    bool operator==(ibi& A){
        if(isPositive != A.isPositive) return false;
        else{
            if(integer_data.up != A.integer_data.up) return false;
            for(int i=integer_data.up-1;i>=0;--i){
                if(integer_data[i] != A.integer_data[i]) return false;
            }
            return true;
        }
    }

    bool operator!=(ibi& A){
        if(isPositive != A.isPositive) return true;
        else{
            if(integer_data.up != A.integer_data.up) return true;
            for(int i=integer_data.up-1;i>=0;--i){
                if(integer_data[i] != A.integer_data[i]) return true;
            }
            return false;
        }
    }

    void carry(ibi* num, int carryloc){
        if(num->integer_data.size() <= carryloc){
            num->integer_data.push_back(1);
        }
        else{
            if(num->integer_data[carryloc] == (unsigned int)-1){
                //carry
                carryloc = carryloc;
                carry(num, carryloc+1);
            }
            num->integer_data[carryloc] += 1;
        }
    }

    ibi operator+(ibi& A){
        ibi r = *this;
        if(r.isPositive == A.isPositive){
            int maxsiz = (A.integer_data.size() > r.integer_data.size()) ? A.integer_data.size() : r.integer_data.size();
            int i;
            for(i=0;i<maxsiz;++i){
                unsigned int Ax = A.integer_data[i];
                unsigned int Tx = r.integer_data[i];
                unsigned int max = (Ax>Tx)?Ax:Tx;
                Tx += Ax;
                if(Tx < max){
                    carry(&r, i+1);
                }
                r.integer_data[i] = Tx;
            }
        }
        else{

        }
        return r;
    }
};