#include "arr_expend.h"
#include "Utill_FreeMemory.h"
using namespace freemem;

typedef unsigned int v4ui __attribute__ ((vector_size (16)));

inline bool XOR(bool a, bool b){
    return a ? !b : b;
}

class ibi{
    public:
    bool isPositive = true;
    bool islocal = true;
    fmvecarr<unsigned int> integer_data;

    static vecarr<ibi*> prime_numbers;

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

    void operator=(ibi& ref){
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

    static ibi add_absolute(ibi& A, ibi& B){
        ibi r;
        r.Init(false);
        fm->_tempPushLayer();
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
        fm->_tempPopLayer();
        return r;
    }

    static ibi sub_absolute(ibi& A, ibi& B){
        bool pos[2] = {A.isPositive, B.isPositive};
        A.isPositive = true;
        B.isPositive = true;
        ibi r;
        r.Init(false);
        fm->_tempPushLayer();
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
        fm->_tempPopLayer();
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
        fm->_tempPushLayer();
        r = *this;
        for(int i=0;i<n;++i){
            r.integer_data.insert(0, 0);
        }
        fm->_tempPopLayer();
        return r;
    }

    ibi operator>>(int n){
        ibi r;
        r.Init(false);
        fm->_tempPushLayer();
        r = *this;
        for(int i=0;i<n;++i){
            r.integer_data.erase(0);
        }
        fm->_tempPopLayer();
        return r;
    }

    ibi mul_32(unsigned int A, unsigned int B){
        ibi r;
        r.Init(false);
        fm->_tempPushLayer();

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

        r = operand[0] + operand[1];
        r = r + operand[2];

        fm->_tempPopLayer();
        return r;
    }

    ibi operator*(ibi& A){
        ibi r;
        r.Init(false);
        fm->_tempPushLayer();
        r.integer_data.push_back(0);
        ibi* thismulibi = new ibi[A.integer_data.up];
        for(int i=0;i<integer_data.up;++i){
            thismulibi[i].Init(true);
            thismulibi[i].integer_data.push_back(0);
            unsigned int uii = integer_data[i];
            ibi* mulibi = new ibi[A.integer_data.up];
            for(int k=0;k<A.integer_data.up;++k){
                ibi[k].Init(true);
                ibi[k] = mul_32(uii, A.integer_data[k]);
                thismulibi = thismulibi + ibi[k];
            }
            delete[] mulibi;
            r = r + thismulibi[i];
        }
        delete[] thismulibi;
        fm->_tempPopLayer();
        return r;
    }

    ibi div_32(ibi& A, unsigned int divn){
        ibi r;
        r.Init(false);
        r.integer_data.push_back(0);
        r.integer_data.Init(A.integer_data.up, false);
        for(int i=0;i<r.integer_data.up;++i){
            r.integer_data[i] = 0;
        }
        if(divn == 0){
            return r;
        }

        fm->_tempPushLayer();

        ibi tempA;
        tempA.Init(false)
        tempA = A;

        ibi tempDivn;
        tempDivn.Init(false)
        tempDivn = divn;

        constexpr double max = pow(2, 32);
        double dv = (double)divn;
        bool updatefirst = true;

        bool zero_stack = 0;
        for(int i=tempA.integer_data.up-1;i>=0;--i){
            if(zero_stack == false){
                unsigned int ad = tempA.integer_data[i] / divn;
                if(ad == 0){
                    zero_stack = true;
                }
                else{
                    r.integer_data[i] = ad;
                }
            }
            else{
                unsigned int seekstart = (unsigned int)((double)tempA.integer_data[i+1] * max / dv);
                bool saturate = false;
                unsigned int lastnum = seekstart;
                while(!saturate){
                    fm->_tempPushLayer();
                    ibi temp;
                    temp.Init(false);
                    temp.integer_data.push_back(A.integer_data[i]); temp.integer_data.push_back(tempA.integer_data[i+1])
                    ibi dv = mul_32(divn, seekstart);
                    if(dv > temp){
                        saturate = true;
                    }
                    else{
                        lastnum = seekstart;
                        ++seekstart;
                    }
                    fm->_tempPopLayer();
                }

                ibi tempB;
                tempB.Init(false);
                tempB.integer_data.Init(i, false);
                for(int k=0;k<i;++k){
                    tempB.integer_data[k] = 0;
                }
                tempB.integer_data[i] = lastnum;
                
                if(updatefirst) r.integer_data.up = i+1;
                r.integer_data[i] = lastnum;
                tempA = tempA - (tempB * tempDivn);
                zero_stack = false;
            }
        }

        fm->_tempPopLayer();
        return r;
    }

    ibi operator/(ibi& A){
        //this / a
        ibi r;
        r.Init(false);

        fm->_tempPushLayer();

        // tempV / A
        ibi tempV;
        tempV.Init(false);
        tempV = *this;

        ibi tempA;
        tempA.Init(false);
        tempA = A;

        int shift = tempA.integer_data.up - 1;
        int vpos = 1;
        while (vpos < 0)
        {
            fm->_tempPushLayer();
            vpos = tempV.integer_data.up - 1 - (shift + 1);
            ibi tV;
            tV.Init(false);
            tV = tempV >> shift;

            ibi tR;
            unsigned int tA = tempA.integer_data.last();
            bool saturate = true;
            while (saturate)
            {
                tR.Init(false);
                tR = div_32(tV, tA);
                tR = tR << vpos;

                if (tempV < (tempA * tR))
                {
                    saturate = true;
                    tA -= 1;
                }
                else{
                    saturate = false;
                }
            }

            tempV = tempV - (tempA * tR);
            for(int k=tempV.up-1;k>=0;--k){
                if(tempV[k] == 0) tempA.integer_data.up -= 1;
                else{
                    break;
                }
            }
            r = r + tR;

            fm->_tempPopLayer();
        }
        fm->_tempPopLayer();
        return r;
    }

    ibi operator%(ibi& A){
        ibi r;
        r.Init(false);
        r = *this - (*this / A) * A;
        return r;
    }

    bool isint(int a){
        if(a >= 0){
            return integer_data.size() == 1 && (integer_data[0] == a && isPositive);
        }
        else if(a <= 0){
            return integer_data.size() == 1 && (integer_data[0] == a && !isPositive);
        }
        else{
            return integer_data.size() == 1 && integer_data[0] == 0;
        }
    }

    static void make_new_prime(){
        ibi* newprime = new ibi(*ibi::prime_numbers.last());
        ibi one;
        one.Init(false);
        one.integer_data.push_back(1);
        *newprime = *newprime + one;

        while (true)
        {
            fm->_tempPushLayer();
            ibi copy;
            copy.Init(false);
            copy = *newprime;
            size_t prime_index = 0;
            ibi *prime = ibi::prime_numbers[prime_index];
            ibi result;
            result.Init(false);
            result = copy % *prime;

            bool isprime = false;
            int count = 0;
            while (!(copy.isint(1)))
            {
                while ((result).isint(0))
                {
                    copy = copy / *prime;
                    ++count;
                    result = copy % *prime;
                }
                ++prime_index;
                
                if (prime_index >= ibi::prime_numbers.size())
                {
                    break;
                }
                else{
                    prime = ibi::prime_numbers[prime_index];
                }
            }

            if(count > 0){
                *newprime = *newprime + one;
                fm->_tempPopLayer();
                continue;
            }
            else{
                fm->_tempPopLayer();
                break;
            }
        }

        ibi::prime_numbers.push_back(newprime);
    }

    //소인수 분해
    fmvecarr<unsigned int>* PrimeFactorization(){
        fmvecarr<unsigned int>* pfarr = fm->_tempNew(sizeof(fmvecarr<unsigned int>));
        pfarr->NULLState();
        pfarr->Init(8, false);

        fm->_tempPushLayer();
        ibi copy;
        copy.Init(false);
        copy = *this;
        size_t prime_index = 0;
        ibi* prime = ibi::prime_numbers[prime_index];
        ibi result;
        result.Init(false);
        result = copy % *prime;
        
        while(!(copy.isint(1))){
            int count = 0;
            while((result).isint(0)){
                copy = copy / *prime;
                ++count;
                result = copy % *prime;
            }
            pfarr[prime_index] = count;
            ++prime_index;
            if(prime_index >= ibi::prime_numbers.size()){
                //make new prime
                ibi::make_new_prime();
            }
            prime = ibi::prime_numbers[prime_index];
        }

        fm->_tempPopLayer();
    }

    ibi abs(){
        ibi r;
        r.Init(false);
        r = *this;
        r.isPositive = true;
    }

    ibi pow(ibi& A){
        ibi r;
        r.Init(false);
        r.integer_data.push_back(1);
        
        fm->_tempPushLayer();

        unsigned int addsiz = 32 * (A.integer_data.up-1);
        unsigned int v = A.integer_data.last();
        for(int i=0;i<32;++i){
            v = v >> 1;
            if(v == 0){
                break;
            }
            else{
                --addsiz;
            }
        }

        ibi muln;
        muln.Init(false);
        muln = *this;
        unsigned int loc = 0;
        for(loc=0;loc<addsiz;++loc){
            if(A.integer_data[loc/32] & (1 << (loc % 32))){
                r = r * muln;
            }
            muln = muln * muln;
        }

        fm->_tempPopLayer();

        return r;
    }

    ibi sqrt_approximate(ibi& A, unsigned int operation_times){
        ibi r;
        r.Init(false);
        r.integer_data.push_back(1);
        
        fm->_tempPushLayer();

        ibi one;
        one.Init(false);
        one.integer_data.push_back(1);

        for(int i=0;i<operation_times;++i){
            r = ((A - one) * r) + (*this / r.pow(A-one)) / A;
        }

        fm->_tempPopLayer();
        return r;
    }

    ibi tetration(ibi& A){
        ibi r;
        r.Init(false);
        r = *this;

        fm->_tempPushLayer();

        ibi k;
        k.Init(false);
        k = *this;

        ibi one;
        one.Init(false);
        one.integer_data.push_back(1);
        for(; one < k; one = one + 1){
            r = k.pow(r);
        }

        fm->_tempPopLayer();
        return r;
    }
};

class ibr{
    public:
    bool isPositive = true;
    bool islocal = false;
    ibi numerator;
    ibi denominator;

