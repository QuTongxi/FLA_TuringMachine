#Q = {1,2,3,4,5,t,tr,tru,true,f,fa,fal,fals,false}
#S = {a,b,c}
#G = {a,b,c,_,f,l,s,e,t,r,u}
#q0 = 1
#B = _
#F = {true}
#N = 2
1 a_ _a rr 1
1 b_ _b rr 1
1 c_ __ rl 5
1 __ __ l* 3
2 aa __ rr 2
2 bb __ rr 2
2 __ t_ r* t
t __ r_ r* tr
tr __ u_ r* tru
tru __ e_ r* true
2 ab __ r* 3
2 ba __ r* 3
2 a_ __ r* 3
2 b_ __ r* 3
2 ac __ r* 3
2 bc __ r* 3
2 ca __ r* 3
2 cb __ r* 3
2 c_ __ r* 3
2 _a __ ** 4
2 _b __ ** 4
2 _c __ ** 4
3 a_ __ r* 3
3 b_ __ r* 3
3 c_ __ r* 3
3 __ f_ r* f
4 __ f_ r* f
f __ a_ r* fa
fa __ l_ r* fal
fal __ s_ r* fals
fals __ e_ r* false
5 ** ** *l 5
5 _* _* *l 5
5 *_ *_ *r 2
5 __ __ *r 2





