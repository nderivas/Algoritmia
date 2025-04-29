# Practica 4 - Algoritmia básica

# Capacidad del tren
param n, integer, > 0;
# Estación final
param m, integer > 0;
# Número de pedidos
param p, integer > 0;

# Pedidos
set P := 1..p;
set T := 1..3;
set V := 1..m-1;

param pedidos{P, T} >= 0;

# Solución
var x{P} binary ;

# Función objetivo
maximize perdida: sum{i in P} x[i]*(pedidos[i,2] - pedidos[i,1])*pedidos[i,3];

# Restricciones
# Capacidad tren
rest_capacidad{j in V}: sum{i in P : pedidos[i,1] <= j and pedidos[i,2] > j} x[i] * pedidos[i,3] <= n;

#datos
data;
/*
# Problema 1
param n:=10;
param m:=3;
param p:=5;

param pedidos: 1 2 3 :=
1 	0 2 1
2 	0 3 2
3 	1 3 3
4  1 2 4
5 	2 3 10;
*/

# Problema 2
param n:=10;
param m:=5;
param p:=6;

param pedidos: 1 2 3 :=
1 	3 5 10
2 	2 4 9
3 	1 3 4
4  0 2 5
5 	2 5 8
6	3 4 2;

/*
# Problema 3
param n:=10;
param m:=4;
param p:=7;

param pedidos: 1 2 3 :=
1 	0 1 2
2 	0 2 4
3 	1 2 2
4  1 4 3
5 	2 3 9
6	2 4 5
7	3 4 1;
*/

end;
