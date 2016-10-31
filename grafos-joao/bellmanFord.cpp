/* Esta versao do Single-Source Shortest Path (SSSP) eh o 
algoritmo de Bellman-Ford, que funciona para grafos com
CICLOS NEGATIVOS... A versao anterior de Dijkstra, até 
funciona para arestas negativas, MAS quando nao houver
ciclos!!!! Verifique..

Este algoritmo percorre a lista de adjacencias V-1 vezes,
relaxando as arestas... ISso garante que nao ficarah preso
em loop infinito..

Vamos aproveitar e verificar se ha ciclos negativos. Como??
Simples: apos finalizar o algoritmo, basta tentar relaxar as
arestas uma vez mais.. se isso acontecer, entao é porque ha
um ciclo negativo!!!

*/

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define INF 1000000


// estruturas uteis para representacao de grafos...
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

void printPath(int s, int t, vi p){
	if (t == s){
		printf("%d", s);
		return;
	}
	printPath(s, p[t], p);
	printf(" -> %d", t);
}

bool hasNegativeCycles(int V, vi dist, vector<vii> list){
	for (int u=0; u<V; u++)
			// para todos os adjacentes de u
		for(int j=0; j<list[u].size(); j++){
			ii v = list[u][j];
			if (dist[u] + v.second < dist[v.first]){
				return true;
			}
		}
	return false;
}


int main(){
	vector<vii> adjList(100);    // uma lista de adjacencia: para cada vertice v, tem-se um conjunto de tuplas (u,w)
	int A;  // nro de Arestas
	int V; // nro de Vertices
	int u,v,w;
	int s; // vertice source....   
	int t;  // vertice target...
 
	scanf("%d", &A);
	scanf("%d", &V);
	scanf("%d", &s);


	for (int i=0; i<A; i++) {
		scanf("%d %d %d", &u, &v, &w);
		adjList[u].push_back(make_pair(v,w));
	}

	// o vetor de distancia a partir de um vertice quqlquer tem inicialmente distancia INFINITA
	vi dist(V, INF); 
	vi parent(V);   // grava a trilha, guardando o pai  de cada vertice..

	dist[s] = 0;  // a distancia de s para s eh zero !!!

	
	// percorra a lista de adjacencia V-1 vezes...
	for (int i=0; i< V-1; i++)
		// agora visite todas as arestas...
		for (int u=0; u< V; u++)
			// para todos os adjacentes de u
			for(int j=0; j<adjList[u].size(); j++){
				ii v = adjList[u][j];
				if (dist[u] + v.second < dist[v.first]){
					dist[v.first] = dist[u]+ v.second; //vai acumulando a distancia..
					parent[v.first] = u;
				}
			}

	//printPath(s,t, parent); 
	//printf("\n");
	printf("Distancia de %d para os demais vertices...\n", s);
	for (int i=0; i<V; i++)
		printf("dist(%d) = %d ", i, dist[i]);
	printf("\n");
	if (hasNegativeCycles(V, dist, adjList))
		printf("O grafo contem ciclos negativos");
	else printf("O grafo NAO contem ciclos negativos");
	return 0;
}