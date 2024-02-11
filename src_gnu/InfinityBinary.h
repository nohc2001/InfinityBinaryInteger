#ifndef INF_BIN_INT
#define INF_BIN_INT
#include <math.h>
#include "arr_expend.h"
#include "Utill_FreeMemory.h"
using namespace freemem;

typedef unsigned int v4ui __attribute__ ((vector_size (16)));

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

#define IBI_INIT DeltaObj* ibi::prime_all = nullptr; ibi ibi::max_primeMul = ibi(); ibi ibi::max_primecount = ibi();

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
        integer_data.Init(ref_size+2, integer_data.islocal);
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

ibi& ibi::operator+(const ibi &A) const
{
    if(*this == ibi(0) && A == ibi(0)){
        return ibi::add_absolute(*this, A);
    }

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

ibi& ibi::operator*(const ibi &A) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = ibi(0);
    ibi *thismulibi = new ibi[integer_data.up];
    for (int i = 0; i < integer_data.up; ++i)
    {
        fm->_tempPushLayer();
        thismulibi[i].Init(true);
        thismulibi[i].integer_data.push_back(0);
        unsigned int uii = integer_data[i];
        ibi *mulibi = new ibi[A.integer_data.up];
        for (int k = 0; k < A.integer_data.up; ++k)
        {
            fm->_tempPushLayer();
            mulibi[k].Init(true);
            mulibi[k] = mul_32(uii, A.integer_data[k]);
            mulibi[k] = mulibi[k] << k;
            //wcout << "AxB=" << uii << "x" << A.integer_data[k] << "=" << mulibi[k].dataString()->c_str() << endl;
            thismulibi[i] = thismulibi[i] + mulibi[k];
            fm->_tempPopLayer();
        }
        delete[] mulibi;
        thismulibi[i] = thismulibi[i] << i;
        r = r + thismulibi[i];
        //wcout << "TM["<< i <<"] : " << thismulibi[i].dataString()->c_str() << endl;
        //wcout << "r : " << r.dataString()->c_str() << endl;
        fm->_tempPopLayer();
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

ibi& ibi::operator%(const ibi &A) const
{
    CreateDataFM(ibi, r);
    fm->_tempPushLayer();
    r = ibi(0);
    r = *this - (*this / A) * A;
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

lcstr* ibi::ToString(bool showpos) const
{
    lcstr* r = (lcstr*)fm->_tempNew(sizeof(lcstr));
    r->NULLState();
    r->Init(8, false);

    //based 10.
    fm->_tempPushLayer();

    ibi present_value; present_value.Init(false); present_value = ibi(*this);
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

    ibi resultv; resultv.Init(false); resultv = ibi(0);
    while(present_value != ibi(0)){
        fm->_tempPushLayer();
        resultv = present_value % ibi(10);
        char addc = '0' + resultv.integer_data[0];
        r->push_back(addc);
        present_value = present_value / ibi(10);
        fm->_tempPopLayer();
    }

    fm->_tempPopLayer();

    int len = r->size();
    int dlen = (len>>1);
    int i = 0;
    if(showpos) {
        i = 1;
        dlen = (len+1>>1);
    }
    else{
        len-=1;
    }
    
    for(;i<dlen;++i){
        char c = r->at(i);
        r->at(i) = r->at(len-i);
        r->at(len-i) = c;
    }

    if(showpos && r->size() == 1){
        r->push_back('0');
    }

    if(r->size() == 0){
        r->push_back('0');
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
            //str->push_back(L' ');
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