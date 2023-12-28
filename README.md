# InfinityBinaryInteger
InfinityBinaryInteger is Special Utility of express numbers correctly and no "error like floating point".

ibi is integer class<br />
ibr is rational number class<br />
expr is math expression with ibr and operation(operation, function..).<br />
irr is real number that contain expr<br />
irc is complex number class that contain two irr.<br />
equa is equation. it can have roots.<br />
function is math function.<br />
Set is Set<br />
Axiom is Custom axiomatic system of Math. it can make Many Theorms in that axiom.<br />

they are developed for making correct math reserch program.

## IBI

### ibi integer provide follow operations<br />
void operator=(const ibi& ref);<br />
bool cmp(const ibi& A, bool left_big, bool include_same) const;<br />
bool operator>(const ibi& A) const;<br />
bool operator>=(const ibi& A) const;<br />
bool operator<(const ibi& A) const;<br />
bool operator<=(const ibi& A) const;<br />
bool operator==(const ibi& A) const;<br />
bool operator!=(const ibi& A) const;<br />
static void carry(ibi* num, int carryloc);<br />
static void carry_under(ibi* num, int carryloc);<br />
static ibi& add_absolute(const ibi& A, const ibi& B);<br />
static ibi& sub_absolute(const ibi& A, const ibi& B);<br />
ibi& operator+(const ibi& A) const;<br />
ibi& operator-(const ibi& A) const;<br />
ibi& operator<<(const int& n) const;<br />
ibi& operator>>(const int& n) const;<br />
static ibi& mul_32(unsigned int A, unsigned int B);<br />
ibi& operator*(const ibi& A) const;<br />
static ibi& div_32(const ibi& A, unsigned int divn);<br />
ibi& operator/(const ibi& A) const;<br />
ibi& operator%(const ibi& A) const; <br />
bool isint(int a) const;<br />
static void prime_data_init();<br />
static void make_new_prime();<br />
static ibi& prime_delta(const ibi& prime_num);<br />
static ibi& prime(const ibi& count);<br />
fmvecarr<unsigned int>* PrimeFactorization();<br />
ibi& abs() const;<br />
ibi& pow(const ibi& A) const;<br />
ibi& sqrt_approximate(const ibi& A, unsigned int operation_times) const;<br />
ibi& tetration(const ibi& A) const;<br />
static ibi& factorial(const ibi& A);<br />
ibi& dimenplus(const ibi& X, const ibi& dim, const ibi& ordermap) const;<br />
lcstr& ToString(int base_num) const;<br />
lwstr* dataString() const; <br />

### ibi expression:<br />
1. 256 based(1byte based expression of number)<br />
> 0~63 number in circle range (원숫자 영역)<br />
○①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮<br />
⑯⑰⑱⑲⑳㉑㉒㉓㉔㉕㉖㉗㉘㉙㉚㉛<br />
㉜㉝㉞㉟㊱㊲㊳㊴㊵㊶㊷㊸㊹㊺㊻㊼<br />
⒪⑴⑵⑶⑷⑸⑹⑺⑻⑼⑽⑾⑿⒀⒁⒂<br />
읽는법 : 원1(one1), 괄1(gural1)<br />

>64 ~ 127 chinese character range (한자 영역)<br />
日㏠㏡㏢㏣㏤㏥㏦㏧㏨㏩㏪㏫㏬㏭㏮<br />
㏯㏰㏱㏲㏳㏴㏵㏶㏷㏸㏹㏺㏻㏼㏽㏾<br />
㍘㍙㍚㍛㍜㍝㍞㍟㍠㍡㍢㍣㍤㍥㍦㍧<br />
零一二三四五六七八九十土王玉罕丑<br />
읽는법 : 일1(il1) 다1(da1) 한1(han1)<br />

>128 ~ 211 Hexagram (I Ching) range (주역 64궤 영역)<br />
䷀䷪䷍䷡䷈䷄䷙䷊䷉䷹䷥䷵䷼䷻䷨䷒<br />
䷌䷰䷝䷶䷤䷾䷕䷣䷘䷐䷔䷲䷩䷂䷚䷗<br />
䷫䷛䷱䷟䷸䷯䷑䷭䷅䷮䷿䷧䷺䷜䷃䷆<br />
䷠䷞䷷䷽䷴䷦䷳䷎䷋䷬䷢䷏䷓䷇䷖䷁<br />
읽는법 : 주1(ju1)<br />

>212 ~ 255 Geometry Range<br />
※⒈⒉⒊⒋⒌⒍⒎⒏⒐⒑⒒⒓⒔⒕⒖<br />
▴▵▸▹►▻▶▷𝍠𝍡𝍢𝍣𝍤𝍥𝍦𝍧𝍨<br />
□▒▥▨▦▩▣■◇◈◆ⓞ◎◔◐◑◕<br />
●❶❷❸❹❺❻❼❽❾❿⓫⓬⓭⓮⓯<br />
읽는법 : 점1(jum1) 삼1(sam1) 탑1(top1) 사1(sa1) 마1(ma1) 호1(ho1) 온1(own1)<br />

