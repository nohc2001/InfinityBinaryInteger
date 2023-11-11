#ifndef INF_BIN_INT
#define INF_BIN_INT
#include <math.h>
#include "arr_expend.h"
#include "Utill_FreeMemory.h"
using namespace freemem;

typedef unsigned int v4ui __attribute__ ((vector_size (16)));

constexpr wchar_t bytebased[16][17] = {
    {L'○',L'①',L'②',L'③',L'④',L'⑤',L'⑥',L'⑦',L'⑧',L'⑨',L'⑩',L'⑪',L'⑫',L'⑬',L'⑭',L'⑮'},
    {L'⑯',L'⑰',L'⑱', L'⑲', L'⑳', L'㉑', L'㉒', L'㉓', L'㉔', L'㉕', L'㉖', L'㉗', L'㉘', L'㉙', L'㉚', L'㉛'},
    {L'㉜', L'㉝', L'㉞', L'㉟', L'㊱', L'㊲', L'㊳', L'㊴', L'㊵', L'㊶', L'㊷', L'㊸', L'㊹', L'㊺', L'㊻', L'㊼'},
    {L'◎', L'⑴', L'⑵', L'⑶', L'⑷', L'⑸', L'⑹', L'⑺', L'⑻', L'⑼', L'⑽', L'⑾', L'⑿', L'⒀', L'⒁', L'⒂'},
    {L'日', L'㏠', L'㏡', L'㏢', L'㏣', L'㏤', L'㏥', L'㏦', L'㏧', L'㏨', L'㏩', L'㏪', L'㏫', L'㏬', L'㏭', L'㏮'},
    {L'㏯', L'㏰', L'㏱', L'㏲', L'㏳', L'㏴', L'㏵', L'㏶', L'㏷', L'㏸', L'㏹', L'㏺', L'㏻', L'㏼', L'㏽', L'㏾'},
    {L'㍘', L'㍙', L'㍚', L'㍛', L'㍜', L'㍝', L'㍞', L'㍟', L'㍠', L'㍡', L'㍢', L'㍣', L'㍤', L'㍥', L'㍦', L'㍧'},
    {L'口', L'一', L'二', L'三', L'四', L'五', L'六', L'七', L'八', L'九', L'十', L'土', L'王', L'玉', L'罕', L'丑'},
    {L'䷀', L'䷪', L'䷍', L'䷡', L'䷈', L'䷄', L'䷙', L'䷊', L'䷉', L'䷹', L'䷥', L'䷵', L'䷼', L'䷻', L'䷨', L'䷒'},
    {L'䷌', L'䷰', L'䷝', L'䷶', L'䷤', L'䷾', L'䷕', L'䷣', L'䷘', L'䷐', L'䷔', L'䷲', L'䷩', L'䷂', L'䷚', L'䷗'},
    {L'䷫', L'䷛', L'䷱', L'䷟', L'䷸', L'䷯', L'䷑', L'䷭', L'䷅', L'䷮', L'䷿', L'䷧', L'䷺', L'䷜', L'䷃', L'䷆'},
    {L'䷠', L'䷞', L'䷷', L'䷽', L'䷴', L'䷦', L'䷳', L'䷎', L'䷋', L'䷬', L'䷢', L'䷏', L'䷓', L'䷇', L'䷖', L'䷁'},
    {L'※', L'⒈', L'⒉', L'⒊', L'⒋', L'⒌', L'⒍', L'⒎', L'⒏', L'⒐', L'⒑', L'⒒', L'⒓', L'⒔', L'⒕', L'⒖'},
    {L'🄁', L'🄂', L'🄃', L'🄄', L'🄅', L'🄆', L'🄇', L'🄈', L'𝍠', L'𝍡', L'𝍢', L'𝍣', L'𝍤', L'𝍥', L'𝍦', L'𝍧', L'𝍨'},
    {L'□', L'▒', L'▥', L'▨', L'▦', L'▩', L'▣', L'■', L'◇', L'◈', L'◆', L'◎', L'◔', L'◐', L'◑', L'◕'},
    {L'●', L'❶', L'❷', L'❸', L'❹', L'❺', L'❻', L'❼', L'❽', L'❾', L'❿', L'⓫', L'⓬', L'⓭', L'⓮', L'⓯'}
};

struct uint_wstr{
    wchar_t str[5] = {};
};

uint_wstr Get256BasedExpr(unsigned int num) {
    unsigned int n = num;
    uint_wstr r;
    int i = n % 256;
    r.str[0] = bytebased[i/16][i%16];
    n = n >> 8;
    i = n % 256;
    r.str[1] = bytebased[i/16][i%16];
    n = n >> 8;
    i = n % 256;
    r.str[2] = bytebased[i/16][i%16];
    n = n >> 8;
    i = n % 256;
    r.str[3] = bytebased[i/16][i%16];
    r.str[4] = 0;
    return r;
}

inline bool XOR(bool a, bool b){
    return a ? !b : b;
}

class ibi{
    public:

    bool isPositive = true;
    bool islocal = true;
    fmvecarr<unsigned int> integer_data;

    static vecarr<ibi*> prime_numbers;