    ibr(){}
    ibr(ibr& ref){
        isPositive = ref.isPositive;
        numerator = ref.numerator;
        denominator = ref.denominator;
    }
    ~ibr(){
        if(islocal){
            numerator.integer_data.release();
            denominator.integer_data.release();
        }
    }

    void Init(bool local){
        islocal = local;
        numerator.Init(local);
        denominator.Init(local);
    }

    void operator=(ibi& ref){
        isPositive = ref.isPositive;
        numerator = ref.numerator;
        denominator = ref.denominator;
    }

    //fraction
    //약분
    void clean(){
        fm->_tempPushLayer();
        fmvecarr<unsigned int>* np = numerator.PrimeFactorization();
        fmvecarr<unsigned int>* dp = denominator.PrimeFactorization();
        size_t min = (np->up > dp->up) ? dp->up : np->up;
        for(int i=0;i<min;++i){
            if(np->at(i) > dp->at(i)){
                *np[i] -= *dp[i];
                *dp[i] = 0;
            }
            else{
                *dp[i] -= *np[i];
                *np[i] = 0;
            }
        }

        numerator.integer_data.up = 0;
        numerator.integer_data.push_back(1);
        for(int i=0;i<np->up;++i){
            for(int k=0;k<np->at(i);++k){
                numerator = numerator * ibi::prime_numbers[i];
            }
        }

        denominator.integer_data.up = 0;
        denominator.integer_data.push_back(1);
        for(int i=0;i<dp->up;++i){
            for(int k=0;k<dp->at(i);++k){
                denominator = denominator * ibi::prime_numbers[i];
            }
        }
        fm->_tempPopLayer();
    }

