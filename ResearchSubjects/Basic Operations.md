# Reserch of Basic Operation of Math.

## Overview
// description of reserch

## Property of Operation
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

## basic operation : +<sub>1</sub>

### operation nextnum(a), a'
aka a' in Peano's axioms
1. parameter
param count = 1      
stackable = true      
2. domain and range : natural number (positive integer)   
3. produce other operation   
repeating function : [+<sub>1</sub>](#operation-a-1-b) produced by [a + b = a_ꭢR<sup>b</sup>[']]   


### operation (a +<sub>1</sub> b)   
aka. a + b
1. parameter
param count = 2   
exchangeable = true   
stackable = true   
identity element = 0   
inverse element : b = 0 -<sub>1</sub> a = -a   
2. domain and range : 0 and natural number (unsigned integer)
3. produce other operation   
inverse function : [-<sub>1</sub>](#operation-a--1-b)   
repeating function : [+<sub>2</sub>](#operation-a-2-b) produced by [a +<sub>2</sub> b = ꭢR<sup>b</sup>[+ a]]   

### operation (a -<sub>1</sub> b)   
aka. a - b   
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

### operation (a +<sub>2</sub> b)   
aka. a × b
1. parameter
param count = 2   
exchangeable = true   
stackable = true   
identity element = 1   
inverse element : b = 1 -<sub>2</sub> a = 1/a   
2. domain and range : integer
3. produce other operation   
inverse function : [-<sub>2</sub>](#operation-a--2-b)   
repeating function : [+<sub>3</sub>](#operation-a-3-b) produced by [a +<sub>2</sub> b = 1_ꭢR<sup>b</sup>[* a]]   

### operation (a -<sub>2</sub> b)   
aka. a ÷ b and a/b
1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element = 1   
inverse element : b = a   
2. domain and range : rational number   
find new number : rational number that exist in between n and n+1.
3. produce other operation   

### operation (a +<sub>3</sub> b)   
aka. a<sup>b</sup>
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
inverse function of a : [-<sub>3|0</sub>]()   
inverse function of b : [-<sub>3|1</sub>]()   
repeating function of a : +<sub>4|0</sub> produced by [a +<sub>4|0</sub> b = ꭢR<sup>b</sup>[(]_<sup>a</sup>√a_ꭢR<sup>b</sup>[) +<sub>3</sub> a]]   
repeating function of b : +<sub>4|1</sub> produced by [a +<sub>4|1</sub> b = ꭢR<sup>b</sup>[a +<sub>3</sub> (]_1_ꭢR<sup>b</sup>[)]

### operation (a -<sub>3|0</sub> b)   
aka. <sup>b</sup>√a
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

### operation (a -<sub>3|1</sub> b)   
aka. log<sub>a</sub>b
1. parameter
param count = 2   
exchangeable = false   
stackable = false   
identity element = 0   
inverse element : b = a   
2. domain and range : rational number   
find new number : rational number that exist in between n and n+1.
3. produce other operation   