    ibi();
    ibi(const ibi& ref);
    ibi(int num);
    ibi(bool isp, unsigned int* data, unsigned int size);
    ~ibi();
    void Init(bool plocal);
    void Release();
    void operator=(const ibi& ref);
    bool cmp(const ibi& A, bool left_big, bool include_same) const;
    bool operator>(const ibi& A) const;
    bool operator>=(const ibi& A) const;
    bool operator<(const ibi& A) const;
    bool operator<=(const ibi& A) const;
    bool operator==(const ibi& A) const;
    bool operator!=(const ibi& A) const;
    static void carry(ibi* num, int carryloc);
    static void carry_under(ibi* num, int carryloc);
    static ibi& add_absolute(const ibi& A, const ibi& B);
    static ibi& sub_absolute(const ibi& A, const ibi& B);
    ibi& operator+(const ibi& A) const;
    ibi& operator-(const ibi& A) const;
    ibi& operator<<(const int& n) const;
    ibi& operator>>(const int& n) const;
    static ibi& mul_32(unsigned int A, unsigned int B);
    ibi& operator*(const ibi& A) const;
    static ibi& div_32(const ibi& A, unsigned int divn);
    ibi& operator/(const ibi& A) const;
    ibi& operator%(const ibi& A) const; 
    bool isint(int a) const;
    static void make_new_prime();

    //소인수 분해
    fmvecarr<unsigned int>* PrimeFactorization();
    ibi& abs() const;
    ibi& pow(const ibi& A) const;
    ibi& sqrt_approximate(const ibi& A, unsigned int operation_times) const;
    ibi& tetration(const ibi& A) const;
    static ibi& factorial(const ibi& A);
    ibi& dimenplus(const ibi& X, const ibi& dim, const ibi& ordermap) const;

    lcstr& ToString(int base_num) const;
    lwstr* dataString() const; // data origin(pow(2, 32) based expression of number)
};

class ibr{
    public:
    bool isPositive = true;
    bool islocal = false;
    ibi numerator;
    ibi denominator;

    static bool befirst;

    static ibr bestPI;
    static ibi pi_oper_time;

    static ibr best_e;
    static ibi e_oper_time;

    ibr();
    ibr(const ibr& ref);
    ~ibr();

    ibr(int num, int den);

    void Init(bool local);

    void operator=(const ibr& ref);

    //fraction
    //약분
    void clean();

    bool operator>(const ibr& A) const;
    bool operator<(const ibr& A) const;
    bool operator==(const ibr& A) const;
    bool operator!=(const ibr& A) const;
    bool operator>=(const ibr& A) const;
    bool operator<=(const ibr& A) const;
    ibr& operator+(const ibr& A) const;
    ibr& operator-(const ibr& A) const;
    ibr& operator*(const ibr& A) const;
    ibr& operator/(const ibr& A) const;
    ibr& floor_function() const;
    ibr& operator%(const ibr& A) const;
    ibr& exp_approximate(const ibr& A, const ibi& operation_times) const;
    static ibr& gamma_approximate(const ibr& A, const ibi& operation_times);
    static ibr& nCr(const ibr& N, const ibr& R, const ibi& operation_times);
    static ibr& nHr(const ibr& N, const ibr& R, const ibi& operation_times);
    static ibr& nPr(const ibr& N, const ibr& R, const ibi& operation_times);
    static ibr& ln_approximate(const ibr& X, const ibi& operation_times);
    static ibr& getPI_approximate(const ibi& operation_times);
    static ibr& get_e_approximate(const ibi& operation_times);
    static ibr& sin_approximate(const ibr& X, const ibi& getPI_operation_times, const ibi& tayler_operation_times);
    static ibr& cos_approximate(const ibr& X, const ibi& getPI_operation_times, const ibi& tayler_operation_times);
    static ibr& tan_approximate(const ibr& X, const ibi& getPI_operation_times, const ibi& tayler_operation_times);
};

#define CreateDataFM(type, name) type& name = *(type*)fm->_tempNew(sizeof(type)); name.Init(false);
#define ricast(type, value) reinterpret_cast<type>(value);
vecarr<ibi*> ibi::prime_numbers;

bool ibr::befirst = false;
ibr ibr::bestPI;
ibi ibr::pi_oper_time;
ibr ibr::best_e;
ibi ibr::e_oper_time;

ibi::ibi() : isPositive(true)
{
    integer_data.NULLState();
}

ibi::ibi(const ibi &ref)
{
    isPositive = ref.isPositive;
    size_t ref_size = ref.integer_data.size();
    if (ref_size > integer_data.maxsize)
        integer_data.Init(ref_size, integer_data.islocal);
    
    integer_data.up = ref_size;
    for (int i = 0; i < ref_size; ++i)
        integer_data[i] = ref.integer_data.Arr[i];
}

ibi::ibi(int num)
{
    Init(false);
    integer_data.push_back((unsigned int)num);
    isPositive = (num >= 0);
}

ibi::ibi(bool isp, unsigned int* data, unsigned int size){
    Init(false);
    isPositive = isp;
    for(int i=0;i<size;++i){
        integer_data.push_back(data[i]);
    }
}

