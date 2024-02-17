# Reserch Method

The Reason of make this project is fact that the math reserching with only human brain is have huge limit.   
When math required too many operations and too many example to find a patterns, computer's operation abillity can help   
math reserchers.   
We already have a code that can operate math correctly, so we have to consider a reserch method in this project(Inifinity Binary Integer)   

## Appendix
[1. Making Law(= experession property) with operating random examples.](#1-making-law-experession-property-with-operating-random-examples)    

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