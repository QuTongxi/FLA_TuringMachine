#Q = {0,a,b,ret,cpy,gbk,acc,ilg,emp,inv,i,il,ill,ille,illeg,illega,illegal,illegal_,illegal_i,illegal_in,illegal_inp,illegal_inpu,illegal_input,ret2}
#S = {a,b}
#G = {a,b,c,_,X,I,l,e,g,n,p,u,t}
#q0 = 0
#B = _
#F = {acc}
#N = 3

0 a__ Xa_ rr* a
a a__ _a_ rr* a
a b__ __b r*r b
b b__ __b r*r b 
b ___ ___ lll ret
ret _** _** l** ret
ret Xa* Xa* *l* ret
ret X_b X_b **l ret
ret X__ ___ *rr cpy

0 b__ X__ *** inv
0 ___ ___ *** emp
a ___ ___ *** inv
b a__ a__ *** inv


cpy _ab cab r*r cpy
cpy _a_ _a_ **l gbk
gbk _ab _ab **l gbk
gbk _a_ _a_ *rr cpy
cpy __b __b *** acc
inv *__ *__ r** inv
inv ___ ___ l** ret2
ret2 ___ ___ l** ret2
ret2 a__ ___ l** ret2
ret2 b__ ___ l** ret2
ret2 X__ ___ *** emp

emp ___ I__ r** i
i ___ l__ r** il
il ___ l__ r** ill
ill ___ e__ r** ille
ille ___ g__ r** illeg
illeg ___ a__ r** illega
illega ___ l__ r** illegal
illegal ___ ___ r** illegal_
illegal_ ___ I__ r** illegal_i
illegal_i ___ n__ r** illegal_in 
illegal_in ___ p__ r** illegal_inp
illegal_inp ___ u__ r** illegal_inpu
illegal_inpu ___ t__ r** illegal_input


