#include <math.h>
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