읽기 예시 (number reading example) <br />
ex> [+㍙䷛⒋□㊳⓯㏲䷉㉔㉖㍟㉜]<br />
플러스 다1, 주33, 점4, 사1, 원38, 온15, 일19, 주8, 원24, 원26, 다7, 원32<br />
plus da1, ju33, jum4, sa1, one38, own15, il19, ju8, one24, one26, da7, one32<br />

## IBR

### ibr rational number provide follow operations
void clean();<br />
bool operator>(const ibr& A) const;<br />
bool operator<(const ibr& A) const;<br />
bool operator==(const ibr& A) const;<br />
bool operator!=(const ibr& A) const;<br />
bool operator>=(const ibr& A) const;<br />
bool operator<=(const ibr& A) const;<br />
ibr& operator+(const ibr& A) const;<br />
ibr& operator-(const ibr& A) const;<br />
ibr& operator*(const ibr& A) const;<br />
ibr& operator/(const ibr& A) const;<br />
ibr& floor_function() const;<br />
ibr& operator%(const ibr& A) const;<br />
ibr& exp_approximate(const ibr& A, const ibi& operation_times) const;<br />
static ibr& gamma_approximate(const ibr& A, const ibi& operation_times);<br />
static ibr& nCr(const ibr& N, const ibr& R, const ibi& operation_times);<br />
static ibr& nHr(const ibr& N, const ibr& R, const ibi& operation_times);<br />
static ibr& nPr(const ibr& N, const ibr& R, const ibi& operation_times);<br />
static ibr& ln_approximate(const ibr& X, const ibi& operation_times);<br />
static ibr& getPI_approximate(const ibi& operation_times);<br />
static ibr& get_e_approximate(const ibi& operation_times);<br />
static ibr& sin_approximate(const ibr& X, const ibi& getPI_operation_times, const ibi& tayler_operation_times);<br />
static ibr& cos_approximate(const ibr& X, const ibi& getPI_operation_times, const ibi& tayler_operation_times);<br />
static ibr& tan_approximate(const ibr& X, const ibi& getPI_operation_times, const ibi& tayler_operation_times);<br />

## expr

The expr class uses the expr symbol: <br />
### "ꭢ"<br />
as a character representing itself.<br />

This character contains four characters, e, x, p, and r, respectively.<br />
This symbol is used to distinguish it from a basic function when representing a function or variable for a sentence.<br />

### the structure of expr

By default, the expr is saved as an array of expr_segment instances that are the underlying elements that make up the sentence.<br />

expr = array<expr_segment><br />
expr_segment = { ꭢsegtype(enum), union{ꭢoper, ꭢvar, ꭢconst}}<br />

At this time, the expr_segment can have three forms: operator, variable, and constant.<br />

ꭢoper = {
    expr_oper_type type; // type of operation
    unsigned int parameter_num; // number of parameters
    int* func = nullptr; // actual function
};

The operation comes first, and then the variable or constant comes out as many as the parameter number of the operation.<br />
If you encounter an operation while obtaining the parameters of the operation, process the newly discovered operation and insert it into the parameter.<br />
ex><br />
expr array data = <br />
[ꭢA, a, b, ꭢB, c, d, e, ꭢC, ꭢD, f, g, h, i]<br />
=> ꭢA(a, b, ꭢB(c, d), e, ꭢC(ꭢD(f), g, h), i)<br />

There can be many types of expr functions, <br />
such as the conjunction function "_", <br />
the repetition function "ꭢRepeat", <br />
and the condition function "ꭢIf". <br />
The expr can also contain variables, allowing other external expr to enter their place.<br />

But what really matters is the sentence constant.<br />
It can fit most of the mathematical expressions that we are familiar with.<br />
Just sentence functions and variables are used to compute the expressions and computations that the sentence constant represents.<br />

expr constant is also familliar with expr.<br />
expr_constant = { expr_constant_type type;<br />
    union{<br />
        ibr* constant_rational_num;<br />
        iboperator* constant_operator;<br />
        ibvariable* constant_variable;<br />
    };<br />
};<br />

And way of interpret of data is also same with expr.<br />
ex><br />
expr_const = [+, 10, -, 2, 3]<br />
=> [+ [10, - [2, 3]]]<br />

There are additional features given to sentences to make them more useful and familiar.<br />
It's about the commutative_property of mathematics, <br />
The parameters of a certain operation are [] to be exchanged, <br />
You'll be tied to a () that can't be exchanged.<br />
ex><br />
f(2, [3, 4]) == f(2, [4, 3])<br />

In Addition,<br />
If parameter_num == -1, there is no limit to the number of parameters, and all parameters have the commutative_property.<br />
If parameter_num == -2, there is no limit to the number of parameters, and all parameters do not have a commutative_property.<br />

ex><br />
when param_num == -1<br />
f[a, b, c, d, e] == f[e, d, c, b, a] == ...<br />

when param_num == -2<br />
f(a, b, c, d, e) != f(b, a, c, d, e)<br />

A function having only two parameters may be expressed as follows by a user's definition.<br />
ex><br />
^(a, b) == a ^ b<br />