    bool operator>(ibr& A){
        if(this->isPositive != A.isPositive){
            return isPositive;
        }
        else{
            return !XOR(A.denominator * this->numerator > A.numerator * this->denominator, isPositive);
        }
    }
    
    bool operator<(ibr& A){
        if(this->isPositive != A.isPositive){
            return !isPositive;
        }
        else{
            return !XOR(A.denominator * this->numerator < A.numerator * this->denominator, isPositive);
        }
    }

    bool operator==(ibr& A){
        return (A.denominator * this->numerator == A.numerator * this->denominator) && isPositive == A.isPositive;
    }

    bool operator!=(ibr& A){
        return !(*this == A);
    }

    bool operator>=(ibr& A){
        return (*this > A) || (*this == A);
    }

    bool operator<=(ibr& A){
        return (*this < A) || (*this == A);
    }

    ibr operator+(ibr& A){
        ibr r;
        r.Init(false);
        fm->_tempPushLayer();

        r.denominator = this->denominator * A.denominator;
        if(this->isPositive == A.isPositive){
            r.numerator = (this->denominator * A.numerator) + (this->numerator * A.denominator);
        }
        else{
            if(A.denominator * this->numerator > A.numerator * this->denominator){
                r.numerator = (this->numerator * A.denominator) - (this->denominator * A.numerator);
            }
            else{
                r.numerator = (this->denominator * A.numerator) - (this->numerator * A.denominator);
                isPositive = !isPositive;
            }
        }
        r.clean();

        fm->_tempPopLayer();
        return r;
    }

