# Reserch Method

The Reason of make this project is fact that the math reserching with only human brain is have huge limit.   
When math required too many operations and too many example to find a patterns, computer's operation abillity can help   
math reserchers.   
We already have a code that can operate math correctly, so we have to consider a reserch method in this project(Inifinity Binary Integer)   

## Appendix
[1. Making Law(= experession property) with operating random examples.](#1-making-law-experession-property-with-operating-random-examples)    
[2. Expression Tree]()   

## 1. Making Law(= experession property) with operating random examples.
To find Law of Variable X, try making random expressions of X.   
|ID|expression|
|--|----------|
|1|x+1|
|2|√x^2|
|3|-x+4|
|4|│x│|
|...|...|   


and try make N values for X.   
|ID|value X|
|--|-------|
|1|100|
|2|3.5|
|3|-6.6|
|4|12345|
|...|...|   


that put the values in the expressions.   
|ID|expression|put X1 case|put X2 case|put X3 case|put X4 case|
|--|----------|---|---|---|---|
|0|x|100|3.5|-6.6|12345|
|1|x+1|101|4.5|-5.6|12346|
|2|√x^2|101|3.5|6.6|12345|
|3|-x+4|-96|0.5|10.6|-12341|
|4|│x│|101|3.5|6.6|12345|   


And We can find ID2, ID4 expressions have totaly same result in every value cases.   
So we can assumed this Law of X (√x^2 = │x│).   
To find Law of X with not rational result, we also assumed by approximate value to rational number.   
If difference of two values are decresing in many cases, we can assumed that Law of X.   


After assumed Law, we have to find domain of X that Law is True.   
But number that we consider have the discountable infinity of cases(real number).   
The Brut Force algorithm (one by one) would not be the right way to do it.   

method 1. just save that assumed Law and put the additional variable to judge reliability.       
|ID|Law|reliability|Assumed Domain|Candidate Domain|   
|--|-------|-----|--------|--------|
|n|√x^2=│x│|4|complex number set|rational number set(-6.6<=x<=12345...(and other property))   

In Reserch Prograss, if that law is used and that law is right, then reliability increse 1. and the Candidate domain is estimated from the previously values.   
But if find wrong cases, reliability will be 0. and domain is updated to Candidate domain.


method 2. Prove the Law from the underlying estimated Law (Expression Tree)


## Expression Tree
