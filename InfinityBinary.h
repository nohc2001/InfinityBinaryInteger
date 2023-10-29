#include "arr_expend.h"

typedef unsigned int v4ui __attribute__ ((vector_size (16)));

inline bool XOR(bool a, bool b){
    return a ? !b : b;
}

class ibi{
    public:
    bool isPositive = true;
    bool islocal = true;
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
        if(islocal) integer_data.release();
    }

    void Init(bool plocal){
        integer_data.Init(2, false);
        islocal = plocal;
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

    static void carry(ibi* num, int carryloc){
        if(num->integer_data.size() <= carryloc){
            num->integer_data.push_back(1);
        }
        else{
            if(num->integer_data[carryloc] == (unsigned int)-1){
                //carry
                carry(num, carryloc+1);
            }
            num->integer_data[carryloc] += 1;
        }
    }

    static void carry_under(ibi* num, int carryloc){
        if(carryloc >= num->integer_data.size()) return;
        if(num->integer_data[carryloc] == 0){
            //carry
            carry_under(num, carryloc+1);
        }
        num->integer_data[carryloc] -= 1;
    }

    static ibi add_absolute(ibi A, ibi B){
        ibi r;
        r.Init(false);
        r = B;
        int maxsiz = (A.integer_data.size() > B.integer_data.size()) ? A.integer_data.size() : B.integer_data.size();
        int i;
        for(i=0;i<maxsiz;++i){
            unsigned int Ax = (A.integer_data.up > i) ? A.integer_data[i] : 0;
            unsigned int Tx = (r.integer_data.up > i) / r.integer_data[i] : 0;
            unsigned int max = (Ax>Tx)?Ax:Tx;
            Tx += Ax;
            if(Tx < max){
                carry(&r, i+1);
            }
            r.integer_data[i] = Tx;
        }
        return r;
    }

    static ibi sub_absolute(ibi A, ibi B){
        bool pos[2] = {A.isPositive, B.isPositive};
        A.isPositive = true;
        B.isPositive = true;
        ibi r;
        r.Init(false);
        if(A > B){
            r = A;
            for(int i=0;i<A.integer_data.up;++i){
                unsigned int Ax = (r.integer_data.up > i) ? r.integer_data[i] : 0;
                unsigned int Bx = (B.integer_data.up > i) / B.integer_data[i] : 0;
                if(Ax < Bx){
                    carry_under(&r, i+1);
                }
                Ax -= Bx;
                r.integer_data[i] = Ax;
            }
            r.isPositive = pos[0];
        }
        else{
            r = B;
            for(int i=0;i<B.integer_data.up;++i){
                unsigned int Bx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
                unsigned int Ax = (A.integer_data.up > i) / A.integer_data[i] : 0;
                if(Bx < Ax){
                    carry_under(&r, i+1);
                }
                Bx -= Ax;
                r.integer_data[i] = Bx;
            }
            r.isPositive = pos[1];
        }
        return r;
    }

    ibi operator+(ibi& A){
        if(isPositive == A.isPositive){
            return ibi::add_absolute(*this, A);
        }
        else{
            return ibi::sub_absolute(*this, A);
        }
        return r;
    }

    ibi operator-(ibi& A){
        if(isPositive == A.isPositive){
            return ibi::sub_absolute(*this, A);
        }
        else{
            return ibi::add_absolute(*this, A);
        }
        return r;
    }

    ibi operator<<(int n){
        ibi r;
        r.Init(false);
        r = *this;
        for(int i=0;i<n;++i){
            r.integer_data.insert(0, 0);
        }
        return r;
    }

    ibi operator>>(int n){
        ibi r;
        r.Init(false);
        r = *this;
        for(int i=0;i<n;++i){
            r.integer_data.erase(0);
        }
        return r;
    }

    ibi mul_32(unsigned int A, unsigned int B){
        unsigned short A1 = A >> 16;
        unsigned short A0 = (A << 16) >> 16;
        unsigned short B1 = B >> 16;
        unsigned short B0 = (B << 16) >> 16;

        unsigned int R0 = (unsigned int)A0 * (unsigned int)B0;
        unsigned int R1 = (unsigned int)A0 * (unsigned int)B1;
        unsigned int R11 = R1 >> 16;
        unsigned int R10 = R1 << 16;
        unsigned int R2 = (unsigned int)A1 * (unsigned int)B0;
        unsigned int R21 = R2 >> 16;
        unsigned int R20 = R2 << 16;
        unsigned int R3 = (unsigned int)A1 * (unsigned int)B1;

        ibi operand[3];
        operand[0].Init(true);
        operand[1].Init(true);
        operand[2].Init(true);
        operand[0].integer_data[0] = R0;
        operand[0].integer_data[1] = R3;
        operand[1].integer_data[0] = R10;
        operand[1].integer_data[1] = R11;
        operand[2].integer_data[0] = R12;
        operand[2].integer_data[1] = R12;

        ibi r;
        r.Init(false);
        r = operand[0] + operand[1];
        r = r + operand[2];
        return r;
    }

    ibi operator*(ibi& A){
        
    }
};