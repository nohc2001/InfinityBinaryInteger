# InfinityBinaryInteger
InfinityBinaryInteger is Special Utility of express numbers correctly and no "error like floating point".

ibi is integer class<br />
ibr is rational number class<br />
expr is math expression with ibr and operation(operation, function..).<br />
irr is real number that contain expr<br />
irc is complex number class that contain two irr.<br />
equa is equation. it can have roots.
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