    ibr operator-(ibr& A){
        ibr r;
        r.Init(false);
        fm->_tempPushLayer();

        r.denominator = this->denominator * A.denominator;
        if(this->isPositive == A.isPositive){
            if(A.denominator * this->numerator > A.numerator * this->denominator){
                r.numerator = (this->numerator * A.denominator) - (this->denominator * A.numerator);
            }
            else{
                r.numerator = (this->denominator * A.numerator) - (this->numerator * A.denominator);
                isPositive = !isPositive;
            }
        }
        else{
            r.numerator = (this->numerator * A.denominator) + (this->denominator * A.numerator);
        }
        r.clean();

        fm->_tempPopLayer();
        return r;
    }

    ibr operator*(ibr& A){
        ibr r;
        r.Init(false);
        fm->_tempPushLayer();
        r.numerator = this->numerator * A.numerator;
        r.denominator = this->denominator * A.denominator;
        r.clean();
        fm->_tempPopLayer();
        return r;
    }

    ibr operator/(ibr& A){
        ibr r;
        r.Init(false);
        fm->_tempPushLayer();
        r.numerator = this->numerator * A.denominator;
        r.denominator = this->denominator * A.numerator;
        r.clean();
        fm->_tempPopLayer();
        return r;
    }

    ibr exp_approximate(ibr& A, unsigned int operation_times){
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(1);
        r.denominator.integer_data.push_back(1);
        fm->_tempPushLayer();

        ibi one;
        one.Init(false);
        one.integer_data.push_back(1);

        for(int i=0;i<operation_times;++i){
            fm->_tempPushLayer();
            ibr rn0;
            rn0.Init(false);
            rn0.denominator = r.denominator;
            rn0.numerator = r.numerator * (A.denominator - one);
            ibr rn1;
            rn1.Init(false);
            rn1.denominator = r.denominator.pow(A.denominator - one);
            rn1.numerator = *this * r.numerator.pow(A.denominator - one);
            r = rn0 + rn1;
            r.denominator = r.denominator * A.denominator;
            r.clean();
            fm->_tempPopLayer();
        }

        r.denominator.pow(A.numerator);
        r.numerator.pow(A.numerator);

        fm->_tempPopLayer();
        return r;
    }
};
