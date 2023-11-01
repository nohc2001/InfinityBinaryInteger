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

    ibi(const ibi& ref){
        isPositive = ref.isPositive;
        size_t ref_size = ref.integer_data.up;
        if(ref_size > integer_data.size())
            integer_data.Init(ref_size, integer_data.islocal);
        else
            integer_data.up = ref_size;
        for(int i=0;i<ref_size;++i)
            integer_data[i] = ref.integer_data.Arr[i];
    }

    ibi(int num){
        Init(false);
        integer_data.push_back((unsigned int)num);
        isPositive = (num >= 0);
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
            unsigned int Tx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
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
        ibi At, Bt;
        At.Init(false);
        Bt.Init(false);

        ibi r;
        r.Init(false);

        At = A;
        Bt = B;
        At.isPositive = true;
        Bt.isPositive = true;

        fm->_tempPushLayer();
        if(At > Bt){
            r = At;
            for(int i=0;i<At.integer_data.up;++i){
                unsigned int Ax = (r.integer_data.up > i) ? r.integer_data[i] : 0;
                unsigned int Bx = (Bt.integer_data.up > i) ? Bt.integer_data[i] : 0;
                if(Ax < Bx){
                    carry_under(&r, i+1);
                }
                Ax -= Bx;
                r.integer_data[i] = Ax;
            }
            r.isPositive = pos[0];
        }
        else{
            r = Bt;
            for(int i=0;i<Bt.integer_data.up;++i){
                unsigned int Bx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
                unsigned int Ax = (At.integer_data.up > i) ? At.integer_data[i] : 0;
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
    }

    ibi operator-(ibi& A){
        if(isPositive == A.isPositive){
            return ibi::sub_absolute(*this, A);
        }
        else{
            return ibi::add_absolute(*this, A);
        }
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
        operand[2].integer_data[0] = R20;
        operand[2].integer_data[1] = R21;

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
        for(; one < A; ){
            fm->_tempPushLayer();
            r = k.pow(r);
            one = one + ibi::one;
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
        return r;
    }

    static ibi factorial(ibi& A){
        ibi r;
        r.Init(false);
        r = ibi::one;

        fm->_tempPushLayer();

        ibi one;
        one.Init(false);
        one.integer_data.push_back(2);
        for(; one < A; ){
            fm->_tempPushLayer();
            r = r * one;
            one = one + ibi::one;
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
        return r;
    }

    ibi dimenplus(ibi& X, ibi& dim, ibi& ordermap){
        if(dim == ibi(1)){
            return *this + X;
        }
        else{
            ibi r;
            r.Init(false);
            r = *this;

            fm->_tempPushLayer();

            ibi temp;
            temp.Init(false);
            temp = r;

            ibi index;
            index.Init(false);
            index = ibi(0);
            if(ordermap.integer_data[0] % 2 == 0){
                //front
                ordermap = ordermap >> 1;
                for(;index < X;){
                    fm->_tempPushLayer();
                    r = r.dimenplus(temp, dim-ibi(1), ordermap);
                    index = index + ibi(1);
                    fm->_tempPopLayer();
                }
            }
            else{
                //back
                ordermap = ordermap >> 1;
                for(;index < X;){
                    fm->_tempPushLayer();
                    r = temp.dimenplus(r, dim - ibi(1), ordermap);
                    index = index + ibi(1);
                    fm->_tempPopLayer();
                }
            }

            fm->_tempPopLayer();

            return r;
        }
    }

    lcstr& ToString(int base_num = 10){
        lcstr str;
        str.Init(integer_data.size() * 32, false);
        fm->_tempPushLayer();

        if(isPositive){
            str.push_back('+');
        }
        else{
            str.push_back('-');
        }

        ibi base;
        base.Init(false);
        base = ibi(base_num);
        ibi pastbase;
        pastbase.Init(false);
        pastbase = ibi(base_num);
        ibi r;
        r.Init(false);
        r = *this;
        while(base < *this){
            unsigned int n = (*this / base).integer_data[0] % base_num;
            lcstr nstr;
            string temp = to_string(n);
            nstr.Init(temp.size(), true);
            nstr = temp.c_str();
            if(base_num > 10){
                str.insert(1, ']');
                for(int i=temp.size()-1;i>=0;--i){
                    str.insert(1, nstr[i]);
                }
                str.insert(1, '[');
            }
            else{
                str.insert(1, nstr[0]);
            }
            base = base * pastbase;
        }
        fm->_tempPopLayer();
        return str;
    }
};

class ibr{
    public:
    bool isPositive = true;
    bool islocal = false;
    ibi numerator;
    ibi denominator;

    static bool befirst = true;
    static ibr one;

    static ibr bestPI;
    static ibi pi_oper_time;

    static ibr best_e;
    static ibi e_oper_time;

    ibr(){
        if(befirst){
            one->numerator.integer_data.push_back(1);
            one->denominator.integer_data.push_back(1);
            befirst = true;

            bestPI.Init(false);
            pi_oper_time.Init(false);
            pi_oper_time = ibi::one;
            getPI_approximate(ibi(10));
        }
    }
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

    ibr(int num, int den){
        ibr r;
        r.Init(false);
        r.numerator.push_back(num);
        r.denominator.push_back(den);
        r.isPositive = XOR((num > 0), (den > 0));
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

    ibr floor_function(){
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(1);
        r.denominator.integer_data.push_back(1);
        fm->_tempPushLayer();
        r.numerator = *this.numerator / *this.denominator;
        r.denominator = ibi::one;
        fm->_tempPopLayer();
        return r;
    }

    ibr operator%(ibr& A){
        ibr r;
        r.Init(false);

        fm->_tempPushLayer();
        r = *this - ((*this / A).floor_function() * A);
        fm->_tempPopLayer();

        return r;
    }

    ibr exp_approximate(ibr& A, ibi& operation_times){
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(1);
        r.denominator.integer_data.push_back(1);
        fm->_tempPushLayer();

        ibi one;
        one.Init(false);
        one.integer_data.push_back(1);

        for(;one<operation_times;one = one + ibi::one){
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

    static ibr gamma_approximate(ibr& A, ibi& operation_times){
        ibr r;
        r.Init(false);
        fm->_tempPushLayer();

        ibr n;
        n.Init(false);
        n.numerator.integer_data.push_back(1);
        n.denominator.integer_data.push_back(1);

        r = ibr::one / A;
        for(;n.numerator < operation_times;n = n + ibr::one){
            fm->_tempPushLayer();
            r = r * (ibr::one + (one / n)).exp_approximate(A, operation_times) / (ibr::one + A / n);
            fm->_tempPopLayer();
        }
        fm->_tempPopLayer();
        return r;
    }

    static ibr nCr(ibr& N, ibr& R, ibi& operation_times){
        return ibr::gamma_approximate(N, operation_times) / (ibr::gamma_approximate(R, operation_times) * ibr::gamma_approximate(N-R, operation_times));
    }

    static ibr nHr(ibr& N, ibr& R, ibi& operation_times){
        return ibr::gamma_approximate(N+R-ibr::one, operation_times) / (ibr::gamma_approximate(N-ibr::one, operation_times) * ibr::gamma_approximate(R, operation_times));
    }

    static ibr nPr(ibr& N, ibr& R, ibi& operation_times){
        return ibr::gamma_approximate(N, operation_times) / ibr::gamma_approximate(R, operation_times);
    }

    static ibr ln_approximate(ibr& X, ibi& operation_times){
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(0);
        r.denominator.integer_data.push_back(1);

        if (X.numerator < X.denominator)
        {
            fm->_tempPushLayer();
            ibi n;
            n.Init(false);
            n = ibi::one;
            for (; n < operation_times; n = n + ibi::one)
            {
                fm->_tempPushLayer();
                ibr frontm;
                frontm.Init(false);
                frontm = ibr::one;
                frontm.isPositive = n.integer_data[0] % 2;

                ibr tempX;
                tempX.Init(false);
                tempX = X - ibr::one;
                tempX.numerator.pow(n);
                tempX.denominator.pow(n);

                ibr tempN;
                tempN.Init(false);
                tempN = n;

                r = r + ((frontm * tempX) / tempN);
                r.clean();
                fm->_tempPopLayer();
            }

            fm->_tempPopLayer();
        }
        else{
            fm->_tempPushLayer();
            ibi n;
            n.Init(false);
            n = ibi::one;
            for (; n < operation_times; n = n + ibi::one)
            {
                fm->_tempPushLayer();
                ibr frontm;
                frontm.Init(false);
                frontm = ibr::one;
                frontm.isPositive = (int)(n.integer_data[0] % 2) - 1;

                ibr tempX;
                tempX.Init(false);
                tempX = (ibr::one / X) - ibr::one;
                tempX.numerator.pow(n);
                tempX.denominator.pow(n);

                ibr tempN;
                tempN.Init(false);
                tempN = n;

                r = r + ((frontm * tempX) / tempN);
                r.clean();
                fm->_tempPopLayer();
            }

            fm->_tempPopLayer();
        }

        return r;
    }

    static ibr getPI_approximate(ibi& operation_times){
        if(pi_oper_time >= operation_times) return bestPI;
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(0);
        r.denominator.integer_data.push_back(1);

        fm->_tempPushLayer();

        ibi n;
        n.Init(false);
        n = ibi::one - ibi::one;

        ibi two;
        two.Init(false);
        two = ibi::one + ibi::one;

        for (; n < operation_times; n = n + ibi::one)
        {
            fm->_tempPushLayer();
            ibr add;
            add.Init(false);
            add = ibr::one;
            add.numerator = ibi::one;
            add.denominator = two * n + ibi::one;
            add.isPositive = n.integer_data[0] % 2;
            r = r + add;
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
        
        bestPI = r;
        pi_oper_time = operation_times;
        
        return bestPI;
    }

    static ibr get_e_approximate(ibi& operation_times){
        if(best_e != nullptr && e_oper_time >= operation_times) return best_e;
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(0);
        r.denominator.integer_data.push_back(1);

        fm->_tempPushLayer();

        ibi n;
        n.Init(false);
        n = ibi::one - ibi::one;

        ibi two;
        two.Init(false);
        two = ibi::one + ibi::one;

        ibr add;
        add.Init(false);
        add = ibr::one;
        
        for (; n < operation_times; )
        {
            fm->_tempPushLayer();
            add.numerator = ibi::one;
            add.denominator = add.denominator * n;
            add.isPositive = n.integer_data[0] % 2;
            r = r + add;
            n = n + ibi::one;
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
        if(best_e != nullptr){
            *best_e = r;
            pi_oper_time = operation_times;
        }
        else{
            best_e = new ibr();
            best_e->Init(false);
            best_e = r;
            e_oper_time = new ibi();
            e_oper_time = operation_times;
        }
        
        return *best_e;
    }

    static ibr sin_approximate(ibr& X, ibi& getPI_operation_times, ibi& tayler_operation_times){
        ibr r;
        r.Init(false);
        r.numerator.integer_data.push_back(0);
        r.denominator.integer_data.push_back(1);

        fm->_tempPushLayer();

        getPI_approximate(getPI_operation_times);
        ibr loopLength;
        loopLength.Init(false);
        loopLength = *bestPI * (ibr::one + ibr::one);

        ibi index;
        index.Init(false);
        index = ibi::one - ibi::one;

        ibr add;
        add.Init(false);
        add = ibr::one;

        ibr tempX;
        tempX.Init(false);
        tempX = ibr::one;
        tempX = X % loopLength;
        
        add = tempX;
        for(;index < tayler_operation_times;){
            fm->_tempPushLayer();
            add = add * tempX * tempX;
            add = add / ((two * n) * (two * n + ibr::one));
            add.isPositive = !(n.integer_data[0] % 2);
            r = r + add;
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
        return r;
    }

    static ibr cos_approximate(ibr& X, ibi& getPI_operation_times, ibi& tayler_operation_times){
        return sin_approximate(X - (*bestPI / (ibr::one + ibr::one)), getPI_approximate, ibi& tayler_operation_times);
    }

    static ibr tan_approximate(ibr& X, ibi& getPI_operation_times, ibi& tayler_operation_times){
        return sin_approximate(X, getPI_approximate, tayler_operation_times) / cos_approximate(X, getPI_operation_times, tayler_operation_times);
    }
};
