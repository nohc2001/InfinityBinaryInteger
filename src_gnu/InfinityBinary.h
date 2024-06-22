#ifndef INF_BIN_INT
#define INF_BIN_INT
#include <math.h>
#include <complex>
#include "arr_expend.h"
#include "Utill_FreeMemory.h"
using namespace freemem;

typedef std::complex<double> Complex;

typedef struct FFTSwapPair{
    unsigned int index0;
    unsigned int index1;

    FFTSwapPair(){}
    FFTSwapPair(int i0, int i1){
        index0 = i0;
        index1 = i1;
    }
    ~FFTSwapPair(){}
}; // siz : 8byte

typedef struct FFTOperPair{
    Complex w; // 16
    unsigned int t_index; // 4
    unsigned int u_index; // 4

    FFTOperPair(){
    }
    FFTOperPair(Complex pw, unsigned int ti, unsigned int ui){
        w = pw;
        t_index = ti;
        u_index = ui;
    }
    ~FFTOperPair(){}
}; // siz : 24byte

typedef unsigned int v4ui __attribute__ ((vector_size (16)));
typedef unsigned int v8ui __attribute__ ((vector_size (32)));
typedef float v8uf __attribute__ ((vector_size (32)));
typedef double v4ud __attribute__ ((vector_size (32)));

constexpr wchar_t bytebased[16][17] = {
    {L'○', L'①' ,L'②' ,L'③' ,L'④' ,L'⑤' ,L'⑥' ,L'⑦' ,L'⑧' ,L'⑨' ,L'⑩' ,L'⑪' ,L'⑫' ,L'⑬' ,L'⑭' ,L'⑮'},
    {L'⑯', L'⑰', L'⑱', L'⑲', L'⑳', L'㉑', L'㉒', L'㉓', L'㉔', L'㉕', L'㉖', L'㉗', L'㉘', L'㉙', L'㉚', L'㉛'},
    {L'㉜', L'㉝', L'㉞', L'㉟', L'㊱', L'㊲', L'㊳', L'㊴', L'㊵', L'㊶', L'㊷', L'㊸', L'㊹', L'㊺', L'㊻', L'㊼'},
    {L'⒪', L'⑴', L'⑵', L'⑶', L'⑷', L'⑸', L'⑹', L'⑺', L'⑻', L'⑼', L'⑽', L'⑾', L'⑿', L'⒀', L'⒁', L'⒂'},
    {L'日', L'㏠', L'㏡', L'㏢', L'㏣', L'㏤', L'㏥', L'㏦', L'㏧', L'㏨', L'㏩', L'㏪', L'㏫', L'㏬', L'㏭', L'㏮'},
    {L'㏯', L'㏰', L'㏱', L'㏲', L'㏳', L'㏴', L'㏵', L'㏶', L'㏷', L'㏸', L'㏹', L'㏺', L'㏻', L'㏼', L'㏽', L'㏾'},
    {L'㍘', L'㍙', L'㍚', L'㍛', L'㍜', L'㍝', L'㍞', L'㍟', L'㍠', L'㍡', L'㍢', L'㍣', L'㍤', L'㍥', L'㍦', L'㍧'},
    {L'零', L'一', L'二', L'三', L'四', L'五', L'六', L'七', L'八', L'九', L'十', L'土', L'王', L'玉', L'罕', L'丑'},
    {L'䷀', L'䷪', L'䷍', L'䷡', L'䷈', L'䷄', L'䷙', L'䷊', L'䷉', L'䷹', L'䷥', L'䷵', L'䷼', L'䷻', L'䷨', L'䷒'},
    {L'䷌', L'䷰', L'䷝', L'䷶', L'䷤', L'䷾', L'䷕', L'䷣', L'䷘', L'䷐', L'䷔', L'䷲', L'䷩', L'䷂', L'䷚', L'䷗'},
    {L'䷫', L'䷛', L'䷱', L'䷟', L'䷸', L'䷯', L'䷑', L'䷭', L'䷅', L'䷮', L'䷿', L'䷧', L'䷺', L'䷜', L'䷃', L'䷆'},
    {L'䷠', L'䷞', L'䷷', L'䷽', L'䷴', L'䷦', L'䷳', L'䷎', L'䷋', L'䷬', L'䷢', L'䷏', L'䷓', L'䷇', L'䷖', L'䷁'},
    {L'※', L'⒈', L'⒉', L'⒊', L'⒋', L'⒌', L'⒍', L'⒎', L'⒏', L'⒐', L'⒑', L'⒒', L'⒓', L'⒔', L'⒕', L'⒖'},
    {L'▴', L'▵', L'▸', L'▹', L'►', L'▻', L'▶', L'▷', L'𝍠', L'𝍡', L'𝍢', L'𝍣', L'𝍤', L'𝍥', L'𝍦', L'𝍧', L'𝍨'},
    {L'□', L'▒', L'▥', L'▨', L'▦', L'▩', L'▣', L'■', L'◇', L'◈', L'◆', L'◎', L'◔', L'◐', L'◑', L'◕'},
    {L'●', L'❶', L'❷', L'❸', L'❹', L'❺', L'❻', L'❼', L'❽', L'❾', L'❿', L'⓫', L'⓬', L'⓭', L'⓮', L'⓯'}
};

constexpr wchar_t expr_symbol = L'ꭢ';

struct uint_wstr{
    wchar_t str[5] = {};
};

uint_wstr Get256BasedExpr(unsigned int num) {
    unsigned int n = num;
    uint_wstr r;
    int i = n % 256;
    r.str[3] = bytebased[i/16][i%16];
    n = n >> 8;
    i = n % 256;
    r.str[2] = bytebased[i/16][i%16];
    n = n >> 8;
    i = n % 256;
    r.str[1] = bytebased[i/16][i%16];
    n = n >> 8;
    i = n % 256;
    r.str[0] = bytebased[i/16][i%16];
    r.str[4] = 0;
    return r;
}

inline bool XOR(bool a, bool b){
    return a ? !b : b;
}

typedef enum class deltakind{
    delta = 0,
    arr = 1
};

class ibi;

struct DeltaObj{
    deltakind mod;
    int* Size; // sum of all arr delta
    int* len; // length of all arr
    int* data;
    DeltaObj* Parent = nullptr;
    // mod == delta -> data = ibi
    // mod == arr -> data = ArrGraph<ibi, DeltaObj>

    void push(const ibi& end, DeltaObj* obj);
    void Compile();
    DeltaObj* fx(const ibi& index);
    DeltaObj* flip();
    DeltaObj* Cut(const ibi& cutline);
    void connectHole(const ibi& loc);
    DeltaObj* RangeCopy();

    DeltaObj(void* delta);
    DeltaObj(void* min, void* max);
};


#define IBI_INIT DeltaObj* ibi::prime_all = nullptr; \
    ibi ibi::max_primeMul = ibi(); \
    ibi ibi::max_primecount = ibi(); \
    fmDynamicArr<FFTOperPair>* ibi::fftoper = nullptr;\
    fmDynamicArr<FFTSwapPair>* ibi::fftswap = nullptr;\
    ibi ibi::mod;\
    ibi ibi::w;

class ibi{
    public:
    bool isPositive = true;
    bool islocal = true;
    fmvecarr<unsigned int> integer_data;

    //static vecarr<ibi*> prime_numbers;
    //계획은 fmvecarr이 아닌 ArrGraph긴함.
    static DeltaObj* prime_all; // 모든 소수 데이터
    static ibi max_primeMul; // 1 부터 max_primecount 번째 소수 까지의 곱
    static ibi max_primecount; // 가용할 수 있는 가장 큰 소수의 번호
    static fmDynamicArr<FFTOperPair>* fftoper;
    static fmDynamicArr<FFTSwapPair>* fftswap;
    static void StaticInit();
    static ibi w;
    static ibi mod;

    ibi();
    ibi(const ibi& ref);
    ibi(int num);
    ibi(bool isp, unsigned int* data, unsigned int size);
    ~ibi();

    void clean();
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
    static ibi& add_absolute_simd(const ibi& A, const ibi& B);
    static ibi& sub_absolute_simd(const ibi& A, const ibi& B);
    ibi& operator+(const ibi& A) const;
    ibi& operator-(const ibi& A) const;
    ibi& operator<<(const int& n) const;
    ibi& operator>>(const int& n) const;
    ibi& bitShiftL(const int& n) const;
    ibi& bitShiftR(const int& n) const;

    static ibi& mul_32(unsigned int A, unsigned int B);
    ibi& operator*(const ibi& A) const;

    ibi& BottomFFTMUL_2uint(unsigned int A[2], unsigned int B[2]);
    ibi& FFTMUL(const ibi& A) const;

    ibi& operator/(const ibi& A) const;
    ibi& operator%(const ibi& A) const;
    ibi& On_Percent(const ibi &A) const;

    ibi& O_N_DIV(const ibi& A) const;

    bool isint(int a) const;
    static void prime_data_init();
    static void make_new_prime(); // prime level update
    static ibi& prime_delta(const ibi& prime_num); // prime to next delta
    static ibi& prime(const ibi& count); // count to count number of prime

    //소인수 분해
    fmvecarr<unsigned int>* PrimeFactorization();
    ibi& abs() const;
    ibi& pow(const ibi& A) const;
    ibi& sqrt_approximate(const ibi& A, unsigned int operation_times) const;
    ibi& tetration(const ibi& A) const;
    static ibi& factorial(const ibi& A);
    ibi& dimenplus(const ibi& X, const ibi& dim, const ibi& ordermap) const;

    lcstr* ToString(bool showpos = true) const;
    lwstr* dataString() const; // data origin(pow(2, 32) based expression of number)

    static ibi& NTT_power_mod(ibi& a, ibi& b);
    static ibi* NTT(ibi* A, unsigned int n, bool inv);
    static ibi* NTT_multiply(ibi* a, ibi* b, unsigned int n);
};

struct range_prime
{
    ibi end;
    DeltaObj* value;
};

class ArrGraph_prime
{
public:
    fmvecarr<range_prime> *ranges;
    ibi* minx = nullptr;
    ibi* maxx = nullptr;
    ibi* margin = nullptr;
    bool islocal = false;
    bool isdebug = true;
    fmvecarr<VP> graph;

    ArrGraph_prime()
    {
    }
    virtual ~ArrGraph_prime()
    {
        if (islocal)
        {
            if (fm->bAlloc(reinterpret_cast<byte8 *>(ranges),
                           sizeof(fmvecarr<range_prime>)))
            {
                ranges->release();
                fm->_Delete((byte8 *)ranges, sizeof(fmvecarr<range_prime>));
                ranges = nullptr;
            }

            graph.release();
            graph.NULLState();
        }
    }

    ArrGraph_prime *Init(const ibi& min, const ibi& max)
    {
        minx = (ibi*)fm->_New(sizeof(ibi), true);
        minx->Init(false);
        *minx = min;
        maxx = (ibi*)fm->_New(sizeof(ibi), true);
        maxx->Init(false);
        *maxx = max;
        margin = (ibi*)fm->_New(sizeof(ibi), true);
        margin->Init(false);
        *margin = ibi(0);
        ranges = (fmvecarr<range_prime> *)fm->_New(sizeof(fmvecarr<range_prime>), true);
        ranges->NULLState();
        ranges->Init(2, false, true);
        islocal = false;
        return this;
    }

    range_prime Range(const ibi& end, DeltaObj* value)
    {
        range_prime r;
        r.end.Init(false);
        r.end = end;
        r.value = value;
        return r;
    }

    void push_range(range_prime r)
    {
        if (*minx <= r.end && r.end <= *maxx)
        {
            ranges->push_back(r);
        }
    }

