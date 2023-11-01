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

    ibi();
    ibi(const ibi& ref);
    ibi(int num);
    ~ibi();
    void Init(bool plocal);
    void Release();
    ibi& operator=(const ibi& ref);
    inline bool cmp(ibi& A, bool left_big, bool include_same);
    bool operator>(ibi& A);
    bool operator>=(ibi& A);
    bool operator<(ibi& A);
    bool operator<=(ibi& A);
    bool operator==(ibi& A);
    bool operator!=(ibi& A);
    static void carry(ibi* num, int carryloc);
    static void carry_under(ibi* num, int carryloc);
    static ibi add_absolute(const ibi& A, const ibi& B);
    static ibi sub_absolute(ibi& A, ibi& B);
    ibi operator+(const ibi& A);
    ibi operator-(ibi& A);
    ibi operator<<(int n);
    ibi operator>>(int n);
    ibi mul_32(unsigned int A, unsigned int B);
    ibi operator*(ibi& A);
    ibi div_32(ibi& A, unsigned int divn);
    ibi operator/(ibi& A);
    ibi operator%(ibi& A);
    bool isint(int a);
    static void make_new_prime();

    //소인수 분해
    fmvecarr<unsigned int>* PrimeFactorization();
    ibi abs();
    ibi pow(ibi& A);
    ibi sqrt_approximate(ibi& A, unsigned int operation_times);
    ibi tetration(ibi& A);
    static ibi factorial(ibi& A);
    ibi dimenplus(ibi& X, ibi& dim, ibi& ordermap);

    lcstr& ToString(int base_num = 10);
};

class ibr{
    public:
    bool isPositive = true;
    bool islocal = false;
    ibi numerator;
    ibi denominator;

    static bool befirst;
    static ibr one;

    static ibr bestPI;
    static ibi pi_oper_time;

    static ibr best_e;
    static ibi e_oper_time;

    ibr();
    ibr(ibr& ref);
    ~ibr();

    ibr(int num, int den);

    void Init(bool local);

    void operator=(ibi& ref);

    //fraction
    //약분
    void clean();

    bool operator>(ibr& A);
    bool operator<(ibr& A);
    bool operator==(ibr& A);
    bool operator!=(ibr& A);
    bool operator>=(ibr& A);
    bool operator<=(ibr& A);
    ibr operator+(ibr& A);
    ibr operator-(ibr& A);
    ibr operator*(ibr& A);
    ibr operator/(ibr& A);
    ibr floor_function();
    ibr operator%(ibr& A);
    ibr exp_approximate(ibr& A, ibi& operation_times);
    static ibr gamma_approximate(ibr& A, ibi& operation_times);
    static ibr nCr(ibr& N, ibr& R, ibi& operation_times);
    static ibr nHr(ibr& N, ibr& R, ibi& operation_times);
    static ibr nPr(ibr& N, ibr& R, ibi& operation_times);
    static ibr ln_approximate(ibr& X, ibi& operation_times);
    static ibr getPI_approximate(ibi& operation_times);
    static ibr get_e_approximate(ibi& operation_times);
    static ibr sin_approximate(ibr& X, ibi& getPI_operation_times, ibi& tayler_operation_times);
    static ibr cos_approximate(ibr& X, ibi& getPI_operation_times, ibi& tayler_operation_times);
    static ibr tan_approximate(ibr& X, ibi& getPI_operation_times, ibi& tayler_operation_times);
};