ibi::~ibi()
{
    if (islocal)
        integer_data.release();
}

void ibi::Init(bool plocal)
{
    integer_data.Init(2, false);
    islocal = plocal;
}

void ibi::Release()
{
    integer_data.release();
}

void ibi::operator=(const ibi &ref)
{
    isPositive = ref.isPositive;
    size_t ref_size = (int)ref.integer_data.up;
    if (ref_size > integer_data.maxsize)
        integer_data.Init(ref_size, integer_data.islocal);
    integer_data.up = ref_size;
    for (int i = 0; i < ref_size; ++i)
        integer_data[i] = ref.integer_data[i];
}

bool ibi::cmp(const ibi &A, bool left_big, bool include_same) const
{
    if (isPositive == A.isPositive)
    {
        bool k = true;
        k = left_big ? k : !k;
        k = isPositive ? k : !k;

        if (integer_data.up > A.integer_data.up)
            return k;
        else if (integer_data.up < A.integer_data.up)
            return !k;
        else
        {
            for (int i = integer_data.up - 1; i >= 0; --i)
            {
                if (integer_data[i] > A.integer_data[i])
                    return k;
                else if (integer_data[i] < A.integer_data[i])
                    return !k;
            }
            return include_same;
        }
    }
    else
    {
        if (isPositive && !A.isPositive)
            return left_big;
        if (!isPositive && A.isPositive)
            return !left_big;
    }
}

bool ibi::operator>(const ibi &A) const
{
    return cmp(A, true, false);
}

bool ibi::operator>=(const ibi &A) const
{
    return cmp(A, true, true);
}

bool ibi::operator<(const ibi &A) const
{
    return cmp(A, false, false);
}

bool ibi::operator<=(const ibi &A) const
{
    return cmp(A, false, true);
}

bool ibi::operator==(const ibi &A) const
{
    if (isPositive != A.isPositive)
        return false;
    else
    {
        if (integer_data.up != A.integer_data.up)
            return false;
        for (int i = integer_data.up - 1; i >= 0; --i)
        {
            if (integer_data[i] != A.integer_data[i])
                return false;
        }
        return true;
    }
}

bool ibi::operator!=(const ibi &A) const
{
    if (isPositive != A.isPositive)
        return true;
    else
    {
        if (integer_data.up != A.integer_data.up)
            return true;
        for (int i = integer_data.up - 1; i >= 0; --i)
        {
            if (integer_data[i] != A.integer_data[i])
                return true;
        }
        return false;
    }
}

void ibi::carry(ibi *num, int carryloc)
{
    if (num->integer_data.size() <= carryloc)
    {
        num->integer_data.push_back(1);
    }
    else
    {
        if (num->integer_data[carryloc] == (unsigned int)-1)
        {
            // carry
            carry(num, carryloc + 1);
        }
        num->integer_data[carryloc] += 1;
    }
}

void ibi::carry_under(ibi *num, int carryloc)
{
    if (carryloc >= num->integer_data.size())
        return;
    if (num->integer_data[carryloc] == 0)
    {
        // carry
        carry_under(num, carryloc + 1);
    }
    num->integer_data[carryloc] -= 1;
}

