# Reserch of Basic Operation of Math.

## Overview
Appendix   
    [1. basic binominal operation : +<sub>n|m</sub>](#basic-binominal-operation--nm)   
    2. new Addition that copying previous operation property : <sup>u</sup>+<sub>n</sub>  
    3. Adding with Increasing Variables : <sup>dim</sup>$\sum_{k=0}^{n}$(f(k))   
    4. Integration and Differential with new Additions : <sup>dim|dx</sup>$\int_a^b$(f(x)), df(x)-<sup>dim</sup>dx   
    5. Superimposed Sigma : <sup>dim</sup>$\sum_{k1=0}^{max}$(<sup>dim</sup>$\sum_{k2=0}^{k1}$(...(<sup>dim</sup>$\sum_{km=0}^{km-1}$(f({kn})))...))   
    6. expend function composition in rational space. : f<sup>r</sup>(x)    
    7. Accurate value state prediction method when various variables are continuously influencing each other (time that don't affect each other is never exist.)   
    ETC. Additional Idea.    

## basic binominal operation : +<sub>n|m</sub>

my goal of this research is to find all effective expression property of basic binominal operation(+<sub>n|m</sub>)   
using this property, try calculate many operations and expression and equation of many hyper operations.   
.+ and × is basic operation of modern math. expending basic knowledge of addition will develop math.     
Historically, the inverse operations of these iterations of addition have had a profound effect on the number system of mathematics.    
that point is also interesting in this research.

### Property of Operation
    1. parameters
        1-1. parameters count
        1-2. parameters exchangeable
        1-3. parameters exchangeable
        1-4. identity element of a parameter
        1-5. inverse element of a parameter
    2. domain and range
        2-1. finding new number
    3. produce other operation
        3-1. inverse function
        3-2. repeating function
        3-3. copy property of operation
    4. found expression property
   

### operation nextnum(a), a'
<details><summary>aka a' in Peano's axioms</summary>

1. parameter
param count = 1      
stackable = true      
2. domain and range : natural number (positive integer)   
3. produce other operation   
repeating function : [+<sub>1</sub>](#operation-a-1-b) defined by [a + b = a_ꭢR<sup>b</sup>[']]   
</details>


### operation (a +<sub>1</sub> b)   
<details><summary>aka. a + b</summary>

1. parameter
param count = 2   
exchangeable = true   
stackable = true   
identity element = 0   
inverse element : b = 0 -<sub>1</sub> a = -a   
2. domain and range : 0 and natural number (unsigned integer)
3. produce other operation   
inverse function : [-<sub>1</sub>](#operation-a--1-b)   
repeating function : [+<sub>2</sub>](#operation-a-2-b) defined by [a +<sub>2</sub> b = ꭢR<sup>b</sup>[+ a]]   
</details>

### operation (a -<sub>1</sub> b)   
<details><summary>aka. a - b</summary>
   
1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element = 0   
inverse element : b = a   
2. domain and range : integer   
find new number : negative integer
    - produce by [B - S = -(B-S)] {B > S}
3. produce other operation   
</details>

### operation (a +<sub>2</sub> b)   
<details><summary>aka. a × b</summary>

1. parameter
param count = 2   
exchangeable = true   
stackable = true   
identity element = 1   
inverse element : b = 1 -<sub>2</sub> a = 1/a   
2. domain and range : integer
3. produce other operation   
inverse function : [-<sub>2</sub>](#operation-a--2-b)   
repeating function : [+<sub>3</sub>](#operation-a-3-b) defined by [a +<sub>2</sub> b = 1_ꭢR<sup>b</sup>[* a]]   
</details>

### operation (a -<sub>2</sub> b)   
<details><summary>aka. a ÷ b and a/b</summary>

1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element = 1   
inverse element : b = a   
2. domain and range : rational number   
find new number : rational number that exist in between n and n+1.
3. produce other operation   
</details>

### operation (a +<sub>3</sub> b)   
<details><summary>aka. a<sup>b</sup></summary>

1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element of a : b = 1   
inverse element of a : b = 0   
identity element of b : a = <sup>b</sup>√b = b<sup>1/b</sup>   
inverse element of b : a = <sup>b</sup>√<sup>b</sup>√b = b<sup>1/b<sup>2</sup></sup>   
2. domain and range : integer
3. produce other operation   
inverse function of a : [-<sub>3|0</sub>](#operation-a--30-b)   
inverse function of b : [-<sub>3|1</sub>](#operation-a--31-b)   
repeating function of a : [+<sub>4|0</sub>](#operation-a-40-b) defined by [a +<sub>4|0</sub> b = ꭢR<sup>b</sup>[(]_<sup>a</sup>√a_ꭢR<sup>b</sup>[) +<sub>3</sub> a]]   
repeating function of b : +<sub>4|1</sub> defined by [a +<sub>4|1</sub> b = ꭢR<sup>b</sup>[a +<sub>3</sub> (]_1_ꭢR<sup>b</sup>[)]
</details>

### operation (a -<sub>3|0</sub> b)   
<details><summary>aka. <sup>b</sup>√a</summary>

1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element of a : b = 1   
inverse element of a : b = countable infinity   
identity element of b : a = b +<sub>3</sub> b = b<sup>b</sup>    
inverse element of b : a = (b +<sub>3</sub> b) +<sub>3</sub> b = (b<sup>b</sup>)<sup>b</sup> = b<sup>b<sup>2</sup></sup> = b +<sub>4|0</sub> 3   
2. domain and range : complex number   
find new number : irrational number and imaginary number   
3. produce other operation   
</details>

### operation (a -<sub>3|1</sub> b)   
<details><summary>aka. log<sub>a</sub>b</summary>

1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element of a : b = a +<sub>3</sub> a = a<sup>a</sup>   
inverse element of a : b = a +<sub>3</sub> (a +<sub>3</sub> a) = a +<sub>4|1</sub> 3   
identity element of b : a = b -<sub>3|0</sub> b = b<sup>1/b</sup> = <sup>b</sup>√b   
inverse element of b : a = b -<sub>3|0</sub> (b -<sub>3|0</sub> b)   
2. domain and range : rational number   
3. produce other operation   
</details>

### operation (a +<sub>4|0</sub> b)   
<details><summary>aka. a<sup>a<sup>b</sup></sup></summary>

1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element of a : b = 0   
inverse element of a : b = log<sub>a</sub>-(countable infinity)   
identity element of b : a = b -<sub>4|0</sub> b   
inverse element of b : a = (b -<sub>4|0</sub> b) -<sub>4|0</sub> b   
2. domain and range : integer
3. produce other operation   
inverse function of a : [-<sub>4|0</sub>](#operation-a--40-b)   
inverse function of b : [-<sub>4|2</sub>]()   
repeating function of a : +<sub>5|0</sub> defined by [a +<sub>5|0</sub> b = ꭢR<sup>b</sup>[(]_(a -<sub>4|0</sub> a)_ꭢR<sup>b</sup>[) +<sub>4|0</sub> a]]   
repeating function of b : +<sub>5|2</sub> defined by [a +<sub>5|2</sub> b = ꭢR<sup>b</sup>[a +<sub>4|0</sub> (]_0_ꭢR<sup>b</sup>[)]
4. found expression property   
    1. a +<sub>4|0</sub> b = a +<sub>3</sub> (a +<sub>3</sub> b)   
    2. (a +<sub>4|0</sub> b) +<sub>3</sub> (a +<sub>3</sub> c) = a +<sub>3</sub> ( a +<sub>3</sub> (b +<sub>1</sub> c ) )   
    3. (a +<sub>4|0</sub> b) +<sub>2</sub> (a +<sub>4|0</sub> c) = a +<sub>3</sub> ((a +<sub>3</sub> b) +<sub>1</sub> (a +<sub>3</sub> c))   
    4. (a +<sub>4|0</sub> b) +<sub>4|0</sub> c = (a +<sub>3</sub> c) +<sub>2</sub> (a +<sub>4|0</sub> (b +<sub>1</sub> (a +<sub>3</sub> b)))   
</details>

### operation (a +<sub>4|1</sub> b)   
<details><summary>aka. a<sup>(a<sup>(a<sup>(a<sup>(a<sup>(...)</sup>)</sup>)</sup>)</sup>)</sup> (number of a = b) = <sup>b</sup>a (tetration)</summary>

1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element of a : b = a -<sub>4|3</sub> a = 1   
inverse element of a : b = a -<sub>4|3</sub> 1  
identity element of b : a = b -<sub>4|1</sub> b   
inverse element of b : a = (b -<sub>4|1</sub> b) -<sub>4|1</sub> b   
2. domain and range : integer
3. produce other operation   
inverse function of a : [-<sub>4|1</sub>]()   
inverse function of b : [-<sub>4|3</sub>]()   
repeating function of a : +<sub>5|1</sub> defined by [a +<sub>5|1</sub> b = ꭢR<sup>b</sup>[(]_(a -<sub>4|1</sub> a)_ꭢR<sup>b</sup>[) +<sub>4|1</sub> a]]   
repeating function of b : +<sub>5|3</sub> defined by [a +<sub>5|3</sub> b = ꭢR<sup>b</sup>[a +<sub>4|1</sub> (]_1_ꭢR<sup>b</sup>[)]
4. found expression property   
    1. a +<sub>4|1</sub> (2n+1) = a +<sub>5|2</sub> n   
</details>

### operation (a -<sub>4|0</sub> b)   
<details><summary>aka. e<sup>W(ln(<sup>b</sup>√a))</sup>. <br>- W(x) is lambert W function (x = ye<sup>y</sup>)</summary>

<br> W(x) = $\sum_{n=1}^{∞}$(((-n)<sup>n-1</sup> / n!) * x<sup>n</sup>)   
1: parameter
param count = 2   
exchangeable = false   
stackable = false   
<details><summary>identity element of a : b = 1/a</summary>

a -<sub>4|0</sub> b = a = e<sup>W(ln(<sup>b</sup>√a))</sup>   
W<sup>-1</sup>(x) = xe<sup>x</sup>.   
ln(<sup>b</sup>√a) = (ln a)e<sup>ln a</sup> = a(ln a)   
<sup>b</sup>√a = a<sup>1/b</sup> = e<sup>a(ln a)</sup> = a<sup>a</sup>
1/b = a
b = 1/a
</details>   

<details><summary>inverse element of a : b = -a </summary>

a -<sub>4|0</sub> b = 1/a = e<sup>W(ln(<sup>b</sup>√a))</sup>   
W<sup>-1</sup>(x) = xe<sup>x</sup>.   
ln(<sup>b</sup>√a) = (ln 1/a)e<sup>ln 1/a</sup> = (1/a)*(ln 1/a)   
<sup>b</sup>√a = a<sup>1/b</sup> = e<sup>(1/a)(ln 1/a)</sup> = (1/a)<sup>(1/a)</sup>
1/b = log<sub>a</sub>((1/a)<sup>(1/a)</sup>)
b = 1 / (-1/a) = -a
</details>   

<details><summary>identity element of b : a = b<sup>2b</sup></summary>   

a -<sub>4|0</sub> b = b = e<sup>W(ln(<sup>b</sup>√a))</sup>   
W<sup>-1</sup>(x) = xe<sup>x</sup>.   
ln(<sup>b</sup>√a) = (ln b)e<sup>ln b</sup> = b(ln b)   
<sup>b</sup>√a = a<sup>1/b</sup> = e<sup>b(ln b)</sup> = b<sup>b</sup>
a =  (b<sup>b</sup>)<sub>b</sub> = b<sup>2b</sup>
</details>   

<details><summary>inverse element of b : a = b<sup>2b<sup>2b+2</sup></sup></summary>

a -<sub>4|0</sub> b = b<sup>2b</sup> = e<sup>W(ln(<sup>b</sup>√a))</sup>   
W<sup>-1</sup>(x) = xe<sup>x</sup>.   
ln(<sup>b</sup>√a) = (2bln b)e<sup>2bln b</sup> = 2blnb * b<sup>2b</sup>   
<sup>b</sup>√a = (b<sup>2b</sup>)(<sup>b<sup>2b</sup></sup>)   
a =  b<sup>2b<sup>2b+2</sup></sup>   
</details> 
2: domain and range : integer<br>   
3: produce other operation<br>   
4: found expression property<br>    
</details>

### operation (a -<sub>4|2</sub> b)   
<details><summary>aka. log<sub>a</sub>(log<sub>a</sub>(b))</summary>

1: parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element of a : b = a<sup>a<sup>a</sup></sup> = a +<sub>4|0</sub> a = a +<sub>4|1</sub> 3   
inverse element of a : b = a<sup>a<sup>a<sup>a<sup>a</sup></sup></sup></sup> = a +<sub>4|1</sub> 5    

<details><summary>identity element of b : a = <sup>b</sup>√b</summary>   

log<sub>a</sub>(log<sub>a</sub>(b)) = b   
log<sub><sup>x</sup>√b</sub>(b) = x   
a = <sup>x</sup>√b</sub>   
log<sub><sup>x</sup>√b</sub></sub>(log<sub><sup>x</sup>√b</sub></sub>(b)) = log<sub><sup>x</sup>√b</sub></sub>(x)   
if x == b, log<sub>a</sub>(log<sub>a</sub>(b)) = b   
a = <sup>b</sup>√b   
</details>   

<details><summary>inverse element of b : a = <sup>b -<sub>4|0</sub> 1/<sup>b</sup>√b</sup>√b = <sup>(e<sup>W(ln(b<sup>b<sup>1/b</sup></sup>)))</sup></sup>√b</summary>

log<sub>a</sub>(log<sub>a</sub>(b)) = <sup>b</sup>√b   
log<sub><sup>x</sup>√b</sub>(b) = x   
a = <sup>x</sup>√b</sub>   
log<sub><sup>x</sup>√b</sub></sub>(log<sub><sup>x</sup>√b</sub></sub>(b)) = log<sub><sup>x</sup>√b</sub></sub>(x) = <sup>b</sup>√b    
(<sup>x</sup>√b)<sup><sup>b</sup>√b</sup> = x = (b<sup><sup>b</sup>√b</sup>)<sup>1/x</sup>   
x<sup>x</sup> = b<sup><sup>b</sup>√b</sup>   
x = b<sup>b<sup>1/b</sup></sup>   
a = <sup>(e<sup>W(ln(b<sup>b<sup>1/b</sup></sup>)))</sup></sup>√b = <sup>b -<sub>4|0</sub> 1/<sup>b</sup>√b</sup>√b   
</details> 
2: domain and range : integer<br>   
3: produce other operation<br>   
4: found expression property<br>     
</details>

## ETC
1. addition dimansional coordinate and identity function.
2. how to find expression property of dimansion addition?