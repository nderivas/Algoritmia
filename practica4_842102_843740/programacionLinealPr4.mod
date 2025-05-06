# Practica 4 - Algoritmia básica

# Capacidad del tren
param n, integer, > 0;
# Estación final
param m, integer > 0;
# Número de pedidos
param p, integer > 0;

# Pedidos
set P := 0..p-1;
set T := 0..2;
set V := 0..m-1;

param pedidos{P, T} >= 0;

# Solución
var x{P} binary ;

# Función objetivo
maximize ganancia: sum{i in P} x[i]*(pedidos[i,1] - pedidos[i,0])*pedidos[i,2];

# Restricciones
# Capacidad tren
rest_capacidad{j in V}: sum{i in P : pedidos[i,0] <= j and pedidos[i,1] > j} x[i] * pedidos[i,2] <= n;

#datos
data;
/*
# Problema 1
param n:=10;
param m:=3;
param p:=5;

param pedidos: 0 1 2 :=
0 	0 2 1
1 	0 3 2
2 	1 3 3
3  1 2 4
4 	2 3 10;
*/
/*
# Problema 2
param n:=10;
param m:=5;
param p:=6;

param pedidos: 0 1 2 :=
0 	3 5 10
1 	2 4 9
2 	1 3 4
3  0 2 5
4 	2 5 8
5	3 4 2;
*/

/*
# Problema 3
param n:=10;
param m:=4;
param p:=7;

param pedidos: 0 1 2 :=
0 	0 1 2
1 	0 2 4
2 	1 2 2
3  1 4 3
4 	2 3 9
5	2 4 5
6	3 4 1;
*/

param n:=1;
param m:=4;
param p:=5;

param pedidos: 0 1 2 :=
0	0 1 2
1	1 2 2
2	0 2 2
3	2 3 2
4	0 3 2;

/*
param n:=1000;
param m:=4;
param p:=3;

param pedidos: 0 1 2 :=
0 	0 3 1000
1 	0 1 10
2 	1 3 100;
*/


end;
