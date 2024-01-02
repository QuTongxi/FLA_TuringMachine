#Q = {1,2,3,4,5,6,7,8,9,10,11,i,il,ill,ille,illeg,illega,illegal,illegal_,illegal_i,illegal_in,illegal_inp,illegal_inpu,illegal_input}
#S = {a,b,c}
#G = {a,b,c,_,x,I,l,e,g,n,p,u,t}
#q0 = 1
#B = _
#F = {8}
#N = 2
1 __ I_ r* i
1 a_ x_ r* 2
1 b_ b_ ** 9
2 a_ a_ r* 2
2 __ __ ** 9
2 b_ bc rr 3
3 b_ bc rr 3
3 a_ a_ ** 9
3 __ __ l* 4
4 a_ a_ l* 4
4 b_ b_ l* 4
4 x_ x_ r* 5
5 a_ x_ r* 2
5 b_ b_ r* 5
5 __ __ l* 6
6 *_ __ l* 6
6 __ __ rl 7
7 _c c_ rl 7
7 __ __ lr 8
9 *_ *_ r* 9
9 __ __ l* 10
10 *_ __ l* 10
10 __ __ r* 11
11 __ I_ r* i
i __ l_ r* il
il __ l_ r* ill
ill __ e_ r* ille
ille __ g_ r* illeg
illeg __ a_ r* illega
illega __ l_ r* illegal
illegal __ __ r* illegal_
illegal_ __ I_ r* illegal_i
illegal_i __ n_ r* illegal_in 
illegal_in __ p_ r* illegal_inp
illegal_inp __ u_ r* illegal_inpu
illegal_inpu __ t_ r* illegal_input