    void Compile()
    {
        fm->_tempPushLayer();
        if (ranges->size() > 2)
        {
            ibi d;
            d.Init(false);
            d = *maxx - *minx;

            ibi div;
            div.Init(false);
            div = ibi(ranges->size());

            ibi f;
            f.Init(false);
            f = d / div + ibi(1);

            ibi average_length;
            average_length.Init(false);
            average_length = f;

            *margin = average_length;
            graph.NULLState();
            graph.Init(ranges->size(), false, true);
            graph.up = ranges->size();
            
            ibi start;
            start.Init(false);
            start = *minx;

            ibi end;
            end.Init(false);
            end = start;

            for (int i = 0; i < graph.up; ++i)
            {
                fm->_tempPushLayer();
                end = start + average_length;
                if (end > *maxx)
                    end = *maxx;
                
                ibi rstart;
                rstart.Init(false);
                rstart = *minx;

                for (int k = 0; k < ranges->up; ++k)
                {
                    fm->_tempPushLayer();

                    ibi rend;
                    rend.Init(false);
                    rend = ranges->at(k).end;

                    if (rstart <= start && end <= rend)
                    {
                        // num
                        graph[i].mod = 0;
                        graph[i].ptr = reinterpret_cast<int *>(&ranges->at(k).value);
                        break;
                    }
                    else if (start <= rend && rend <= end)
                    {
                        // graph
                        ArrGraph_prime *newgraph =
                            (ArrGraph_prime *)fm->_New(sizeof(ArrGraph_prime), true);
                        newgraph->Init(start, end);
                        newgraph->push_range(ranges->at(k));
                        range_prime *r = &ranges->at(k + 1);
                        while (r->end <= end)
                        {
                            newgraph->push_range(*r);
                            ++k;
                            if (k >= ranges->size())
                            {
                                break;
                            }
                            r = &ranges->at(k + 1);
                        }
                        // input last range
                        range_prime lastr;
                        lastr = *r;
                        lastr.end = *newgraph->maxx;
                        newgraph->push_range(lastr);
                        newgraph->Compile();
                        graph[i].ptr = reinterpret_cast<int *>(newgraph);
                        graph[i].mod = 1;
                        break;
                    }
                    fm->_tempPopLayer();
                }
                start = end;
                fm->_tempPopLayer();
            }
        }
        else if (ranges->size() == 2)
        {
            graph.NULLState();
            graph.Init(2, false, true);
            ibi center; 
            center.Init(false);
            center = ranges->at(0).end;
            ibi start; start.Init(false); start = *minx;
            ibi end; end.Init(false); end = *maxx - ibi(1);
            if (*maxx - center > center - start)
            {
                *minx = ibi(2) * center + ibi(1) - end;
            }
            else
            {
                *maxx = ibi(2) * center + ibi(1) - start;
            }
            *margin = (*maxx - *minx) / ibi(ranges->size());
            VP vp0;
            vp0.mod = 0;
            vp0.ptr = reinterpret_cast<int *>(&ranges->at(0).value);
            graph.push_back(vp0);
            vp0.ptr = reinterpret_cast<int *>(&ranges->at(1).value);
            graph.push_back(vp0);
        }
        fm->_tempPopLayer();
    }

    DeltaObj* fx(const ibi& x)
    {
        static constexpr void *jumpptr[2] = {&&ISVALUE, &&ISGRAPH};
        ArrGraph_prime *ag = this;
        fmvecarr<VP> *g = &graph;
        VP vp;
        ibi f; f.Init(false); f = ibi(0);
        int index = 0;

    GET_START:
        f = x - *ag->minx;
        f = f / *ag->margin;
        index = (int)f.integer_data[0];
        vp = (*g)[index];
        goto *jumpptr[vp.mod];

    ISGRAPH:
        ag = reinterpret_cast<ArrGraph_prime *>(vp.ptr);
        g = &ag->graph;
        goto GET_START;

    ISVALUE:
        return reinterpret_cast<DeltaObj*>(vp.ptr);
    }

    void print_state()
    {
        cout << "arrgraph" << endl;
        cout << "minx : " << minx << endl;
        cout << "maxx : " << maxx << endl;
        cout << "capacity : " << graph.size() << endl;
        cout << "margin : " << margin << endl;
        for (int i = 0; i < graph.size(); ++i)
        {
            if (graph[i].mod == 0)
            {
                cout << "index : " << i << "] = value : " << *reinterpret_cast<DeltaObj* *>(graph[i].ptr) << endl;
            }
            else
            {
                cout << "index : " << i << "] = ptr : " << endl;
                reinterpret_cast<ArrGraph_prime *>(graph[i].ptr)->print_state();
                cout << endl;
            }
        }
    }
};

DeltaObj::DeltaObj(void* delta){
    mod = deltakind::delta;
    data = (int*)fm->_New(sizeof(ibi), true);
    ibi* n = reinterpret_cast<ibi*>(data);
    n->Init(false);
    *n = *reinterpret_cast<ibi*>(delta);
    Size = (int*)fm->_New(sizeof(ibi), true);
    ibi* s = reinterpret_cast<ibi*>(Size);
    s->Init(false);
    *s = ibi(0);

    len = (int*)fm->_New(sizeof(ibi), true);
    ibi* l = reinterpret_cast<ibi*>(len);
    l->Init(false);
    *l = ibi(1);
}

DeltaObj::DeltaObj(void* min, void* max){
    ibi* ibimin = reinterpret_cast<ibi*>(min);
    ibi* ibimax = reinterpret_cast<ibi*>(max);
    mod = deltakind::arr;
    data = (int*)fm->_New(sizeof(ArrGraph<ibi, DeltaObj*>), true);
    ArrGraph<ibi, DeltaObj*>* arr = reinterpret_cast<ArrGraph<ibi, DeltaObj*>*>(data);
    arr->Init(*ibimin, *ibimax, fm);
    Size = (int*)fm->_New(sizeof(ibi), true);
    ibi* s = reinterpret_cast<ibi*>(Size);
    s->Init(false);
    *s = ibi(0);

    len = (int*)fm->_New(sizeof(ibi), true);
    ibi* l = reinterpret_cast<ibi*>(len);
    l->Init(false);
    *l = ibi(0);
}

void DeltaObj::push(const ibi& end, DeltaObj* obj){
    if(mod == deltakind::arr){
        reinterpret_cast<ArrGraph_prime*>(data)->push_range(reinterpret_cast<ArrGraph_prime*>(data)->Range(end, obj));
        if(obj->mod == deltakind::arr){
            *reinterpret_cast<ibi*>(Size) = *reinterpret_cast<ibi*>(Size) + *reinterpret_cast<ibi*>(obj->Size);
            *reinterpret_cast<ibi*>(len) = *reinterpret_cast<ibi*>(len) + *reinterpret_cast<ibi*>(obj->len);
            obj->Parent = this;
        }
        else{
            *reinterpret_cast<ibi*>(Size) = *reinterpret_cast<ibi*>(Size) + *reinterpret_cast<ibi*>(obj->data);
            *reinterpret_cast<ibi*>(len) = *reinterpret_cast<ibi*>(len) + ibi(1);
            obj->Parent = this;
        }
    }
}

void DeltaObj::Compile(){
    if(mod == deltakind::arr){
        reinterpret_cast<ArrGraph_prime*>(data)->Compile();
    }
}

DeltaObj* DeltaObj::fx(const ibi& index){
    if(mod == deltakind::arr){
        reinterpret_cast<ArrGraph_prime*>(data)->fx(index);
    }
    else return nullptr;
}

DeltaObj* DeltaObj::flip(){
    if(mod == deltakind::arr){
        DeltaObj* newDeltaObj = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
        ArrGraph_prime* agp = reinterpret_cast<ArrGraph_prime*>(data);
        ibi* minx = (ibi*)fm->_New(sizeof(ibi), true); minx->Init(false); *minx = *agp->minx;
        ibi* maxx = (ibi*)fm->_New(sizeof(ibi), true); maxx->Init(false); *maxx = *agp->maxx;
        *newDeltaObj = DeltaObj((void*)minx, (void*)maxx);
        //newagp->push_range(range_prime())
        ibi savemax; savemax.Init(false); savemax = *maxx;
        for(int i = agp->ranges->size() - 1;i>=0;--i){
            range_prime v;
            v.value = agp->ranges->at(i).value;
            v.end = savemax;
            newDeltaObj->push(v.end, v.value);
            savemax = *maxx - agp->ranges->at(i).end;
        }
        newDeltaObj->Compile();
        return newDeltaObj;
    }
    else{
        return this;
    }
}

DeltaObj* DeltaObj::Cut(const ibi& cutline){
    ArrGraph_prime* agp = reinterpret_cast<ArrGraph_prime*>(data);
    ibi* minx = (ibi*)fm->_New(sizeof(ibi), true); minx->Init(false); *minx = *agp->minx;
    ibi* maxx = (ibi*)fm->_New(sizeof(ibi), true); maxx->Init(false); *maxx = *agp->maxx;
    
    if(cutline < *minx || *maxx < cutline){
        return nullptr;
    }
    
    DeltaObj* newDeltaObj = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    *newDeltaObj = DeltaObj((void*)minx, (void*)maxx);
    
    int i;
    for(i=0;(i<agp->ranges->size() && agp->ranges->at(i).end < cutline);++i){
        range_prime v;
        v.value = agp->ranges->at(i).value;
        v.end = agp->ranges->at(i).end;
        newDeltaObj->push(v.end, v.value);
    }

    DeltaObj* delta_obj = agp->ranges->at(i).value->Cut(cutline);
    if(delta_obj != nullptr){
        newDeltaObj->push(cutline, delta_obj);
    } 
    newDeltaObj->Compile();
    return newDeltaObj;
}

DeltaObj* DeltaObj::RangeCopy(){
    if(this->mod == deltakind::delta){
        return nullptr;
    }
    ArrGraph_prime* lparr = reinterpret_cast<ArrGraph_prime*>(this->data);
    DeltaObj* new_deltaObj = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    *new_deltaObj = DeltaObj(lparr->minx, lparr->maxx);
    for(int i=0;i<lparr->ranges->size();++i){
        range_prime v = lparr->ranges->at(i);
        new_deltaObj->push(v.end, v.value);
    }
    new_deltaObj->Parent = this->Parent;
    return new_deltaObj;
}