ibi& ibi::add_absolute(const ibi &A, const ibi &B)
{
	CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = B;
    int maxsiz = (A.integer_data.size() > B.integer_data.size()) ? A.integer_data.size() : B.integer_data.size();
    int i;
    for (i = 0; i < maxsiz; ++i)
    {
        unsigned int Ax = (A.integer_data.up > i) ? A.integer_data[i] : 0;
        unsigned int Tx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
        unsigned int max = (Ax > Tx) ? Ax : Tx;
        Tx += Ax;
        if (Tx < max)
        {
            carry(&r, i + 1);
        }
        r.integer_data[i] = Tx;
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::sub_absolute(const ibi &A, const ibi &B)
{
    bool pos[2] = {A.isPositive, !B.isPositive};
    CreateDataFM(ibi, r);
	
	ibi At, Bt;
    At.Init(false);
    Bt.Init(false);
	
    At = A;
    Bt = B;
    At.isPositive = true;
    Bt.isPositive = true;

    fm->_tempPushLayer();
    if (At > Bt)
    {
        r = At;
        for (int i = 0; i < At.integer_data.up; ++i)
        {
            unsigned int Ax = (r.integer_data.up > i) ? r.integer_data[i] : 0;
            unsigned int Bx = (Bt.integer_data.up > i) ? Bt.integer_data[i] : 0;
            if (Ax < Bx)
            {
                carry_under(&r, i + 1);
            }
            Ax -= Bx;
            r.integer_data[i] = Ax;
        }
        r.isPositive = pos[0];
    }
    else
    {
        r = Bt;
        for (int i = 0; i < Bt.integer_data.up; ++i)
        {
            unsigned int Bx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
            unsigned int Ax = (At.integer_data.up > i) ? At.integer_data[i] : 0;
            if (Bx < Ax)
            {
                carry_under(&r, i + 1);
            }
            Bx -= Ax;
            r.integer_data[i] = Bx;
        }
        r.isPositive = pos[1];
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator+(const ibi &A) const
{
    if (isPositive == A.isPositive)
    {
        return ibi::add_absolute(*this, A);
    }
    else
    {
        return ibi::sub_absolute(*this, A);
    }
}

ibi& ibi::operator-(const ibi &A) const
{
    if (isPositive == A.isPositive)
    {
        return ibi::sub_absolute(*this, A);
    }
    else
    {
        return ibi::add_absolute(*this, A);
    }
}

ibi& ibi::operator<<(const int& n) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = *this;
    for (int i = 0; i < n; ++i)
    {
        r.integer_data.insert(0, 0);
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator>>(const int& n) const
{
    CreateDataFM(ibi, r);
    
    fm->_tempPushLayer();
    r = *this;
    for (int i = 0; i < n; ++i)
    {
        r.integer_data.erase(0);
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::mul_32(unsigned int A, unsigned int B)
{
    CreateDataFM(ibi, r);
    
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

    r = operand[0].operator+(operand[1]);
    r = r + operand[2];

    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator*(const ibi &A) const
{
    CreateDataFM(ibi, r);
    
    fm->_tempPushLayer();
    r.integer_data.push_back(0);
    ibi *thismulibi = new ibi[A.integer_data.up];
    for (int i = 0; i < integer_data.up; ++i)
    {
        thismulibi[i].Init(true);
        thismulibi[i].integer_data.push_back(0);
        unsigned int uii = integer_data[i];
        ibi *mulibi = new ibi[A.integer_data.up];
        for (int k = 0; k < A.integer_data.up; ++k)
        {
            mulibi[k].Init(true);
            mulibi[k] = mul_32(uii, A.integer_data[k]);
            thismulibi[i] = thismulibi[i] + mulibi[k];
        }
        delete[] mulibi;
        r = r + thismulibi[i];
    }
    delete[] thismulibi;
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::div_32(const ibi &A, unsigned int divn)
{
    CreateDataFM(ibi, r);
    
    r.integer_data.push_back(0);
    r.integer_data.Init(A.integer_data.up, false);
    for (int i = 0; i < r.integer_data.up; ++i)
    {
        r.integer_data[i] = 0;
    }
    if (divn == 0)
    {
        return r;
    }

    fm->_tempPushLayer();

    ibi tempA;
    tempA.Init(false);
    tempA = A;

    ibi tempDivn;
    tempDivn.Init(false);
    tempDivn = divn;
    
    double max = powf64(2.0, 32.0);
    double dv = (double)divn;
    bool updatefirst = true;

    bool zero_stack = 0;
    for (int i = tempA.integer_data.up - 1; i >= 0; --i)
    {
        if (zero_stack == false)
        {
            unsigned int ad = tempA.integer_data[i] / divn;
            if (ad == 0)
            {
                zero_stack = true;
            }
            else
            {
                r.integer_data[i] = ad;
            }
        }
        else
        {
            unsigned int seekstart = (unsigned int)((double)tempA.integer_data[i + 1] * max / dv);
            bool saturate = false;
            unsigned int lastnum = seekstart;
            while (!saturate)
            {
                fm->_tempPushLayer();
                ibi temp;
                temp.Init(false);
                temp.integer_data.push_back(A.integer_data[i]);
                temp.integer_data.push_back(tempA.integer_data[i + 1]);
                    ibi dv = mul_32(divn, seekstart);
                if (dv > temp)
                {
                    saturate = true;
                }
                else
                {
                    lastnum = seekstart;
                    ++seekstart;
                }
                fm->_tempPopLayer();
            }

            ibi tempB;
            tempB.Init(false);
            tempB.integer_data.Init(i, false);
            for (int k = 0; k < i; ++k)
            {
                tempB.integer_data[k] = 0;
            }
            tempB.integer_data[i] = lastnum;

            if (updatefirst)
                r.integer_data.up = i + 1;
            r.integer_data[i] = lastnum;
            tempA = tempA - (tempB * tempDivn);
            zero_stack = false;
        }
    }

    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator/(const ibi &A) const
{
    // this / a
    CreateDataFM(ibi, r);
    

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
    while (vpos >= 0)
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
            else
            {
                saturate = false;
            }
        }

        tempV = tempV - (tempA * tR);
        for (int k = tempV.integer_data.up - 1; k >= 0; --k)
        {
            if (tempV.integer_data[k] == 0)
                tempA.integer_data.up -= 1;
            else
            {
                break;
            }
        }
        r = r + tR;

        fm->_tempPopLayer();
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator%(const ibi &A) const
{
    CreateDataFM(ibi, r);
    ;
    r = *this - (*this / A) * A;
    return r;
}

bool ibi::isint(int a) const
{
    if (a >= 0)
    {
        return integer_data.size() == 1 && (integer_data[0] == a && isPositive);
    }
    else if (a <= 0)
    {
        return integer_data.size() == 1 && (integer_data[0] == a && !isPositive);
    }
    else
    {
        return integer_data.size() == 1 && integer_data[0] == 0;
    }
}

void ibi::make_new_prime()
{
    ibi *newprime = new ibi(*ibi::prime_numbers.last());
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
            else
            {
                prime = ibi::prime_numbers[prime_index];
            }
        }

        if (count > 0)
        {
            *newprime = *newprime + one;
            fm->_tempPopLayer();
            continue;
        }
        else
        {
            fm->_tempPopLayer();
            break;
        }
    }

    ibi::prime_numbers.push_back(newprime);
}

// 소인수 분해
fmvecarr<unsigned int> *ibi::PrimeFactorization()
{
    fmvecarr<unsigned int> *pfarr = ricast(fmvecarr<unsigned int>*, fm->_tempNew(sizeof(fmvecarr<unsigned int>)));
    pfarr->NULLState();
    pfarr->Init(8, false);

    fm->_tempPushLayer();
    ibi copy;
    copy.Init(false);
    copy = *this;
    size_t prime_index = 0;
    ibi *prime = ibi::prime_numbers[prime_index];
    ibi result;
    result.Init(false);
    result = copy % *prime;

    while (!(copy.isint(1)))
    {
        int count = 0;
        while ((result).isint(0))
        {
            copy = copy / *prime;
            ++count;
            result = copy % *prime;
        }
        (*pfarr)[prime_index] = count;
        ++prime_index;
        if (prime_index >= ibi::prime_numbers.size())
        {
            // make new prime
            ibi::make_new_prime();
        }
        prime = ibi::prime_numbers[prime_index];
    }

    fm->_tempPopLayer();
	
	return pfarr;
}

ibi& ibi::abs() const
{
    CreateDataFM(ibi, r);
    r = *this;
    r.isPositive = true;
	return r;
}

ibi& ibi::pow(const ibi &A) const
{
    CreateDataFM(ibi, r);
    r.integer_data.push_back(1);

    fm->_tempPushLayer();

    unsigned int addsiz = 32 * (A.integer_data.up - 1);
    unsigned int v = (unsigned int)A.integer_data.last();
    for (int i = 0; i < 32; ++i)
    {
        v = v >> 1;
        if (v == 0)
        {
            break;
        }
        else
        {
            --addsiz;
        }
    }

    ibi muln;
    muln.Init(false);
    muln = *this;
    unsigned int loc = 0;
    for (loc = 0; loc < addsiz; ++loc)
    {
        if (A.integer_data[loc / 32] & (1 << (loc % 32)))
        {
            r = r * muln;
        }
        muln = muln * muln;
    }

    fm->_tempPopLayer();

    return r;
}

ibi& ibi::sqrt_approximate(const ibi &A, unsigned int operation_times) const
{
    CreateDataFM(ibi, r);
    ;
    r.integer_data.push_back(1);

    fm->_tempPushLayer();

    ibi one;
    one.Init(false);
    one.integer_data.push_back(1);

    for (int i = 0; i < operation_times; ++i)
    {
        r = ((A - one) * r) + (*this / r.pow(A - one)) / A;
    }

    fm->_tempPopLayer();
    return r;
}

ibi& ibi::tetration(const ibi &A) const
{
    CreateDataFM(ibi, r);
    r = *this;

    fm->_tempPushLayer();

    ibi k;
    k.Init(false);
    k = *this;

    ibi one;
    one.Init(false);
    one.integer_data.push_back(1);
    for (; one < A;)
    {
        fm->_tempPushLayer();
        r = k.pow(r);
        one = one + ibi(1);
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();
    return r;
}

ibi& ibi::factorial(const ibi &A)
{
    CreateDataFM(ibi, r);
    r = ibi(1);

    fm->_tempPushLayer();

    ibi one;
    one.Init(false);
    one.integer_data.push_back(2);
    for (; one < A;)
    {
        fm->_tempPushLayer();
        r = r * one;
        one = one + ibi(1);
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();
    return r;
}

ibi& ibi::dimenplus(const ibi &X, const ibi &dim, const ibi &ordermap) const
{
    if (dim == ibi(1))
    {
        return *this + X;
    }
    else
    {
        CreateDataFM(ibi, r);
        r = *this;

        fm->_tempPushLayer();

        ibi temp;
        temp.Init(false);
        temp = r;
		
		ibi tempO;
        tempO.Init(false);
        tempO = ordermap;

        ibi index;
        index.Init(false);
        index = ibi(0);
        if (tempO.integer_data[0] % 2 == 0)
        {
            // front
            tempO = tempO >> 1;
            for (; index < X;)
            {
                fm->_tempPushLayer();
                r = r.dimenplus(temp, dim - ibi(1), tempO);
                index = index + ibi(1);
                fm->_tempPopLayer();
            }
        }
        else
        {
            // back
            tempO = tempO >> 1;
            for (; index < X;)
            {
                fm->_tempPushLayer();
                r = temp.dimenplus(r, dim - ibi(1), tempO);
                index = index + ibi(1);
                fm->_tempPopLayer();
            }
        }

        fm->_tempPopLayer();

        return r;
    }
}

lcstr& ibi::ToString(int base_num = 10) const
{
    lcstr str;
    str.Init(integer_data.size() * 32, false);
    fm->_tempPushLayer();

    if (isPositive)
    {
        str.push_back('+');
    }
    else
    {
        str.push_back('-');
    }

    ibi base;
    base.Init(false);
    base = ibi(1);
    ibi pastbase;
    pastbase.Init(false);
    pastbase = ibi(base_num);
    CreateDataFM(ibi, r);
	
    r = *this;
    r.isPositive = true;

    while (base < r)
    {
        unsigned int n = (r / base).integer_data[0] % base_num;
        lcstr nstr;
        string temp = to_string(n);
        nstr.Init(temp.size(), true);
        nstr = temp.c_str();
        if (base_num > 10)
        {
            str.insert(1, ']');
            for (int i = temp.size() - 1; i >= 0; --i)
            {
                str.insert(1, nstr[i]);
            }
            str.insert(1, '[');
        }
        else
        {
            str.insert(1, nstr[0]);
        }
        base = base * pastbase;
    }
    fm->_tempPopLayer();
    return str;
}

lwstr* ibi::dataString() const
{
    lwstr* str = (lcstr*)fm->_tempNew(sizeof(lwstr));
    str->Init(integer_data.size() * 32, false);
    fm->_tempPushLayer();

    str->push_back(L'[');

    if (isPositive)
    {
        str->push_back(L'+');
    }
    else
    {
        str->push_back(L'-');
    }

    for(int i=this->integer_data.size() - 1;i>=0;--i){
        str->push_back(L':');
        uint_wstr uintstr = Get256BasedExpr(integer_data[i]);
        for(int k=0;k<4;++k){
            str->push_back(uintstr[k]);
        }
    }

    str->push_back(L']');
    fm->_tempPopLayer();
    return str;
}

ibr::ibr()
{
    if (befirst)
    {
        befirst = true;

        bestPI.Init(false);
        pi_oper_time.Init(false);
        pi_oper_time = ibi(1);
        getPI_approximate(ibi(10));
    }
}
ibr::ibr(const ibr &ref)
{
    isPositive = ref.isPositive;
    numerator = ref.numerator;
    denominator = ref.denominator;
}
ibr::~ibr()
{
    if (islocal)
    {
        numerator.integer_data.release();
        denominator.integer_data.release();
    }
}

ibr::ibr(int num, int den)
{
    numerator.integer_data.push_back(num);
    denominator.integer_data.push_back(den);
    isPositive = XOR((num > 0), (den > 0));
}

void ibr::Init(bool local)
{
    islocal = local;
    numerator.Init(local);
    denominator.Init(local);
}

void ibr::operator=(const ibr &ref)
{
    isPositive = ref.isPositive;
    numerator = ref.numerator;
    denominator = ref.denominator;
}

// fraction
// 약분
void ibr::clean()
{
    fm->_tempPushLayer();
    fmvecarr<unsigned int> *np = numerator.PrimeFactorization();
    fmvecarr<unsigned int> *dp = denominator.PrimeFactorization();
    size_t min = (np->up > dp->up) ? dp->up : np->up;
    for (int i = 0; i < min; ++i)
    {
        if (np->at(i) > dp->at(i))
        {
            (*np)[i] -= (*dp)[i];
            (*dp)[i] = 0;
        }
        else
        {
            (*dp)[i] -= (*np)[i];
            (*np)[i] = 0;
        }
    }

    numerator.integer_data.up = 0;
    numerator.integer_data.push_back(1);
    for (int i = 0; i < np->up; ++i)
    {
        for (int k = 0; k < np->at(i); ++k)
        {
            numerator = numerator * (*ibi::prime_numbers[i]);
        }
    }

    denominator.integer_data.up = 0;
    denominator.integer_data.push_back(1);
    for (int i = 0; i < dp->up; ++i)
    {
        for (int k = 0; k < dp->at(i); ++k)
        {
            denominator = denominator * (*ibi::prime_numbers[i]);
        }
    }
    fm->_tempPopLayer();
}

bool ibr::operator>(const ibr &A) const
{
    if (this->isPositive != A.isPositive)
    {
        return isPositive;
    }
    else
    {
        return !XOR(A.denominator * this->numerator > A.numerator * this->denominator, isPositive);
    }
}

bool ibr::operator<(const ibr &A) const
{
    if (this->isPositive != A.isPositive)
    {
        return !isPositive;
    }
    else
    {
        return !XOR(A.denominator * this->numerator < A.numerator * this->denominator, isPositive);
    }
}

bool ibr::operator==(const ibr &A) const
{
    return (A.denominator * this->numerator == A.numerator * this->denominator) && isPositive == A.isPositive;
}

bool ibr::operator!=(const ibr &A) const
{
    return !(*this == A);
}

bool ibr::operator>=(const ibr &A) const
{
    return (*this > A) || (*this == A);
}

bool ibr::operator<=(const ibr &A) const
{
    return (*this < A) || (*this == A);
}

ibr& ibr::operator+(const ibr &A) const
{
    CreateDataFM(ibr, r);
    fm->_tempPushLayer();

    r.denominator = this->denominator * A.denominator;
    if (this->isPositive == A.isPositive)
    {
        r.numerator = (this->denominator * A.numerator) + (this->numerator * A.denominator);
    }
    else
    {
        if (A.denominator * this->numerator > A.numerator * this->denominator)
        {
            r.numerator = (this->numerator * A.denominator) - (this->denominator * A.numerator);
        }
        else
        {
            r.numerator = (this->denominator * A.numerator) - (this->numerator * A.denominator);
            r.isPositive = !r.isPositive;
        }
    }
    r.clean();

    fm->_tempPopLayer();
    return r;
}

ibr& ibr::operator-(const ibr &A) const
{
    CreateDataFM(ibr, r);
    fm->_tempPushLayer();

    r.denominator = this->denominator * A.denominator;
    if (this->isPositive == A.isPositive)
    {
        if (A.denominator * this->numerator > A.numerator * this->denominator)
        {
            r.numerator = (this->numerator * A.denominator) - (this->denominator * A.numerator);
        }
        else
        {
            r.numerator = (this->denominator * A.numerator) - (this->numerator * A.denominator);
            r.isPositive = !r.isPositive;
        }
    }
    else
    {
        r.numerator = (this->numerator * A.denominator) + (this->denominator * A.numerator);
    }
    r.clean();

    fm->_tempPopLayer();
    return r;
}

ibr& ibr::operator*(const ibr &A) const
{
    CreateDataFM(ibr, r);
    fm->_tempPushLayer();
    r.numerator = this->numerator * A.numerator;
    r.denominator = this->denominator * A.denominator;
    r.clean();
    fm->_tempPopLayer();
    return r;
}

ibr& ibr::operator/(const ibr &A) const
{
    CreateDataFM(ibr, r);
    fm->_tempPushLayer();
    r.numerator = this->numerator * A.denominator;
    r.denominator = this->denominator * A.numerator;
    r.clean();
    fm->_tempPopLayer();
    return r;
}

ibr& ibr::floor_function() const
{
    CreateDataFM(ibr, r);
    r.numerator.integer_data.push_back(1);
    r.denominator.integer_data.push_back(1);
    fm->_tempPushLayer();
    r.numerator = this->numerator / this->denominator;
    r.denominator = ibi(1);
    fm->_tempPopLayer();
    return r;
}

ibr& ibr::operator%(const ibr &A) const
{
    CreateDataFM(ibr, r);

    fm->_tempPushLayer();
    r = *this - ((*this / A).floor_function() * A);
    fm->_tempPopLayer();

    return r;
}

ibr& ibr::exp_approximate(const ibr &A, const ibi &operation_times) const
{
    CreateDataFM(ibr, r);
    r.numerator.integer_data.push_back(1);
    r.denominator.integer_data.push_back(1);
    fm->_tempPushLayer();

    ibi one;
    one.Init(false);
    one.integer_data.push_back(1);

    for (; one < operation_times; one = one + ibi(1))
    {
        fm->_tempPushLayer();
        ibr rn0;
        rn0.Init(false);
        rn0.denominator = r.denominator;
        rn0.numerator = r.numerator * (A.denominator - one);
        ibr rn1;
        rn1.Init(false);
        rn1.denominator = this->denominator * r.denominator.pow(A.denominator - one);
        rn1.numerator = this->numerator * r.numerator.pow(A.denominator - one);
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

ibr& ibr::gamma_approximate(const ibr &A, const ibi &operation_times)
{
    CreateDataFM(ibr, r);
    ;
    fm->_tempPushLayer();

    ibr n;
    n.Init(false);
    n.numerator.integer_data.push_back(1);
    n.denominator.integer_data.push_back(1);

    r = ibr(1, 1) / A;
    for (; n.numerator < operation_times; n = n + ibr(1, 1))
    {
        fm->_tempPushLayer();
        r = r * (ibr(1, 1) + (ibr(1, 1) / n)).exp_approximate(A, operation_times) / (ibr(1, 1) + A / n);
        fm->_tempPopLayer();
    }
    fm->_tempPopLayer();
    return r;
}

ibr& ibr::nCr(const ibr &N, const ibr &R, const ibi &operation_times)
{
    return ibr::gamma_approximate(N, operation_times) / (ibr::gamma_approximate(R, operation_times) * ibr::gamma_approximate(N - R, operation_times));
}

ibr& ibr::nHr(const ibr &N, const ibr &R, const ibi &operation_times)
{
    return ibr::gamma_approximate(N + R - ibr(1, 1), operation_times) / (ibr::gamma_approximate(N - ibr(1, 1), operation_times) * ibr::gamma_approximate(R, operation_times));
}

ibr& ibr::nPr(const ibr &N, const ibr &R, const ibi &operation_times)
{
    return ibr::gamma_approximate(N, operation_times) / ibr::gamma_approximate(R, operation_times);
}

ibr& ibr::ln_approximate(const ibr &X, const ibi &operation_times)
{
    CreateDataFM(ibr, r);
    
    r.numerator.integer_data.push_back(0);
    r.denominator.integer_data.push_back(1);

    if (X.numerator < X.denominator)
    {
        fm->_tempPushLayer();
        ibi n;
        n.Init(false);
        n = ibi(1);
        for (; n < operation_times; n = n + ibi(1))
        {
            fm->_tempPushLayer();
            ibr frontm;
            frontm.Init(false);
            frontm = ibr(1, 1);
            frontm.isPositive = n.integer_data[0] % 2;

            ibr tempX;
            tempX.Init(false);
            tempX = X.operator-(ibr(1, 1));
            tempX.numerator.pow(n);
            tempX.denominator.pow(n);

            ibr tempN;
            tempN.Init(false);
            tempN.numerator = n;
			tempN.denominator = ibi(1);

            r = r + ((frontm * tempX) / tempN);
            r.clean();
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
    }
    else
    {
        fm->_tempPushLayer();
        ibi n;
        n.Init(false);
        n = ibi(1);
        for (; n < operation_times; n = n + ibi(1))
        {
            fm->_tempPushLayer();
            ibr frontm;
            frontm.Init(false);
            frontm = ibr(1, 1);
            frontm.isPositive = (int)(n.integer_data[0] % 2) - 1;

            ibr tempX;
            tempX.Init(false);
            tempX = (ibr(1, 1) / X) - ibr(1, 1);
            tempX.numerator.pow(n);
            tempX.denominator.pow(n);

            ibr tempN;
            tempN.Init(false);
            tempN.numerator = n;
			tempN.denominator = ibi(1);

            r = r + ((frontm * tempX) / tempN);
            r.clean();
            fm->_tempPopLayer();
        }

        fm->_tempPopLayer();
    }

    return r;
}

ibr& ibr::getPI_approximate(const ibi &operation_times)
{
    if (pi_oper_time >= operation_times)
        return bestPI;
    CreateDataFM(ibr, r);
    ;
    r.numerator.integer_data.push_back(0);
    r.denominator.integer_data.push_back(1);

    fm->_tempPushLayer();

    ibi n;
    n.Init(false);
    n = ibi(1) - ibi(1);

    ibi two;
    two.Init(false);
    two = ibi(1) + ibi(1);

    for (; n < operation_times; n = n + ibi(1))
    {
        fm->_tempPushLayer();
        ibr add;
        add.Init(false);
        add = ibr(1, 1);
        add.numerator = ibi(1);
        add.denominator = two * n + ibi(1);
        add.isPositive = n.integer_data[0] % 2;
        r = r + add;
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();

    bestPI = r;
    pi_oper_time = operation_times;

    return bestPI;
}

ibr& ibr::get_e_approximate(const ibi &operation_times)
{
    if (e_oper_time >= operation_times)
        return best_e;
    CreateDataFM(ibr, r);
    
    r.numerator.integer_data.push_back(0);
    r.denominator.integer_data.push_back(1);

    fm->_tempPushLayer();

    ibi n;
    n.Init(false);
    n = ibi(1) - ibi(1);

    ibi two;
    two.Init(false);
    two = ibi(1) + ibi(1);

    ibr add;
    add.Init(false);
    add = ibr(1, 1);

    for (; n < operation_times;)
    {
        fm->_tempPushLayer();
        add.numerator = ibi(1);
        add.denominator = add.denominator * n;
        add.isPositive = n.integer_data[0] % 2;
        r = r + add;
        n = n + ibi(1);
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();

    best_e = r;
    e_oper_time = operation_times;

    return best_e;
}

ibr& ibr::sin_approximate(const ibr &X, const ibi &getPI_operation_times, const ibi &tayler_operation_times)
{
    CreateDataFM(ibr, r);
    r.numerator.integer_data.push_back(0);
    r.denominator.integer_data.push_back(1);

    fm->_tempPushLayer();

    getPI_approximate(getPI_operation_times);
    ibr loopLength;
    loopLength.Init(false);
    loopLength = bestPI * (ibr(1, 1) + ibr(1, 1));

    ibi index;
    index.Init(false);
    index = ibi(1) - ibi(1);

    ibr add;
    add.Init(false);
    add = ibr(1, 1);

    ibr tempX;
    tempX.Init(false);
    tempX = ibr(1, 1);
    tempX = X % loopLength;
	
	ibr two;
    two.Init(false);
    two = ibr(2, 1);
	
	ibr indexr;
    indexr.Init(false);
    indexr = ibr(1, 1);

    add = tempX;
    for (; index < tayler_operation_times;)
    {
        fm->_tempPushLayer();
        add = add * tempX * tempX;
        add = add / ((two * indexr) * (two * indexr + ibr(1, 1)));
        add.isPositive = !(index.integer_data[0] % 2);
        r = r + add;
		index = index + ibi(1);
		indexr = indexr + ibr(1, 1);
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();
    return r;
}

ibr& ibr::cos_approximate(const ibr &X, const ibi &getPI_operation_times, const ibi &tayler_operation_times)
{
    return sin_approximate(X - (bestPI / (ibr(1, 1) + ibr(1, 1))), getPI_operation_times, tayler_operation_times);
}

ibr& ibr::tan_approximate(const ibr &X, const ibi &getPI_operation_times, const ibi &tayler_operation_times)
{
    return sin_approximate(X, getPI_operation_times, tayler_operation_times) / cos_approximate(X, getPI_operation_times, tayler_operation_times);
}
#endif