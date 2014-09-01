pushdownAutomata
================


file to load

'Ends in a 
2
S, read, a, A
S, read, b, S
A, read, a, A
A, read, b, S
A, read, z, F
aba
bbaabba
bbabab
aaaab
b
a

another file to try

'no. a's = no. b's
8
S, read, a, A
S, read, b, B
S, read, z, C
A, pop, a, X
A, pop, b, S
A, pop, z, Y
X, push, a, Y
Y, push, a, S
B, pop, a, S
B, pop, b, U
B, pop, z, V
U, push, b, V
V, push, b, S
C, pop, z, F
ab
aaabb
ababab
aaa
bbbaaa
aaaabbbb