void DeltaObj::connectHole(const ibi& loc){
    constexpr void* labels[2] = {&&IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_ARR, &&IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_DELTA};
    ArrGraph_prime* parr = reinterpret_cast<ArrGraph_prime*>(data);
    DeltaObj* lastlast_deltaObj = this;
    DeltaObj* last_deltaObj = this;
    ibi *k = reinterpret_cast<ibi*>(this->len);
    *k = *k - ibi(1);
    DeltaObj* deltaobj = parr->fx(loc);
    k = reinterpret_cast<ibi*>(deltaobj->len);
    *k = *k - ibi(1);
    goto *labels[(unsigned int)deltaobj->mod];

IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_ARR:
    parr = reinterpret_cast<ArrGraph_prime*>(deltaobj->data);
    lastlast_deltaObj = last_deltaObj;
    last_deltaObj = deltaobj;
    deltaobj = parr->fx(loc);
    k = reinterpret_cast<ibi*>(deltaobj->len);
    *k = *k - ibi(1);
    goto *labels[(unsigned int)deltaobj->mod];

IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_DELTA:
    /*
    1. deltaobj의 상대적 위치가 0이 아닌 최소부모를 찾는다.
    2. 그 부모로 부터 arr이 아닌 delta가 될때까지 내려간다.
    3. 마지막 arr을 새로운 arr로 대체한다. (그 위 모든 부모까지.)
    */

    //arr하나가 바뀌면, 그 모든 부모가 다 새로 만들어져야 함. (트리형식이여서 어짜피 데이터드는건 같음. 생각보다 별로 안든다.)
    //parent가 nullptr인 deltaobj로 도달하면, 더이상 안바꿔도 된다.

    // objerase 위치의 항목을 삭제하는 코드가 새로운 코드에 적응을 못해서 지워짐.
    // 추가 필요.
    //추가로 arr항목의 range 개수가 0이면 그 항목을 없애는 코드도 추가하자.

    DeltaObj* parent_dobj = lastlast_deltaObj;
    int obj_erase = loc.integer_data[0];
    if(obj_erase > 0){
        ArrGraph_prime* lparr = reinterpret_cast<ArrGraph_prime*>(last_deltaObj->data);
        DeltaObj* new_last_deltaObj = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
        *new_last_deltaObj = DeltaObj(lparr->minx, lparr->maxx);
        for(int i=0;i<lparr->ranges->size();++i){
            range_prime v = lparr->ranges->at(i);
            if(v.value == deltaobj){
                obj_erase = i;
            }
            new_last_deltaObj->push(v.end, v.value);
        }

        ArrGraph_prime* newlparr = reinterpret_cast<ArrGraph_prime*>(new_last_deltaObj->data);

        ibi* destibi = reinterpret_cast<ibi*>(newlparr->ranges->at(obj_erase-1).value->data);
        *destibi = *destibi + *reinterpret_cast<ibi*>(newlparr->ranges->at(obj_erase).value->data);

        DeltaObj* pastPtr = last_deltaObj;
        DeltaObj* pastDelta = new_last_deltaObj;
        DeltaObj* pastDelta_Parent = new_last_deltaObj->Parent;
        DeltaObj* origin_Parent = pastPtr->Parent;
        while(origin_Parent->Parent != nullptr){
            pastDelta_Parent = origin_Parent->RangeCopy();
            ArrGraph_prime* pparent_arr = reinterpret_cast<ArrGraph_prime*>(pastDelta_Parent->data);
            int i = 0;
            for(i = 0; i<pparent_arr->ranges->size();++i){
                if(pparent_arr->ranges->at(i).value == pastPtr){
                    pastDelta->Compile();
                    pparent_arr->ranges->at(i).value = pastDelta;
                    break;
                }
            }
            
            pastPtr = origin_Parent;
            pastDelta = pastDelta_Parent;
            origin_Parent = pastPtr->Parent;
        }

        ArrGraph_prime* origin_arr = reinterpret_cast<ArrGraph_prime*>(origin_Parent->data);
        int i = 0;
        for(i = 0; i<origin_arr->ranges->size();++i){
            if(origin_arr->ranges->at(i).value == pastPtr){
                pastDelta->Compile();
                origin_arr->ranges->at(i).value = pastDelta;
                break;
            }
        }
    }
    else{
        //ibi* parentArrIn0 = parent_dobj
        DeltaObj* present_dobj = last_deltaObj;
        while(obj_erase == 0){
            ArrGraph_prime* parent_arr = reinterpret_cast<ArrGraph_prime*>(parent_dobj->data);
            int k=0;
            for(k=0;k<parent_arr->ranges->size();++k){
                if(parent_arr->ranges->at(k).value == present_dobj){
                    break;
                }
            }
            obj_erase = k;
            present_dobj = parent_dobj;
            parent_dobj = parent_dobj->Parent;
        }

        while(present_dobj->mod == deltakind::arr){
            ArrGraph_prime* present_arr = reinterpret_cast<ArrGraph_prime*>(parent_dobj->data);
            parent_dobj = present_dobj;
            present_dobj = reinterpret_cast<DeltaObj*>(present_arr->ranges->last().value);
        }

        ibi* newnum = (ibi*)fm->_New(sizeof(ibi), true);
        newnum->Init(false);
        *newnum = *reinterpret_cast<ibi*>(present_dobj->data);  /* + *reinterpret_cast<ibi*>(newlparr->ranges->at(0).value->data); */ 
        DeltaObj* newDelta = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
        *newDelta = DeltaObj((void*)newnum);
        DeltaObj* newParent_dobj = parent_dobj->RangeCopy();
        newParent_dobj->Parent = parent_dobj->Parent;
        ArrGraph_prime* nparent_arr = reinterpret_cast<ArrGraph_prime*>(newParent_dobj->data);
        nparent_arr->ranges->last().value = newDelta;
        nparent_arr->ranges->last().end = nparent_arr->ranges->last().end; /* + *reinterpret_cast<ibi*>(newlparr->ranges->at(0).value->data);
*/
        ArrGraph_prime* pparent_arr = reinterpret_cast<ArrGraph_prime*>(parent_dobj->Parent->data);
        DeltaObj* pastPtr = pparent_arr->ranges->last().value;
        DeltaObj* pastDelta = newParent_dobj;
        DeltaObj* pastDelta_Parent = newParent_dobj->Parent;
        DeltaObj* origin_Parent = pastPtr->Parent;
        while(origin_Parent->Parent != nullptr){
            pastDelta_Parent = origin_Parent->RangeCopy();
            pparent_arr = reinterpret_cast<ArrGraph_prime*>(pastDelta_Parent->data);
            int i = 0;
            for(i = 0; i<pparent_arr->ranges->size();++i){
                if(pparent_arr->ranges->at(i).value == pastPtr){
                    pastDelta->Compile();
                    pparent_arr->ranges->at(i).value = pastDelta;
                    break;
                }
            }
            
            pastPtr = origin_Parent;
            pastDelta = pastDelta_Parent;
            origin_Parent = pastPtr->Parent;
        }

        ArrGraph_prime* origin_arr = reinterpret_cast<ArrGraph_prime*>(origin_Parent->data);
        int i = 0;
        for(i = 0; i<origin_arr->ranges->size();++i){
            if(origin_arr->ranges->at(i).value == pastPtr){
                pastDelta->Compile();
                origin_arr->ranges->at(i).value = pastDelta;
                break;
            }
        }
    }
}

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

    lcstr* ToString(bool showpos = true) const;
};

enum class expr_oper_type{
    EOT_Connect = 0,
    EOT_Repeat = 1,
    EOT_If = 2,
    EOT_Custom = 3,
    EOT_UnKnown = 4
};

class expr_operator{
    public:
    expr_oper_type type;
    unsigned int parameter_num;
    //fmvecarr<fmvecarr<unsigned int>*> commutative_property;
    int* func = nullptr;
};

class expr_variable{
};

enum class iboperation_type{
    IBOT_CustomFunction = 0,
    
    IBOT_Plus = 1,
    IBOT_Minus = 2,
    IBOT_Multiply = 3,
    IBOT_Division = 4,
    IBOT_FloorFunction = 5,
    IBOT_Extra = 6,
    IBOT_Exponetial = 7,
    IBOT_Gamma = 8,
    IBOT_nCr = 9,
    IBOT_nHr = 10,
    IBOT_nPr = 11,
    IBOT_NatureLogarithm = 12,
    IBOT_Sin = 13,
    IBOT_Cos = 14,
    IBOT_Tan = 15,

    IBOT_SigmaSum,
    IBOT_PiMultiply,
    IBOT_Limit,
    IBOT_Derivative,
    IBOT_Integral
};

class iboperator{
    public:
    iboperation_type type;
    unsigned int parameter_num;
    fmvecarr<fmvecarr<unsigned int>*> commutative_property;
    int* func = nullptr;
};

class ibvariable{
    public:
    lcstr name;
};

enum class expr_constant_type{
    ECT_Parameter = 0,
    ECT_Operation = 1,
    ECT_Variable = 2,
    ECT_Unknown = 3
};

class expr_constant{
    public:
    expr_constant_type type;
    union{
        ibr* constant_rational_num;
        iboperator* constant_operator;
        ibvariable* constant_variable;
    };
};

enum class expr_segment_type{
    EST_expr_oper = 0,
    EST_expr_var = 1,
    EST_expr_const = 2,
    EST_UnKnown = 3
};

struct expr_segment{
    expr_segment_type type;
    union{
        expr_operator* oper;
        expr_variable* var;
        expr_constant* _const;
    };
};

class expr{
    public:
    fmvecarr<expr_segment> data;

    expr();
    ~expr();


};

#define CreateDataFM(type, name) type& name = *(type*)fm->_tempNew(sizeof(type)); name.Init(false);
#define ricast(type, value) reinterpret_cast<type>(value);

bool ibr::befirst = false;
ibr ibr::bestPI;
ibi ibr::pi_oper_time;
ibr ibr::best_e;
ibi ibr::e_oper_time;

void ibi::StaticInit(){
    ibi::fftoper = (fmDynamicArr<FFTOperPair>*)fm->_tempNew(sizeof(fmDynamicArr<FFTOperPair>));
    ibi::fftoper->NULLState();
    ibi::fftoper->Init(8, false); // 16byte objs, 256 capacity

    ibi::fftswap = (fmDynamicArr<FFTSwapPair>*)fm->_tempNew(sizeof(fmDynamicArr<FFTSwapPair>));
    ibi::fftswap->NULLState();
    ibi::fftswap->Init(9, false); // 8byte objs, 512 capacity

    ibi::w.Init(false);
    ibi::w = ibi(3);
    ibi::mod.Init(false);
    ibi::mod = ibi(998244353);
}

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

void ibi::clean(){
    for(int i=integer_data.size()-1;i >=0;--i){
        if(integer_data[i] == 0){
            integer_data.up -= 1;
        }
        else{
            break;
        }
    }
}

