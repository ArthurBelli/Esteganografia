#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX 400
#define MAX2 160000
#define FNMAX 200

int LeDesenho (char nomearq[FNMAX], int M[MAX][MAX], int *pm, int *pn, int *pmax);
int LeTexto (char nomearq[FNMAX], char T[MAX2], int *pk);
int BeDe (int k, int m, int n, int *pb, int *pd);
int ProximosBBits (char T[MAX2], int b, int *pik, int *pib);
void Codifica (int D[MAX][MAX], int m, int n, char T[MAX2], int k, int Dl[MAX][MAX], int b, int d, int modo);
int Maximo (int D[MAX][MAX], int m, int n);
int EscreveDesenho (char nomearq[FNMAX], int M[MAX][MAX], int m, int n, int max);
void DeBeDe (int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int *pb, int *pd);
int DeCodifica (int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int b, int d, char T[MAX2], int modo);
int EscreveTexto (char nomearq[FNMAX], char T[MAX2], int k);

/*Funcoes adicionais*/
void restart (int *opcao, int modo);/*Para evitar poluicao visual na main*/
int pot (int base, int expo);
void listFiles (char extension[]);