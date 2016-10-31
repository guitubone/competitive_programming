/* Esta versao do ALL-PAIR Shortest Path (APSP) eh o 
algoritmo de Floyd Warshall, que funciona para grafos com
CICLOS NEGATIVOS tambem. 

Esta algoritmo usa MATRIZ de adjacencia (por efiencia na hora
de consultar o peso da aresta!) e tem complexidade V3...
a ideia e relaxar os vertices percorrendo a matriz V vezes
fazendo mat[i][j] = min (mat[i][j], mat[i][k]+mat[k][j])

para cada k: 0 a V-1, o algoritmo vai calculando o caminho
minino de i a j, para aquele vertice k !!! ao final, teremos
o caminho minino.. nao tem problemas se houver ciclos negativos..

VEja que aqui computamos a menor distancia de todos para todos
dai o nome ALL PAIR shortest patha !!

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define INF 1000000


// 
void iniciaMat(int V, int mat[][100]){
	for (int i=0; i<V; i++)
		for (int j=0; j<V; j++)
			if (i == j)
				mat[i][j] = 0;
			else mat[i][j] = INF;
}

void printMat(int V, int mat[][100]){
	for (int i=0; i<V; i++){
		for (int j=0; j<V; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

// PAra este algoritmo, se uma aresta v -> v for negativa, entao
// eh sinal de que tem um ciclo negativo......
bool hasNegativeCycles(int V, int mat[][100]){
	for (int i=0; i<V; i++)
		for (int j=0; j<V; j++)
			if (i==j && mat[i][j] < 0)
				return true;
	return false;
}


int main(){
	int adjMat[100][100];  // matriz de adjacencia....

	int A;  // nro de Arestas
	int V; // nro de Vertices
	int u,v,w;
	int s; // vertice source....   
	int t;  // vertice target...
 
	scanf("%d", &A);
	scanf("%d", &V);
	
	// prepara a matriz de adjacencia..
	iniciaMat(V, adjMat);  

	// le as arestas...
	for (int i=0; i<A; i++) {
		scanf("%d %d %d", &u, &v, &w);
		adjMat[u][v] = w;
	}

	
	// para cada vertice k...
	for (int k=0; k< V; k++)
		// Percorre a matriz [i,j] ajustando os pesos para k
		for (int i=0; i< V; i++)
			for (int j=0; j< V; j++)
				if (adjMat[i][k] + adjMat[k][j] < adjMat[i][j]){
					adjMat[i][j] = adjMat[i][k] + adjMat[k][j];  // relaxa a aresta !
				}
			

	printMat(V, adjMat); 
	printf("\n");

	if (hasNegativeCycles(V, adjMat))
		printf("O grafo contem ciclos negativos");
	else printf("O grafo NAO contem ciclos negativos");
	return 0;
}