void ibi::Init(bool plocal)
{
    integer_data.NULLState();
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
    while (ref_size > integer_data.maxsize)
        integer_data.Init(ref_size+2, integer_data.islocal, false, integer_data.fmlayer);
    integer_data.up = ref_size;

    for (int i = 0; i < ref_size; ++i)
        integer_data[i] = ref.integer_data[i];
    
    for(int i = ref_size-1;i>=1;--i){
        if(integer_data[i] == 0) integer_data.up -= 1;
        else break;
    }
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
    if (isPositive != A.isPositive){
        if((A.integer_data.size() == 1 && A.integer_data[0] == 0) && (this->integer_data.size() == 1 && this->integer_data[0] == 0)){
            return true;
        }
        return false;
    }
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
    {
        if ((A.integer_data.up == 1 && this->integer_data.up == 1) && (A.integer_data[0] == 0 && this->integer_data[0] == 0)) {
            return false;
        }
        return true;
    }
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
    //wcout << "dbg carry num : " << num->dataString()->c_str() << endl;
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
    // no optim
    
    r = B;
    unsigned int maxsiz = (A.integer_data.size() > B.integer_data.size()) ? A.integer_data.size() : B.integer_data.size();

    for (int i = 0; i < maxsiz; ++i)
    {
        unsigned int Ax = (A.integer_data.up > i) ? A.integer_data[i] : 0;
        unsigned int Tx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
        unsigned int max = (Ax > Tx) ? Ax : Tx;
        Tx += Ax;
        if (Tx < max)
        {
            carry(&r, i + 1);
        }
        
        if(r.integer_data.up <= i){
            r.integer_data.push_back(Tx);
        }
        else{
            r.integer_data[i] = Tx;
        }
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

ibi& ibi::add_absolute_simd(const ibi &A, const ibi &B)
{
	CreateDataFM(ibi, r);
    
    fm->_tempPushLayer();

    ibi Atemp; Atemp.Init(false); Atemp = A;
    ibi Btemp; Btemp.Init(false); Btemp = B;
    if(A > B){
        r = A;
        for(int i=B.integer_data.size(); i < A.integer_data.size();++i){
            Btemp.integer_data.push_back(0);
        }
    }
    else{
        r = B;
        for(int i=A.integer_data.size(); i < B.integer_data.size();++i){
            Atemp.integer_data.push_back(0);
        }
    }
    // no optim
    /*
    r = B;
    unsigned int maxsiz = (A.integer_data.size() > B.integer_data.size()) ? A.integer_data.size() : B.integer_data.size();

    for (int i = 0; i < maxsiz; ++i)
    {
        unsigned int Ax = (A.integer_data.up > i) ? A.integer_data[i] : 0;
        unsigned int Tx = (r.integer_data.up > i) ? r.integer_data[i] : 0;
        unsigned int max = (Ax > Tx) ? Ax : Tx;
        Tx += Ax;
        if (Tx < max)
        {
            carry(&r, i + 1);
        }
        
        if(r.integer_data.up <= i){
            r.integer_data.push_back(Tx);
        }
        else{
            r.integer_data[i] = Tx;
        }
    }
    
    */

    //simd optimized
    register unsigned int temp = (A.integer_data.size() > B.integer_data.size()) ? B.integer_data.size() : A.integer_data.size();
    unsigned int addSiz = 1;
    addSiz = temp;
    unsigned int addSiz_v8 = addSiz >> 3;
    unsigned int addSiz_v88 = addSiz >> 6;
    unsigned int* APBarr = (unsigned int*)&r.integer_data[0]; // max
    unsigned int* Marr = (unsigned int*)fm->_tempNew(addSiz << 2); // max
    unsigned int* Carr = (unsigned int*)fm->_tempNew((addSiz+1) << 2); // carry
    Carr[0] = 0;
    if(addSiz_v88){
        register v8ui Ar, Br, Ar2, Br2;
        register v8ui Ar3, Br3, Ar4, Br4;
        constexpr v8ui ActiveVec = {1, 1, 1, 1, 1, 1, 1, 1};
        constexpr v8ui OffVec = {0, 0, 0, 0, 0, 0, 0, 0};
        v8ui* APBptr = (v8ui*)&APBarr[0];
        v8ui* Mptr = (v8ui*)&Marr[0];
        temp = (addSiz_v88<<6);
        for(uint si=0;si<temp;si+=64){
            Ar = *(v8ui*)&Atemp.integer_data[si];
            Br = *(v8ui*)&Btemp.integer_data[si];
            Ar2 = *(v8ui*)&Atemp.integer_data[si+8];
            Br2 = *(v8ui*)&Btemp.integer_data[si+8];
            Ar3 = *(v8ui*)&Atemp.integer_data[si+16];
            Br3 = *(v8ui*)&Btemp.integer_data[si+16];
            Ar4 = *(v8ui*)&Atemp.integer_data[si+24];
            Br4 = *(v8ui*)&Btemp.integer_data[si+24];
            *APBptr = Ar + Br;
            *Mptr = (Ar > Br) ? Ar : Br;
            *(APBptr+1) = Ar2 + Br2;
            *(Mptr+1) = (Ar2 > Br2) ? Ar2 : Br2;
            *(APBptr+2) = Ar3 + Br3;
            *(Mptr+2) = (Ar3 > Br3) ? Ar3 : Br3;
            *(APBptr+3) = Ar4 + Br4;
            *(Mptr+3) = (Ar4 > Br4) ? Ar4 : Br4;
            APBptr+=4;
            Mptr+=4;
            Ar = *(v8ui*)&Atemp.integer_data[si+32];
            Br = *(v8ui*)&Btemp.integer_data[si+32];
            Ar2 = *(v8ui*)&Atemp.integer_data[si+40];
            Br2 = *(v8ui*)&Btemp.integer_data[si+40];
            Ar3 = *(v8ui*)&Atemp.integer_data[si+48];
            Br3 = *(v8ui*)&Btemp.integer_data[si+48];
            Ar4 = *(v8ui*)&Atemp.integer_data[si+56];
            Br4 = *(v8ui*)&Btemp.integer_data[si+56];
            *APBptr = Ar + Br;
            *Mptr = (Ar > Br) ? Ar : Br;
            *(APBptr+1) = Ar2 + Br2;
            *(Mptr+1) = (Ar2 > Br2) ? Ar2 : Br2;
            *(APBptr+2) = Ar3 + Br3;
            *(Mptr+2) = (Ar3 > Br3) ? Ar3 : Br3;
            *(APBptr+3) = Ar4 + Br4;
            *(Mptr+3) = (Ar4 > Br4) ? Ar4 : Br4;
            APBptr+=4;
            Mptr+=4;

            *(v8ui*)&Carr[si+1] = (*(v8ui*)&Marr[si] > *(v8ui*)&APBarr[si]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+9] = (*(v8ui*)&Marr[si+8] > *(v8ui*)&APBarr[si+8]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+17] = (*(v8ui*)&Marr[si+16] > *(v8ui*)&APBarr[si+16]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+25] = (*(v8ui*)&Marr[si+24] > *(v8ui*)&APBarr[si+24]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+33] = (*(v8ui*)&Marr[si+32] > *(v8ui*)&APBarr[si+32]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+41] = (*(v8ui*)&Marr[si+40] > *(v8ui*)&APBarr[si+40]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+49] = (*(v8ui*)&Marr[si+48] > *(v8ui*)&APBarr[si+48]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+57] = (*(v8ui*)&Marr[si+56] > *(v8ui*)&APBarr[si+56]) ? ActiveVec : OffVec;
        }

        temp = addSiz_v8 << 3;
        for(uint si=(addSiz_v88 << 6);si<temp;si+=8){
            Ar = *(v8ui*)&Atemp.integer_data[si];
            Br = *(v8ui*)&Btemp.integer_data[si];
            *(v8ui*)&APBarr[si] = Ar + Br;
            *(v8ui*)&Marr[si] = (Ar > Br) ? Ar : Br;
            *(v8ui*)&Carr[si+1] = (*(v8ui*)&Marr[si] > *(v8ui*)&APBarr[si]) ? ActiveVec : OffVec;
        }

        register unsigned int uA, uB;
        for(uint i=temp;i<addSiz;++i){
            uA = Atemp.integer_data[i];
            uB = Btemp.integer_data[i];
            APBarr[i] = uA + uB;
            Marr[i] = (uA > uB) ? uA : uB;
            Carr[i+1] = (Marr[i] > APBarr[i]) ? 1 : 0;
        }

        for(uint i=0;i<addSiz;++i){
            if(Carr[i]){
                carry(&r, i);
            }
        }
        if(Carr[addSiz]){
            r.integer_data.push_back(1);
        }
    }
    else if(addSiz_v8){
        register v8ui Ar, Br;
        constexpr v8ui ActiveVec = {1, 1, 1, 1, 1, 1, 1, 1};
        constexpr v8ui OffVec = {0, 0, 0, 0, 0, 0, 0, 0};
        for(uint i=0;i<addSiz_v8;++i){
            uint si = i << 3;
            Ar = *(v8ui*)&Atemp.integer_data[si];
            Br = *(v8ui*)&Btemp.integer_data[si];
            *(v8ui*)&APBarr[si] = Ar + Br;
            *(v8ui*)&Marr[si] = (Ar > Br) ? Ar : Br;
            *(v8ui*)&Carr[si+1] = (*(v8ui*)&Marr[si] > *(v8ui*)&APBarr[si]) ? ActiveVec : OffVec;
        }

        register unsigned int uA, uB;
        for(uint i=(addSiz_v8 << 3);i<addSiz;++i){
            uA = Atemp.integer_data[i];
            uB = Btemp.integer_data[i];
            APBarr[i] = uA + uB;
            Marr[i] = (uA > uB) ? uA : uB;
            Carr[i+1] = (Marr[i] > APBarr[i]) ? 1 : 0;
        }

        for(uint i=0;i<addSiz;++i){
            if(Carr[i]){
                carry(&r, i);
            }
        }
        if(Carr[addSiz]){
            r.integer_data.push_back(1);
        }
    }
    else{
        register unsigned int uA, uB;
        for(uint i=0;i<addSiz;++i){
            uA = Atemp.integer_data[i];
            uB = Btemp.integer_data[i];
            APBarr[i] = uA + uB;
            Marr[i] = (uA > uB) ? uA : uB;
            Carr[i+1] = (Marr[i] > APBarr[i]) ? 1 : 0;
        }

        for(uint i=1;i<addSiz;++i){
            if(Carr[i]){
                carry(&r, i);
            }
        }
        if(Carr[addSiz]){
            if(r.integer_data.size() == addSiz){
                r.integer_data.push_back(1);
            }
            else{
                carry(&r, addSiz);
            }
        }
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::sub_absolute_simd(const ibi &A, const ibi &B)
{
    /*
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
    */
    
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();

    ibi MaxI; MaxI.Init(false); MaxI = A;
    ibi MinI; MinI.Init(false); MinI = B;
    MaxI.isPositive = true;
    MinI.isPositive = true;
    bool bab = MaxI > MinI;
    if(bab){
        r = A;
        MaxI = A;
        MinI = B;
    }
    else{
        r = B;
        MaxI = B;
        MinI = A;
    }
    MaxI.isPositive = true;
    MinI.isPositive = true;
    MinI.integer_data.Init(MaxI.integer_data.size(), false);
    for(int i=MinI.integer_data.size();i<MinI.integer_data.maxsize;++i){
        MinI.integer_data[i] = 0;
    }
    
    //simd optimized
    register unsigned int temp = MaxI.integer_data.size();
    unsigned int addSiz = 1;
    addSiz = temp;
    unsigned int addSiz_v8 = addSiz >> 3;
    unsigned int addSiz_v88 = addSiz >> 6;
    unsigned int* APBarr = (unsigned int*)&r.integer_data[0]; // max[i]-min[i]
    unsigned int* Carr = (unsigned int*)fm->_tempNew((addSiz+1) << 2); // carry
    Carr[0] = 0;
    if(addSiz_v88){
        register v8ui Ar, Br, Ar2, Br2;
        register v8ui Ar3, Br3, Ar4, Br4;
        constexpr v8ui ActiveVec = {1, 1, 1, 1, 1, 1, 1, 1};
        constexpr v8ui OffVec = {0, 0, 0, 0, 0, 0, 0, 0};
        v8ui* APBptr = (v8ui*)&APBarr[0];
        temp = (addSiz_v88<<6);
        for(uint si=0;si<temp;si+=64){
            Ar = *(v8ui*)&MaxI.integer_data[si];
            Br = *(v8ui*)&MinI.integer_data[si];
            Ar2 = *(v8ui*)&MaxI.integer_data[si+8];
            Br2 = *(v8ui*)&MinI.integer_data[si+8];
            Ar3 = *(v8ui*)&MaxI.integer_data[si+16];
            Br3 = *(v8ui*)&MinI.integer_data[si+16];
            Ar4 = *(v8ui*)&MaxI.integer_data[si+24];
            Br4 = *(v8ui*)&MinI.integer_data[si+24];
            *APBptr = Ar - Br;
            *(APBptr+1) = Ar2 - Br2;
            *(APBptr+2) = Ar3 - Br3;
            *(APBptr+3) = Ar4 - Br4;
            APBptr+=4;

            *(v8ui*)&Carr[si+1] = (*(v8ui*)&Ar[si] < *(v8ui*)&Br[si]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+9] = (*(v8ui*)&Ar2[si+8] < *(v8ui*)&Br2[si+8]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+17] = (*(v8ui*)&Ar3[si+16] < *(v8ui*)&Br3[si+16]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+25] = (*(v8ui*)&Ar4[si+24] < *(v8ui*)&Br4[si+24]) ? ActiveVec : OffVec;

            Ar = *(v8ui*)&MaxI.integer_data[si+32];
            Br = *(v8ui*)&MinI.integer_data[si+32];
            Ar2 = *(v8ui*)&MaxI.integer_data[si+40];
            Br2 = *(v8ui*)&MinI.integer_data[si+40];
            Ar3 = *(v8ui*)&MaxI.integer_data[si+48];
            Br3 = *(v8ui*)&MinI.integer_data[si+48];
            Ar4 = *(v8ui*)&MaxI.integer_data[si+56];
            Br4 = *(v8ui*)&MinI.integer_data[si+56];
            *APBptr = Ar - Br;
            *(APBptr+1) = Ar2 - Br2;
            *(APBptr+2) = Ar3 - Br3;
            *(APBptr+3) = Ar4 - Br4;
            APBptr+=4;

            *(v8ui*)&Carr[si+33] = (*(v8ui*)&Ar[si+32] < *(v8ui*)&Br[si+32]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+41] = (*(v8ui*)&Ar2[si+40] < *(v8ui*)&Br2[si+40]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+49] = (*(v8ui*)&Ar3[si+48] < *(v8ui*)&Br3[si+48]) ? ActiveVec : OffVec;
            *(v8ui*)&Carr[si+57] = (*(v8ui*)&Ar4[si+56] < *(v8ui*)&Br4[si+56]) ? ActiveVec : OffVec;
        }

        temp = addSiz_v8 << 3;
        for(uint si=(addSiz_v88 << 6);si<temp;si+=8){
            Ar = *(v8ui*)&MaxI.integer_data[si];
            Br = *(v8ui*)&MinI.integer_data[si];
            *(v8ui*)&APBarr[si] = Ar - Br;
            *(v8ui*)&Carr[si+1] = (*(v8ui*)&Ar[si] < *(v8ui*)&Br[si]) ? ActiveVec : OffVec;
        }

        register unsigned int uA, uB;
        for(uint i=temp;i<addSiz;++i){
            uA = MaxI.integer_data[i];
            uB = MinI.integer_data[i];
            APBarr[i] = uA - uB;
            Carr[i+1] = (uA < uB) ? 1 : 0;
        }

        r.clean();

        for(uint i=1;i<addSiz+1;++i){
            if(Carr[i]){
                carry_under(&r, i);
            }
        }
    }
    else if(addSiz_v8){
        register v8ui Ar, Br;
        constexpr v8ui ActiveVec = {1, 1, 1, 1, 1, 1, 1, 1};
        constexpr v8ui OffVec = {0, 0, 0, 0, 0, 0, 0, 0};
        for(uint i=0;i<addSiz_v8;++i){
            uint si = i << 3;
            Ar = *(v8ui*)&MaxI.integer_data[si];
            Br = *(v8ui*)&MinI.integer_data[si];
            *(v8ui*)&APBarr[si] = Ar - Br;
            *(v8ui*)&Carr[si+1] = (Ar < Br) ? ActiveVec : OffVec;
        }

        register unsigned int uA, uB;
        for(uint i=(addSiz_v8 << 3);i<addSiz;++i){
            uA = MaxI.integer_data[i];
            uB = MinI.integer_data[i];
            APBarr[i] = uA - uB;
            Carr[i+1] = (uA < uB) ? 1 : 0;
        }

        r.clean();

        for(uint i=1;i<addSiz+1;++i){
            if(Carr[i]){
                carry_under(&r, i);
            }
        }
    }
    else{
        register unsigned int uA, uB;
        for(uint i=0;i<addSiz;++i){
            uA = MaxI.integer_data[i];
            uB = MinI.integer_data[i];
            APBarr[i] = uA - uB;
            Carr[i+1] = (uA < uB) ? 1 : 0;
        }

        r.clean();

        for(uint i=1;i<addSiz+1;++i){
            if(Carr[i]){
                carry_under(&r, i);
            }
        }
    }

    if(bab){
        r.isPositive = A.isPositive;
    }
    else{
        r.isPositive = !B.isPositive;
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator+(const ibi &A) const
{
    if(*this == ibi(0) && A == ibi(0)){
        return ibi::add_absolute_simd(*this, A);
    }

    if (isPositive == A.isPositive)
    {
        return ibi::add_absolute_simd(*this, A);
    }
    else
    {
        return ibi::sub_absolute_simd(*this, A);
    }
}

ibi& ibi::operator-(const ibi &A) const
{
    if (isPositive == A.isPositive)
    {
        return ibi::sub_absolute_simd(*this, A);
    }
    else
    {
        return ibi::add_absolute_simd(*this, A);
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

ibi& ibi::bitShiftL(const int& n) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    int sh = n >> 5;
    int rn = n - (sh << 5);
    r = *this << sh;
    ibi temp; temp.Init(false); temp = *this;
    temp.integer_data.push_back(0);
    r.integer_data.push_back(0);
    for (int i = sh; i < r.integer_data.size(); ++i)
    {
        int ti = i - sh;
        unsigned int upfrag = temp.integer_data[ti] << rn;
        unsigned int downfrag = 0;
        if(ti != 0){
            downfrag = temp.integer_data[ti-1] >> (32-rn);
        }

        r.integer_data[i] = upfrag + downfrag;
    }

    for(int i = r.integer_data.size()-1;i>=1;--i){
        if(r.integer_data[i] == 0){
            r.integer_data.pop_back();
        }
        else break;
    }
    fm->_tempPopLayer();
    return r;
}
ibi& ibi::bitShiftR(const int& n) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    int sh = n >> 5;
    int rn = n - (sh << 5);
    r = *this >> sh;
    ibi temp; temp.Init(false); temp = *this;
    temp.integer_data.push_back(0);
    r.integer_data.push_back(0);

    for (int i = sh; i < r.integer_data.size(); ++i)
    {
        int ti = i - sh;
        unsigned int upfrag = temp.integer_data[ti] >> rn;
        unsigned int downfrag = 0;
        if(ti < r.integer_data.size()-1){
            downfrag = temp.integer_data[ti+1] << (32-rn);
        }

        r.integer_data[i] = upfrag + downfrag;
    }

    for(int i = r.integer_data.size()-1;i>=1;--i){
        if(r.integer_data[i] == 0){
            r.integer_data.pop_back();
        }
        else break;
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
    operand[0].Init(false);
    operand[1].Init(false);
    operand[2].Init(false);
    operand[0] = ibi(0);
    operand[1] = ibi(0);
    operand[2] = ibi(0);
    operand[0].integer_data[0] = R0;
    if(R3 != 0){
        operand[0].integer_data.push_back(R3);
    }
    operand[1].integer_data[0] = R10;
    if(R11 != 0){
        operand[1].integer_data.push_back(R11);
    }
    operand[2].integer_data[0] = R20;
    if(R21 != 0){
        operand[2].integer_data.push_back(R21);
    }

    r = operand[0].operator+(operand[1]);
    r = r + operand[2];

    fm->_tempPopLayer();
    return r;
}

inline unsigned int reverseBits(unsigned int num, int bits)
{
	unsigned int reverse_num = 0;
	for (int i = 0; i < bits; i++)
	{
		if ((num & (1 << i)))
			reverse_num |= 1 << ((bits - 1) - i);
	}
	return reverse_num;
}

void fft_addStamp(unsigned int dataSiz)
{
    constexpr double PI = 3.14159265358979323846;
    if(ibi::fftoper->get_bottom_array(256) != nullptr){
        cout << "fftoper_corr : " << ibi::fftoper->get_bottom_array(256)->maxsiz_pow2 << endl;
    }
    ibi::fftswap->clear();
    //ibi::fftswap->Init(9, false);
    ibi::fftoper->clear();
    //ibi::fftoper->Init(8, false);
    if(ibi::fftoper->get_bottom_array(256) != nullptr){
        cout << "fftoper_corr : " << ibi::fftoper->get_bottom_array(256)->maxsiz_pow2 << endl;
    }

    const size_t N = dataSiz;
    const size_t M = log2(N);

    // bit-reversed permutation
    for (size_t i = 0; i < N; i++)
    {
        size_t j = reverseBits(i, M);
        if (i < j){
            ibi::fftswap->push_back(FFTSwapPair(i, j));
        }
    }

    // butterfly updates
    for (size_t s = 1; s <= M; s++)
    {
        size_t m = 1 << s;
        Complex wm = std::polar(1.0, -2.0 * PI / (double)m);

        for (size_t k = 0; k < N; k += m)
        {
            Complex w = 1;
            for (size_t j = 0; j < m / 2; j++)
            {
                ibi::fftoper->push_back(FFTOperPair(w, k + j + m / 2, k + j));
                w *= wm;
            }
        }
    }
}

void fft_useStamp(fmDynamicArr<Complex>& x){
    Complex temp;
    for(int i=0;i<ibi::fftswap->size();++i){
        FFTSwapPair& sp = ibi::fftswap->at(i);
        unsigned int index0 = sp.index0;
        unsigned int index1 = sp.index1;
        temp = x[index0];
        x[index0] = x[index1];
        x[index1] = temp;
    }

    for(int i=0;i<ibi::fftoper->size();++i){
        FFTOperPair& op = ibi::fftoper->at(i);
        Complex w = op.w;
        unsigned int ti = op.t_index;
        unsigned int ui = op.u_index;
        Complex t = w * x[ti];
        Complex u = x[ui];
        x[ui] = u + t;
        x[ti] = u - t;
    }
}

inline void ifft_useStamp(fmDynamicArr<Complex> &x)
{
    constexpr unsigned int signbit = 1 << 31;
    constexpr v8ui conjB = {0, 0, signbit, 0, 0, 0, signbit, 0};
    // conjugate the complex numbers
    //x = x.apply(std::conj);
    //constexpr v8uf conjV = {1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f};
    //혹은 비트만 바꿔서 부호 바꾸기
    unsigned int s = x.size();
    if (s >= 16)
    {
        for (uint si = 0; si < s; si += 16)
        {
            v8ui *so0 = reinterpret_cast<v8ui *>(&x.at(si));
            v8ui *so1 = reinterpret_cast<v8ui *>(&x.at(si + 2));
            v8ui *so2 = reinterpret_cast<v8ui *>(&x.at(si + 4));
            v8ui *so3 = reinterpret_cast<v8ui *>(&x.at(si + 6));
            v8ui *so4 = reinterpret_cast<v8ui *>(&x.at(si + 8));
            v8ui *so5 = reinterpret_cast<v8ui *>(&x.at(si + 10));
            v8ui *so6 = reinterpret_cast<v8ui *>(&x.at(si + 12));
            v8ui *so7 = reinterpret_cast<v8ui *>(&x.at(si + 14));
            *so0 = *so0 ^ conjB;
            *so1 = *so1 ^ conjB;
            *so2 = *so2 ^ conjB;
            *so3 = *so3 ^ conjB;
            *so4 = *so4 ^ conjB;
            *so5 = *so5 ^ conjB;
            *so6 = *so6 ^ conjB;
            *so7 = *so7 ^ conjB;
        }

        // forward fft
        fft_useStamp(x);

        // conjugate the complex numbers again
        // x = x.apply(std::conj);
        for (uint si = 0; si < s; si += 16)
        {
            v8ui *so0 = reinterpret_cast<v8ui *>(&x.at(si));
            v8ui *so1 = reinterpret_cast<v8ui *>(&x.at(si + 2));
            v8ui *so2 = reinterpret_cast<v8ui *>(&x.at(si + 4));
            v8ui *so3 = reinterpret_cast<v8ui *>(&x.at(si + 6));
            v8ui *so4 = reinterpret_cast<v8ui *>(&x.at(si + 8));
            v8ui *so5 = reinterpret_cast<v8ui *>(&x.at(si + 10));
            v8ui *so6 = reinterpret_cast<v8ui *>(&x.at(si + 12));
            v8ui *so7 = reinterpret_cast<v8ui *>(&x.at(si + 14));
            *so0 = *so0 ^ conjB;
            *so1 = *so1 ^ conjB;
            *so2 = *so2 ^ conjB;
            *so3 = *so3 ^ conjB;
            *so4 = *so4 ^ conjB;
            *so5 = *so5 ^ conjB;
            *so6 = *so6 ^ conjB;
            *so7 = *so7 ^ conjB;
        }

        // scale the numbers
        double divf = 1.0f / (double)x.size();
        v4ud divV = {divf, divf, divf, divf};
        // x /= x.size();
        for (uint si = 0; si < s; si += 16)
        {
            v4ud *so0 = reinterpret_cast<v4ud *>(&x.at(si));
            v4ud *so1 = reinterpret_cast<v4ud *>(&x.at(si + 2));
            v4ud *so2 = reinterpret_cast<v4ud *>(&x.at(si + 4));
            v4ud *so3 = reinterpret_cast<v4ud *>(&x.at(si + 6));
            v4ud *so4 = reinterpret_cast<v4ud *>(&x.at(si + 8));
            v4ud *so5 = reinterpret_cast<v4ud *>(&x.at(si + 10));
            v4ud *so6 = reinterpret_cast<v4ud *>(&x.at(si + 12));
            v4ud *so7 = reinterpret_cast<v4ud *>(&x.at(si + 14));
            *so0 = *so0 * divV;
            *so1 = *so1 * divV;
            *so2 = *so2 * divV;
            *so3 = *so3 * divV;
            *so4 = *so4 * divV;
            *so5 = *so5 * divV;
            *so6 = *so6 * divV;
            *so7 = *so7 * divV;
        }
    }
    else{
        for(uint si = 0; si < s; si += 1){
            x.at(si).imag(-1.0 * x.at(si).imag());
        }

        // forward fft
        fft_useStamp(x);

        for(uint si = 0; si < s; si += 1){
            x.at(si).imag(-1.0 * x.at(si).imag());
        }

        double divf = 1.0 / (double)x.size();
        for(uint si = 0; si < s; si += 1){
            x.at(si) = divf * x.at(si);
        }
    }
}

inline ibi &ibi::BottomFFTMUL_2uint(unsigned int A[2], unsigned int B[2])
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = ibi(0);
    int64_t temp[4] = {A[0]*B[0]-A[1]*B[1], A[0]*B[1]+A[1]*B[0], 0, 0};
    int64_t cr[4] = {(A[0]+A[1])*(B[0]+B[1]),temp[0], (A[0]-A[1])*(B[0]-B[1]), temp[0]};
    int64_t ci[4] = {0, temp[1], 0, -temp[1]};

    fm->_tempPopLayer();
    return r;
}

ibi &ibi::FFTMUL(const ibi &A) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = ibi(0);
    unsigned int dSiz = (this->integer_data.size() > A.integer_data.size()) ? this->integer_data.size() : A.integer_data.size();
    unsigned int Siz = dSiz;
    
    unsigned int log2 = 0;
    while(Siz > (1 << log2)){
        ++log2;
    }
    dSiz = 1 << log2;
    Siz = dSiz;
    dSiz = dSiz << 1;
    unsigned int qSiz = dSiz << 1;

    fmDynamicArr<Complex> TCArr;
    TCArr.NULLState();
    TCArr.Init(8, false, qSiz);

    fmDynamicArr<Complex> ACArr;
    ACArr.NULLState();
    ACArr.Init(8, false, qSiz);

    r.integer_data.Init(dSiz, false);
    fmDynamicArr<unsigned int> rdata;
    rdata.NULLState();
    rdata.Init(9, false, qSiz);
    
    fft_addStamp(qSiz);

    for (int i = 0; i < Siz; ++i)
    {
        unsigned int di = i << 1;
        unsigned short put_temp0 = (unsigned short)integer_data[i];
        unsigned short put_temp1 = (unsigned short)(integer_data[i] >> 16);
        double d0 = (integer_data.size()-1 < i) ? 0 : (double)(put_temp0);
        TCArr[di] = Complex(d0, 0.0);
        double d1 = (integer_data.size()-1 < i) ? 0 : (double)(put_temp1);
        TCArr[di+1] = Complex(d1, 0.0);

        put_temp0 = (unsigned short)A.integer_data[i];
        put_temp1 = (unsigned short)(A.integer_data[i] >> 16);
        d0 = (A.integer_data.size()-1 < i) ? 0 : (double)(put_temp0);
        ACArr[di] = Complex(d0, 0.0);
        d1 = (A.integer_data.size()-1 < i) ? 0 : (double)(put_temp1);
        ACArr[di+1] = Complex(d1, 0.0);
    }

    for (int i = dSiz; i < qSiz; ++i)
    {
        TCArr[i] = Complex(0.0, 0.0);
        ACArr[i] = Complex(0.0, 0.0);
    }

    /*
    cout << "TCArr : " << endl;
    for(int i=0;i<qSiz;++i){
        cout << TCArr[i].real() << ", ";
    }
    cout << endl;

    cout << "ACArr : " << endl;
    for(int i=0;i<qSiz;++i){
        cout << ACArr[i].real() << ", ";
    }
    cout << endl;
    */
    
    fft_useStamp(TCArr);
    fft_useStamp(ACArr);

    /*
    cout << "TCArr : " << endl;
    for(int i=0;i<qSiz;++i){
        cout << TCArr[i].real() << ", ";
    }
    cout << endl;

    cout << "ACArr : " << endl;
    for(int i=0;i<qSiz;++i){
        cout << ACArr[i].real() << ", ";
    }
    cout << endl;
    */

    for (int i = 0; i < qSiz; ++i)
    {
        TCArr[i] = TCArr[i] * ACArr[i];
    }
    ifft_useStamp(TCArr);

    /*
    cout << "TCArr : " << endl;
    for(int i=0;i<qSiz;++i){
        cout << TCArr[i].real() << ", ";
    }
    cout << endl;
    */
    

    //cout << "rdata : " << endl;
    for (int i = 0; i < qSiz; ++i)
    {
        unsigned int c = (unsigned int)(TCArr[i].real() + 0.5);
        rdata[i] = c;
        //cout << rdata[i] << ", ";
    }
    //cout << endl;

    //cout << "return data : " << endl;
    for (unsigned int i = 0; i < qSiz; ++i)
    {
        // i/2 = index, i%2 == 0 -> just add, i%2 == 1 -> add low << 16, add to next index high >> 16
        unsigned int divi = i >> 1;
        if(i & 1){
            if(r.integer_data[divi] > r.integer_data[divi] + rdata[i] << 16){
                ibi::carry(&r, divi+1);
            }
            r.integer_data[divi] += rdata[i] << 16;
            
            if(r.integer_data[divi+1] > r.integer_data[divi+1] + rdata[i] >> 16){
                ibi::carry(&r, divi+2);
            }
            r.integer_data[divi] += rdata[i] >> 16;
        }
        else{
            if(r.integer_data[divi] > r.integer_data[divi] + rdata[i]){
                ibi::carry(&r, divi+1);
            }
            r.integer_data[divi] += rdata[i];
        }

        if(rdata[i] != 0){
            r.integer_data.up = divi+1;
        }
    }

    /*
    cout << "RESULT : " << endl;
    for(int i=0;i<r.integer_data.size();++i){
        cout << r.integer_data[i] << ", ";
    }
    cout << endl;
    */

    //TCArr.release();
    //ACArr.release();
    //rdata.release();
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::operator*(const ibi &A) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = ibi(0);
    ibi *thismulibi = (ibi*)fm->_tempNew(sizeof(ibi)*integer_data.up);
    for (int i = 0; i < integer_data.up; ++i)
    {
        fm->_tempPushLayer();
        thismulibi[i].Init(false);
        thismulibi[i] = ibi(0);
        unsigned int uii = integer_data[i];
        //ibi *mulibi = new ibi[A.integer_data.up];
        ibi *mulibi = (ibi*)fm->_tempNew(sizeof(ibi)*A.integer_data.up);
        for (int k = 0; k < A.integer_data.up; ++k)
        {
            fm->_tempPushLayer();
            mulibi[k].Init(false);
            mulibi[k] = mul_32(uii, A.integer_data[k]);
            mulibi[k] = mulibi[k] << k;
            //wcout << "AxB=" << uii << "x" << A.integer_data[k] << "=" << mulibi[k].dataString()->c_str() << endl;
            thismulibi[i] = thismulibi[i] + mulibi[k];
            fm->_tempPopLayer();
        }
        thismulibi[i] = thismulibi[i] << i;
        r = r + thismulibi[i];
        //wcout << "TM["<< i <<"] : " << thismulibi[i].dataString()->c_str() << endl;
        //wcout << "r : " << r.dataString()->c_str() << endl;
        fm->_tempPopLayer();
    }
    fm->_tempPopLayer();

    return r;
}

ibi& ibi::operator/(const ibi &A) const
{
    // this / a
    CreateDataFM(ibi, r);

    fm->_tempPushLayer();
    r = ibi(0);

    // tempV / A
    ibi tempV;
    tempV.Init(false);
    tempV = *this;

    ibi tempA;
    tempA.Init(false);
    tempA = A;

    int shift = tempA.integer_data.up;
    int vpos = 1;
    vpos = tempV.integer_data.up - shift;
    while (vpos >= 0)
    {
        fm->_tempPushLayer();
        ibi teV;
        teV.Init(false);
        teV = tempV >> vpos;

        ibi tR;

        unsigned int divva = 0;
        if(teV.integer_data.size() == tempA.integer_data.size()){
            unsigned int tA = tempA.integer_data.last();
            unsigned int tV = teV.integer_data.last();
            divva = tV / tA;
        }
        else{
            unsigned int delta = 4294967295 >> 2;
            unsigned int divp = 4294967295 >> 1;

            ibi seekI;
            seekI.Init(false);
            ibi seekK;
            seekK.Init(false);

            //humm need testing
            while(delta > 4){
                fm->_tempPushLayer();
                seekI = tempA * ibi(true, &divp, 1);
                bool saturate = true;
                if(seekI > teV){
                    divp -= delta;
                    //wcout << seekI.dataString()->c_str() << L" > " << teV.dataString()->c_str() << endl;
                }
                else{
                    divp += delta;
                    //wcout << seekI.dataString()->c_str() << L" < " << teV.dataString()->c_str() << endl;
                }
                delta = 1 + delta >> 1;
                fm->_tempPopLayer();
            }

            while(true){
                fm->_tempPushLayer();
                unsigned int divp1 = divp + 1;
                seekI = tempA * ibi(true, &divp, 1);
                seekK = tempA * ibi(true, &divp1, 1);
                if(seekI <= teV && seekK > teV){
                    //ret
                    divva = divp;
                    fm->_tempPopLayer();
                    break;
                }
                else if(teV < seekI){
                    divp -= 1;
                }
                else if(seekK <= teV){
                    divp += 1;
                }
                fm->_tempPopLayer();
            }
        }
        
        
        tR.Init(false);
        tR = ibi(true, &divva, 1);

        bool saturate = true;
        while (saturate)
        {
            fm->_tempPushLayer();
            if(teV >= tempA * tR){
                saturate = false;
            }
            else{
                tR = tR - 1;
            }
            fm->_tempPopLayer();
        }

        //wcout << L"tR : \t" << tR.dataString()->c_str() << endl;
        //wcout << L"tempV : \t" << tempV.dataString()->c_str() << endl;
        ibi temparv;
        temparv.Init(false);
        temparv = ((tempA * tR) << vpos);
        tempV = tempV - temparv;
        //wcout << L"tR*tempA : \t" << temparv.dataString()->c_str() << endl;
        for (int k = tempV.integer_data.up - 1; k >= 0; --k)
        {
            if (tempV.integer_data[k] == 0)
                tempV.integer_data.up -= 1;
            else
            {
                break;
            }
        }
        //wcout << L"post-tempV : \t" << tempV.dataString()->c_str() << endl;
        r = r + (tR << vpos);
        //wcout << L"stacking-R : \t" << r.dataString()->c_str() << endl;
        --vpos;
        fm->_tempPopLayer();
    }
    fm->_tempPopLayer();

    for (int k = r.integer_data.up - 1; k >= 1; --k)
    {
        if (r.integer_data[k] == 0)
            r.integer_data.up -= 1;
        else
        {
            break;
        }
    }
    return r;
}

ibi& ibi::O_N_DIV(const ibi& A) const
{
    // this / a
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = ibi(0);
    ibi tempT; tempT.Init(false); tempT = *this;
    tempT.isPositive = true;
    unsigned int bitSiz = tempT.integer_data.size() << 5;
    ibi tempB; tempB.Init(false); tempB = A;
    ibi tempBit; tempBit.Init(false); tempBit = ibi(1);
    tempB = tempB.bitShiftL(bitSiz-1);
    tempBit = tempBit.bitShiftL(bitSiz-1);
    tempBit.isPositive = true;
    tempB.isPositive = true;

    ibi tempSave; tempSave.Init(false); tempSave = ibi(1);
    //wcout << L"init state : " << endl;
    //wcout << L"tempT : " << tempT.dataString()->c_str() << endl;
    //wcout << L"tempB : " << tempB.dataString()->c_str() << endl;
    //wcout << L"tempBit : " << tempBit.dataString()->c_str() << endl;
    for(int i = bitSiz-1;i>=0;--i){
        //wcout << L"\nLoop : " << i << endl;
        //wcout << L"tempT : " << tempT.dataString()->c_str() << endl;
        //wcout << L"tempB : " << tempB.dataString()->c_str() << endl;
        //wcout << L"tempBit : " << tempBit.dataString()->c_str() << endl;
        if(tempT - tempB >= ibi(0)){
            tempSave = tempT - tempB;
            //wcout << L"tempSave(T-B) : " << tempSave.dataString()->c_str() << endl;
            //wcout << L"update!" << endl;
            tempT = tempSave;
            r = r + tempBit;
            //wcout << L"r : " << r.dataString()->c_str() << endl;
            //std::wcout << tempT.dataString()->c_str() << endl;
            //std::wcout << r.dataString()->c_str() << endl;
        }
        tempB = tempB.bitShiftR(1);
        tempBit = tempBit.bitShiftR(1);
    }

    //std::wcout << this->dataString()->c_str() << endl;
    //std::wcout << A.dataString()->c_str() << endl;
    //std::wcout << r.dataString()->c_str() << endl;
    fm->_tempPopLayer();
    r.isPositive = this->isPositive;
    return r;
}

ibi& ibi::operator%(const ibi &A) const
{
    CreateDataFM(ibi, r);
    r = ibi(0);
    fm->_tempPushLayer();
    if(*this > ibi(0) && *this < (((*this).O_N_DIV(A)) * A)){
        cout << "break;" << endl;
        wcout << L"this : " << this->dataString()->c_str() << endl;
        ibi temp0; temp0.Init(false);
        temp0 = (*this).O_N_DIV(A);
        wcout << L"A : " << A.dataString()->c_str() << endl;
        wcout << L"this/A : " << temp0.dataString()->c_str() << endl;
        temp0 = temp0 * A;
        wcout << L"(this/A)*A : " << temp0.dataString()->c_str() << endl;
    }
    r = *this - (((*this).O_N_DIV(A)) * A);
    if(r > A){
        cout << "break;" << endl;
        r.isPositive = true;
        r = *this - (((*this).O_N_DIV(A)) * A);
    }
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::On_Percent(const ibi &A) const
{
    CreateDataFM(ibi, r);
    r = ibi(0);
    fm->_tempPushLayer();

    ibi N;
    N.Init(false);
    N = ibi(1);
    N = N << 1;

    for(int i=0;i<integer_data.size();++i){
        ibi Ai;
        Ai.Init(false);
        Ai = ibi(integer_data[i]);

        ibi tempN; tempN.Init(false);
        tempN = 1;
        for(int k=0;k<i;++k){
            tempN = tempN * N;
            tempN = tempN % A;
        }

        r = (r + (tempN * Ai) % A) % A;
    }

    fm->_tempPopLayer();
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

void ibi::prime_data_init(){
    max_primecount.Init(false);
    max_primeMul.Init(false);
    fm->_tempPushLayer();
    max_primecount = ibi(2);
    
    ibi* minibi = (ibi*)fm->_New(sizeof(ibi), true);
    minibi->Init(false);
    *minibi = ibi(1);

    ibi* maxibi = (ibi*)fm->_New(sizeof(ibi), true);
    maxibi->Init(false);
    *maxibi = ibi(4);

    prime_all = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    *prime_all = DeltaObj(minibi, maxibi);

    ibi* delta0 = (ibi*)fm->_New(sizeof(ibi), true);
    delta0->Init(false);
    *delta0 = ibi(1);
    DeltaObj* D0 = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    *D0 = DeltaObj((void*)delta0);
    prime_all->push(ibi(1), D0);

    ibi* delta1 = (ibi*)fm->_New(sizeof(ibi), true);
    delta1->Init(false);
    *delta1 = ibi(1);
    DeltaObj* D1 = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    *D1 = DeltaObj((void*)delta1);
    prime_all->push(ibi(2), D1);

    ibi* delta2 = (ibi*)fm->_New(sizeof(ibi), true);
    delta2->Init(false);
    *delta2 = ibi(2);
    DeltaObj* D2 = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    *D2 = DeltaObj((void*)delta2);
    prime_all->push(ibi(4), D2);

    max_primeMul = ibi(6);

    fm->_tempPopLayer();
 }

void ibi::make_new_prime()
{
    DeltaObj* prevD = prime_all;
    DeltaObj* newD;
    newD = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);

    fm->_tempPushLayer();

    max_primecount = max_primecount + ibi(1);
    ibi newprime; newprime.Init(false);
    newprime = prime(max_primecount);
    max_primeMul = max_primeMul * newprime;
    ibi* one = (ibi*)fm->_New(sizeof(ibi), true);
    one->Init(false);
    *one = ibi(1);
    *newD = DeltaObj((void*)one, (void*)&max_primeMul);
    ibi stacking_size;
    stacking_size.Init(false);
    stacking_size = *reinterpret_cast<ibi*>(prevD->Size);
    ibi increse_size; increse_size.Init(false);
    increse_size = ibi(0);
    ibi index0; index0.Init(false); index0 = ibi(0);
    ibi frontmax; frontmax.Init(false); frontmax = newprime / ibi(2);

    // fill front of new Delta
    for(;index0 < frontmax;){
        fm->_tempPushLayer();
        newD->push(stacking_size * (index0 + ibi(1)), prevD);
        index0 = index0 + ibi(1);
        increse_size = increse_size + stacking_size;
        fm->_tempPopLayer();
    }
    
    // fill the center of Delta
    ibi centersize; centersize.Init(false);
    centersize = ibi(0);
    centersize = max_primeMul - (ibi(2) * increse_size);
    ibi hcs; hcs.Init(false); // half_center_size
    hcs = centersize / ibi(2);
    DeltaObj* DCut = prevD->Cut(hcs);
    newD->push(increse_size + hcs, DCut);
    DeltaObj* DCutflip = DCut->flip();
    newD->push(increse_size + centersize, DCutflip);
    increse_size = increse_size + centersize;

    // fill the back of Delta (mirror image of front Delta)
    DeltaObj* Dflip = prevD->flip();
    index0 = ibi(0);
    frontmax = frontmax - ibi(1);
    for(;index0 < frontmax;){
        fm->_tempPushLayer();
        newD->push(increse_size + stacking_size * (index0 + ibi(1)), Dflip);
        index0 = index0 + ibi(1);
        increse_size = increse_size + stacking_size;
        fm->_tempPopLayer();
    }

    // fill the last mirror of front (back) fill to max_primeMul
    DeltaObj* dobj2 = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    ibi* thePpi = (ibi*)fm->_New(sizeof(ibi), true);
    thePpi->Init(false); *thePpi = stacking_size;
    *dobj2 = DeltaObj(thePpi);
    newD->push(increse_size + stacking_size, dobj2);
    increse_size = increse_size + stacking_size;

    // push 2 in the last
    dobj2 = (DeltaObj*)fm->_New(sizeof(DeltaObj), true);
    ibi* thetwo = (ibi*)fm->_New(sizeof(ibi), true);
    thetwo->Init(false); *thetwo = ibi(2);
    *dobj2 = DeltaObj(thetwo);
    increse_size = increse_size + ibi(2);
    newD->push(increse_size, dobj2);

    //fill the holes
    ibi stacklevel; stacklevel.Init(false); stacklevel = ibi(1);
    ibi prep; prep.Init(false); prep = max_primecount;
    while(true){
        fm->_tempPushLayer();
        ibi pcount; pcount.Init(false); pcount = ibi(0);
        ibi saturate_index; saturate_index.Init(false); saturate_index = ibi(max_primecount);
        while(true){
            fm->_tempPushLayer();
            if(prime(saturate_index).pow(ibi(2)) < max_primeMul) {
                fm->_tempPopLayer();
                break;
            }
            saturate_index = saturate_index + ibi(1);
            fm->_tempPopLayer();
        }

        while(true){
            fm->_tempPushLayer();
            ibi hole; hole.Init(false); hole = ibi(0);
            ibi index1; index1.Init(false); index1 = prep;
            for(;index1 < saturate_index;){
                fm->_tempPushLayer();
                hole = prime(prep + index1).pow(stacklevel) * prime(prep + index1 + pcount);
                if(hole < max_primeMul){
                    newD->connectHole(hole);
                }
                else{
                    saturate_index = index1;
                }
                index1 = index1 + ibi(1);
                fm->_tempPopLayer();
            }
            pcount = pcount + ibi(1);
            if(saturate_index == prep){
                fm->_tempPopLayer();
                break;
            }
            fm->_tempPopLayer();
        }
        stacklevel = stacklevel + ibi(1);
        if(prime(prep).pow(stacklevel) > max_primeMul){
            fm->_tempPopLayer();
            break;
        }
        fm->_tempPopLayer();
    }
    
    fm->_tempPopLayer();

    ibi::prime_all = newD;
}

ibi& ibi::prime_delta(const ibi& prime_num){
    CreateDataFM(ibi, r);
    r = ibi(0);
    
    constexpr void* labels[2] = {&&IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_ARR, &&IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_DELTA};
    ArrGraph_prime* parr = reinterpret_cast<ArrGraph_prime*>(prime_all->data);
    DeltaObj* deltaobj = parr->fx(prime_num);
    goto *labels[(unsigned int)deltaobj->mod];

IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_ARR:
    parr = reinterpret_cast<ArrGraph_prime*>(deltaobj->data);
    deltaobj = parr->fx(prime_num);
    goto *labels[(unsigned int)deltaobj->mod];

IBI_PRIME_DELTA_FUNC_DELTAMOD_IS_DELTA:
    fm->_tempPushLayer();
    r = *reinterpret_cast<ibi*>(deltaobj->data);
    fm->_tempPopLayer();
    return r;
}

ibi& ibi::prime(const ibi& count){
    // count to prime number
    CreateDataFM(ibi, r);
    r = ibi(1);

    fm->_tempPushLayer();
    DeltaObj* dpi = prime_all;
    while(true){
        int i=0;
        ibi index; index.Init(false); index = ibi(0);
        while(index >= count){
            ArrGraph_prime* agp = reinterpret_cast<ArrGraph_prime*>(dpi->data);
            DeltaObj* agp_deltaobj = agp->ranges->at(i).value;
            ibi* len = reinterpret_cast<ibi*>(agp_deltaobj->len);
            if(index + *len < count){
                index = index + *reinterpret_cast<ibi*>(agp_deltaobj->len);
                r = r + *reinterpret_cast<ibi*>(agp_deltaobj->Size);
            }
            else{
                break;
            }
            ++i;
        }

        ArrGraph_prime* agp = reinterpret_cast<ArrGraph_prime*>(dpi->data);
        DeltaObj* agp_deltaobj = agp->ranges->at(i).value;
        if(agp_deltaobj->mod == deltakind::delta){
            break;
        }
        else{
            dpi = reinterpret_cast<DeltaObj*>(agp_deltaobj->data);
        }
    }
    fm->_tempPopLayer();

    return r;
}

// 소인수 분해
/*
fmvecarr<unsigned int> *ibi::PrimeFactorization()
{
    fmvecarr<unsigned int> *pfarr = ricast(fmvecarr<unsigned int>*, fm->_tempNew(sizeof(fmvecarr<unsigned int>)));
    pfarr->NULLState();
    pfarr->Init(8, false);

    fm->_tempPushLayer();
    ibi copy;
    copy.Init(false);
    copy = *this;
    ibi prime_index; prime_ind = 0;
    ibi::prime()
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
*/

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

    unsigned int addsiz = 32 * (A.integer_data.up-1);
    unsigned int v = (unsigned int)A.integer_data.last();
    for (int i = 0; i < 32; ++i)
    {
        v = v >> 1;
        ++addsiz;
        if (v == 0)
        {
            break;
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

lcstr *ibi::ToString(bool showpos) const
{
    lcstr *r = (lcstr *)fm->_tempNew(sizeof(lcstr));
    r->NULLState();
    r->Init(8, false);

    // based 10.
    fm->_tempPushLayer();

    ibi present_value;
    present_value.Init(false);
    present_value = ibi(*this);
    if (showpos)
    {
        if (present_value.isPositive)
        {
            r->push_back('+');
        }
        else
        {
            r->push_back('-');
        }
    }

    ibi resultv;
    resultv.Init(false);
    resultv = ibi(0);
    ibi tempv;
    tempv.Init(false);
    tempv = ibi(0);
    ibi hm;
    hm.Init(false);
    hm = ibi(1000000000);
    fmvecarr<unsigned int> numstack;
    numstack.NULLState();
    numstack.Init(8, false, false);
    if (present_value.integer_data.size() > 10)
    {
        wcout << "present_value : " << present_value.dataString()->c_str() << endl;
        int half = present_value.integer_data.size() / 2;
        ibi largeHM; largeHM.Init(false); largeHM = hm.pow(ibi(half)); // herer
        wcout << "largeHM : " << largeHM.dataString()->c_str() << endl;
        ibi Temp0; Temp0.Init(false); Temp0 = present_value.O_N_DIV(largeHM);
        wcout << "temp0 : " << Temp0.dataString()->c_str() << endl;
        ibi Temp1; Temp1.Init(false); Temp1 = Temp0.FFTMUL(largeHM);
        wcout << "temp1 : " << Temp1.dataString()->c_str() << endl;
        Temp1 = present_value - Temp1;
        wcout << "temp1 : " << Temp1.dataString()->c_str() << endl;
        lcstr* str0 = Temp0.ToString(false);
        lcstr* str1 = Temp1.ToString(false);
        
        for(int i=0;i<str0->size();++i){
            r->push_back(str0->at(i));
        }
        for(int i=0;i<str1->size();++i){
            r->push_back(str1->at(i));
        }
    }
    else
    {
        while (present_value != ibi(0))
        {
            fm->_tempPushLayer();
            // std::wcout << present_value.dataString()->c_str() << endl;
            tempv = present_value.O_N_DIV(hm);
            resultv = present_value - tempv * hm;
            present_value = tempv;
            numstack.push_back(resultv.integer_data[0]);
            // char addc = '0' + resultv.integer_data[0];
            // r->push_back(addc);
            fm->_tempPopLayer();
        }

        for (int i = numstack.size() - 1; i >= 0; --i)
        {
            string numstr = to_string(numstack.at(i));
            if (i != numstack.size() - 1)
            {
                for (int k = 0; k < 10 - numstr.size(); ++k)
                {
                    r->push_back('0');
                }
            }

            for (int k = 0; k < numstr.size(); ++k)
            {
                r->push_back(numstr.at(k));
            }
        }

        fm->_tempPopLayer();

        if (showpos && r->size() == 1)
        {
            r->push_back('0');
        }

        if (r->size() == 0)
        {
            r->push_back('0');
        }
    }
    return r;
}

lwstr* ibi::dataString() const
{
    lwstr* str = (lwstr*)fm->_tempNew(sizeof(lwstr));
    str->NULLState();
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
        //str->push_back(L'|');
        uint_wstr uintstr = Get256BasedExpr(integer_data[i]);
        for(int k=0;k<4;++k){
            str->push_back(uintstr.str[k]);
            str->push_back(L' ');
        }
    }

    str->push_back(L']');
    fm->_tempPopLayer();
    return str;
}

ibi& ibi::NTT_power_mod(ibi& a, ibi& b)
{
    CreateDataFM(ibi, ret);
    fm->_tempPushLayer();
    ret = ibi(1);

    ibi tempA;
    tempA.Init(false);
    tempA = a;

    ibi tempB;
    tempB.Init(false);
    tempB = b;

    while(tempB != ibi(0)){
        fm->_tempPushLayer();
        if (tempB.integer_data[0] & 1) {
            ret = ((tempA.On_Percent(ibi::mod)) * ret).On_Percent(ibi::mod);
        }
        tempA = ((tempA.On_Percent(ibi::mod)) * tempA).On_Percent(ibi::mod);
        tempB = tempB.bitShiftR(1);
        wcout << tempB.dataString()->c_str() << endl;
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();
    return ret;
}

ibi* ibi::NTT(ibi* A, unsigned int n, bool inv){
    ibi* nttA = (ibi*)fm->_New(sizeof(ibi)*n, true);
    for(int i=0;i<n;++i){
        nttA[i].Init(false);
        nttA[i] = A[i];
    }

    fm->_tempPushLayer();
    fmDynamicArr<unsigned int> rev;
    rev.NULLState();
    rev.Init(10, false, n);
    for(int i=0;i<n;++i){
        rev[i] = 0;
    }
    ibi temp;
    temp.Init(false);
    for(int i=0;i<n;++i){
        rev[i] = rev[i >> 1]>>1;
        if(i&1){
            rev[i] |= n >> 1;
        }
        if(i < rev[i]){
            fm->_tempPushLayer();
            temp = nttA[i];
            nttA[i] = nttA[rev[i]];
            nttA[rev[i]] = temp;
            fm->_tempPopLayer();
        }
    }
    
    ibi x;
    x.Init(false);
    x = ibi(0);
    x = NTT_power_mod(w, (mod - ibi(1)) / ibi(n));
    if(inv){
        x = NTT_power_mod(x, mod - ibi(2));
    }
    
    ibi* root = (ibi*)fm->_New(sizeof(ibi)*n, true);
    root[0] = ibi(1);
    for(int i=1;i<=n;++i){
        root[i].Init(false);
        root[i] = ibi(0);
        root[i] = ibi(root[i-1] * x).On_Percent(ibi::mod);
    }

    unsigned int i = 2;
    ibi v;
    v.Init(false);
    while(i <= n){
        unsigned int step = n / i;
        for(unsigned int j=0;j<n;j+=i){
            for(unsigned int k=0;k<(i>>1);++k){
                //ibi u = A[j|k];
                v = ((nttA[j|k|i >> 1].On_Percent(ibi::mod)) * root[step*k]).On_Percent(ibi::mod);
                nttA[j|k] = (nttA[j|k] + v).On_Percent(ibi::mod);
                nttA[j|k|i >> 1] = (nttA[j|k] - v).On_Percent(ibi::mod);
                if(nttA[j|k|i >> 1] < ibi(0)) {
                    nttA[j|k|i >> 1] = nttA[j|k|i >> 1] + ibi::mod;
                }
            }
        }
        i = i<<1;
    }

    
    if(inv){
        ibi ibin = ibi(n);
        ibi t = NTT_power_mod(ibin, mod - ibi(2));
        for(int i=0;i<n;++i){
            nttA[i] = ((nttA[i].On_Percent(ibi::mod)) * t).On_Percent(ibi::mod);
        }
    }

    fm->_tempPopLayer();

    return nttA;
}

ibi* ibi::NTT_multiply(ibi* a, ibi* b, unsigned int n){
    ibi* C = (ibi*)fm->_New(sizeof(ibi) * n, false);
    for(int i=0;i<n;++i){
        C[i].Init(false);
        C[i] = ibi(0);
    }
    fm->_tempPushLayer();

    //NTT
    ibi* A = NTT(a, n, false);
    ibi* B = NTT(b, n, false);
    
    // A*B(convolusions)
    for(int i=0;i<n;++i){
        A[i].Init(false);
        A[i] = A[i]*B[i];
    }

    for(int i=0;i<n;++i){
        A[i] = A[i].On_Percent(mod);
    }

    //INTT
    ibi* tempC = NTT(A, n, true);
    for(int i=0;i<n;++i){
        C[i] = tempC[i];
    }

    fm->_tempPopLayer();
    return C;
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
    isPositive = !XOR((num >= 0), (den >= 0));
}

void ibr::Init(bool local)
{
    islocal = local;
    isPositive = true;
    numerator.Init(local);
    numerator = ibi(0);
    denominator.Init(local);
    denominator = ibi(1);
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
    ibi A; A.Init(false); A = numerator;
    A.isPositive = true;
    ibi B; B.Init(false); B = denominator;
    B.isPositive = true;
    ibi C;
    C.Init(false);
    C = ibi(1);
    bool havefraction = false;
    while (true)
    {
        fm->_tempPushLayer();
        if (A > B)
        {
            C = A % B;
            if (C != ibi(1) && C != ibi(0))
            {
                A = C;
            }
            else if (C == ibi(0)) {
                C = B;
                havefraction = true;
                break;
            }
            else
            {
                break;
            }
        }
        else if (B > A)
        {
            C = B % A;
            if (C != ibi(1) && C != ibi(0))
            {
                B = C;
            }
            else if (C == ibi(0)) {
                C = A;
                havefraction = true;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            C = A;
            havefraction = true;
            break;
        }
        fm->_tempPopLayer();
    }

    if (havefraction)
    {
        numerator = numerator / C;
        denominator = denominator / C;
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

    r.isPositive = this->isPositive;
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

    r.isPositive = this->isPositive;
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
    r.isPositive = !XOR(this->isPositive, A.isPositive);
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
    r.isPositive = !XOR(this->isPositive, A.isPositive);
    r.numerator = this->numerator * A.denominator;
    r.denominator = this->denominator * A.numerator;
    r.clean();
    fm->_tempPopLayer();
    return r;
}

ibr& ibr::floor_function() const
{
    CreateDataFM(ibr, r);
    r = ibr(1, 1);

    fm->_tempPushLayer();

    r.isPositive = this->isPositive;
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
    r = ibr(1, 1);
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

        cout << "r : " << r.ToString(true)->c_str() << endl;
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

lcstr* ibr::ToString(bool showpos) const{
    lcstr* r = (lcstr*)fm->_tempNew(sizeof(lcstr));
    r->NULLState();
    r->Init(8, false);

    fm->_tempPushLayer();
    lcstr* numstr = numerator.ToString(false);
    lcstr* denstr = denominator.ToString(false);

    r->push_back('[');

    if(showpos){
        if(this->isPositive){
            r->push_back('+');
        }
        else{
            r->push_back('-');
        }
    }
    

    for(int i=0;i<numstr->size();++i){
        r->push_back(numstr->at(i));
    }

    r->push_back('/');

    for(int i=0;i<denstr->size();++i){
        r->push_back(denstr->at(i));
    }

    r->push_back(']');

    fm->_tempPopLayer();

    return r;
}
#endif