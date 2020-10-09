/***************************************************************/
/**                                                           **/
/**   Arthur Pedroso Porto Belli          NUSP: ********      **/
/**   Exercicio-Programa 03                                   **/
/**   Professor: Marcel Kenji                                 **/
/**   Turma: 02                                               **/
/**                                                           **/
/***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX 400
#define MAX2 160000
#define FNMAX 200

int LeDesenho( char nomearq[FNMAX], int M[MAX][MAX], int *pm, int *pn, int *pmax );
int LeTexto( char nomearq[FNMAX], char T[MAX2], int *pk );
int BeDe( int k, int m, int n, int *pb, int *pd );
int ProximosBBits( char T[MAX2], int b, int *pik, int *pib );
void Codifica( int D[MAX][MAX], int m, int n, char T[MAX2], int k, int Dl[MAX][MAX], int b, int d, int modo );
int Maximo( int D[MAX][MAX], int m, int n );
int EscreveDesenho( char nomearq[FNMAX], int M[MAX][MAX], int m, int n, int max );
void DeBeDe( int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int *pb, int *pd );
int DeCodifica( int D[MAX][MAX], int Dl[MAX][MAX], int m, int n, int b, int d, char T[MAX2], int modo );
int EscreveTexto( char nomearq[FNMAX], char T[MAX2], int k );
/*Funcoes adicionais*/
void restart( int *opcao, int modo );/*Para evitar poluicao visual na main*/
int pot( int base, int expo );

int main() {
    int opcao, b, d, m1, m2, n1, n2, k, max, i, modo=0;
    int D[MAX][MAX], D1[MAX][MAX];
    char nomearq[FNMAX], T[MAX2];
    printf("Digite a opcao desejada:\n\t1. Codificar\n\t2. Decodificar\n\t3. Mostrar mensagem\n\t4. Ativar modo verborragico\n\t0. Finalizar\n\nOPCAO: ");
    scanf("%d", &opcao);
    while(opcao){
/*Codificar*/
        if(opcao == 1){
            printf("Arquivo que contem o desenho orignal: ");
            scanf(" %[^\n]", nomearq);
            if(LeDesenho(nomearq, D, &m1, &n1, &max) == 0){
                printf("m = %d n = %d\n", m1, n1);
                printf("Arquivo que contem a mensagem a ser ocultada: ");
                scanf(" %[^\n]", nomearq);
                if(LeTexto(nomearq, T, &k) == 0){
                    printf("k = %d\n", k);
                    if(k){ /*So' vamos codificar algo se houver o que ser codificado*/
                        if(BeDe(k, m1, n1, &b, &d) == 0){
                            printf("b = %d d = %d\n", b, d);
                            Codifica(D, m1, n1, T, k, D1, b, d, modo);
                            max = Maximo(D1, m1, n1); /*temos de atualizar o valor maximo da imagem*/
                            printf("Gravar desenho esteganografado em: ");
                            scanf(" %[^\n]", nomearq);
                            if(EscreveDesenho(nomearq, D1, m1, n1, max) == 0){
                                printf("Operacao concluida com sucesso!\n");
                                restart(&opcao, modo);
                            }
                            else restart(&opcao, modo);
                        }
                        else restart(&opcao, modo);
                    }
                    else{ /*Para k=0, a imagem ocultada sera igual a original*/
                        printf("b = 0 d = 0\n");
                        printf("Gravar desenho esteganografado em: ");
                        scanf(" %[^\n]", nomearq);
                        if(EscreveDesenho(nomearq, D, m1, n1, max) == 0){
                            printf("Operacao concluida com sucesso!\n");
                            restart(&opcao, modo);
                        }
                        else restart(&opcao, modo);
                    }
                }
                else restart(&opcao, modo);
            }
            else restart(&opcao, modo);
        }
/*Decodificar*/
        else if(opcao == 2){
            printf("Arquivo que contem o desenho orignal: ");
            scanf(" %[^\n]", nomearq);
            if(LeDesenho(nomearq, D, &m1, &n1, &max ) == 0){
                printf("m = %d n = %d\n", m1, n1);
                printf("Arquivo que contem o desenho esteganografado: ");
                scanf(" %[^\n]", nomearq);
                if(LeDesenho(nomearq, D1, &m2, &n2, &max ) == 0){
                    printf("m = %d n = %d\n", m2, n2);
                    if(m1 == m2 && n1 == n2){ /*Vericar se os desenhos tem as mesmas dimensoes*/
                        DeBeDe(D, D1, m1, n1, &b, &d);
                        printf("b = %d d = %d\n", b, d);
                        k = DeCodifica(D, D1, m1, n1, b, d, T, modo);
                        printf("k = %d\n", k);
                        printf("Gravar mensagem decodificada em: ");
                        scanf(" %[^\n]", nomearq);
                        if(EscreveTexto(nomearq, T, k) == 0){
                            printf("Operacao concluida com sucesso!\n");
                            restart(&opcao, modo);
                        }
                        else restart(&opcao, modo);
                    }
                    else{
                        printf("ERRO: Operacao abortada. Os desenhos devem ser do mesmo tamanho\n");
                        restart(&opcao, modo);
                    }
                }
                else restart(&opcao, modo);
            }
            else restart(&opcao, modo);
        }
/*Mostrar mensagem*/
        else if(opcao == 3){
            printf("Arquivo que contem a mensagem: ");
            scanf(" %[^\n]", nomearq);
            if(LeTexto(nomearq, T, &k) == 0){
                printf("k = %d\n", k);
                printf("A mensagem contida em %s eh:(tudo entre ---> e <---)\n", nomearq);
                printf("--->");
                for(i=0; i<k; i++){
                    printf("%c", T[i]);
                }
                printf("<---");
            }
            printf("\n");
            restart(&opcao, modo);
        }
/*Ativar modo verborragico*/
        else if(opcao == 4){
            if(modo == 0){
                modo = 1;
                printf("Modo verborragico ativado!\n");
            }
            else{
                modo = 0;
                printf("Modo verborragico desativado!\n");
            }
            restart(&opcao, modo);
        }
    }
    return 0;
}


int LeDesenho( char nomearq[FNMAX], int M[MAX][MAX], int *pm, int *pn, int *pmax )
{
    char linha1[3]; /*como vamos ignorar a primeira linha nao vamos alocar muita memoria para ela*/
    FILE *fp;
    int i, j, erro;
    if (!(fp = fopen(nomearq, "r"))){
        printf("Erro ao abrir o arquivo %s\n", nomearq);
        return 1;
    }
    if(!(erro = fscanf(fp, "%s", linha1))){
    printf("Erro ao ler o arquivo %s\n", nomearq);
    return 1;
    }
    if(linha1[0] != 'P' || linha1[1] != '2'){
        printf("ERRO: formato de arquivo desconhecido!\n");
        return 1;
    }
    if(!(erro = fscanf(fp, "%d %d %d", &(*pn), &(*pm), &(*pmax)))){
        printf("Erro ao ler o arquivo %s\n", nomearq);
        return 1;
    }
    for(i=0; i<(*pm); i++){
        for(j=0; j<(*pn); j++){
            if(!(erro = fscanf(fp, "%d", &M[i][j]))){
                printf("Erro ao ler o arquivo %s\n", nomearq);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

int LeTexto( char nomearq[FNMAX], char T[MAX2], int *pk )
{
    FILE *fp;
    if (!(fp = fopen(nomearq, "r"))){
        printf("Erro ao abrir o arquivo %s\n", nomearq);
        return 1;
    }
    *pk = 0;
    while (fscanf(fp, "%c", &T[*pk]) > 0){
        *pk += 1;
    }
    T[*pk] = '\0';
    fclose(fp);
    return 0;
}

int BeDe( int k, int m, int n, int *pb, int *pd )
{ /*Nao precisamos nos preocupar com o caso em que k=0, pois a funcao soh chega a ser chamada se k>0*/
    *pb = 0;
    while((m*n-1)*(*pb) < 8*k){
        *pb += 1;
    }
    if(*pb <= 8){/*precisamos garantir que b será divisor de 8, se sair do while e o resto for != 0, quer dizer que é impar*/
        if(8%(*pb) != 0) {
            if(*pb == 5) *pb = 8;
            else *pb += 1;
        }
    }
    else{ /*Para caso pb > 8 -->ERRO*/
        printf("ERRO: Nao foi possivel encontrar valores de b e d suficientes!\n");
        return 1;
    }

    *pd = n;
    if(m < *pd) *pd = m;/*vamos comecar pd = min(m, n) e ir descrescendo, assim, conseguimos garantir que o valor obtido seja o maior possivel*/
    while((*pd >=1) && ((m/(*pd))*(n/(*pd))*(*pb) < 8*k + *pb)){ /*como estamos decrescendo o valor de pd, o primeiro que falhar sera o maior que atende*/
        *pd -= 1;
    }
    if(*pd == 0){
        printf("ERRO: Nao foi possivel encontrar valores de b e d suficientes!\n");
        return 1;
    }
    return 0;
}

int ProximosBBits( char T[MAX2], int b, int *pik, int *pib )
{ /*Nao precisamos nos preocupar com o caso em que b=0, pois a funcao soh chega a ser chamada se b>0*/
    int proximo=0;
    if(*pik >= 0){
        if(*pib  == 8){
            *pik += 1;
            *pib = 0;
        }
        proximo = (((int)T[*pik]/pot(2,*pib))%(pot(2,b)));
        *pib += b;
    }
    else{ /*esconder o parametro b*/
        proximo = ((b/pot(2,*pib))%pot(2,b));
        *pik += 1;
    }
    return proximo;
}

void Codifica( int D[MAX][MAX], int m, int n, char T[MAX2], int k, int D1[MAX][MAX], int b, int d, int modo )
{ /*Nao precisamos nos preocupar com o caso em que b=0 && d=0, pois a funcao soh chega a ser chamada se b>0 && d>0*/
    int ib=0, ik=-1, i=0, j=0; /*Vamos iniciar ik = -1  para podermos esconder o b antes de esconder o texto*/
    for(i=0; i<m; i++){ /*Vamos primeiro copiar a imagem original para depois substituir apenas os pixels de ocultacao, caso existam*/
        for(j=0; j<n; j++){
            D1[i][j] = D[i][j];
        }
    }
    for(i=d-1; i<=(m/d)*d-1 && ik<k; i+= d){
        for(j=d-1; j<=(n/d)*d-1 && ik<k; j+= d){
            D1[i][j] = ((D1[i][j]/pot(2,b))*pot(2,b) + ((D1[i][j] + ProximosBBits(T, b, &ik, &ib))%pot(2,b))); /*Atribuicao dos novos valores*/
            if(modo){
                printf("(%d,%d) bits %d original %02x codificado %02x\n", i, j, ((D1[i][j]-D[i][j]+256)%pot(2,b)), D[i][j], D1[i][j]);
            }
        }
    }
}

int Maximo( int D[MAX][MAX], int m, int n)
{
    int max = D[0][0];
    int i, j;
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            if(D[i][j] > max) max = D[i][j];
        }
    }
    return max;
}

int EscreveDesenho( char nomearq[FNMAX], int M[MAX][MAX], int m, int n, int max )
{
    int i, j, print;
    FILE *fp;
    if (!(fp = fopen(nomearq, "w"))){
        printf("Erro ao abrir o arquivo %s\n", nomearq);
        return 1;
    }
    /*vamos seguir o padrao dos arquivos .PGM*/
    fprintf(fp, "P2\n"); /*Como no enunciado, primeira linha contem P2*/
    fprintf(fp, "%d %d\n", n, m); /*Segunda linha contem numero de colunas e de linhas, respectivamente*/
    fprintf(fp, "%d\n", max); /*Em seguida, o valor maximo da matriz*/
    for(i=0; i<m; i++){ /*E por fim, imprimimos os valores da matriz M no arquivo*/
        for(j=0; j<n; j++){
            if(!(print = fprintf(fp, "%03d ", M[i][j]))){ /*caso ocorra erro na impressao*/
                printf("Erro ao gravar a imagem no arquivo %s\n", nomearq);
                return 1;
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}

void DeBeDe( int D[MAX][MAX], int D1[MAX][MAX], int m, int n, int *pb, int *pd )
{
    int i, min;
    *pd = 0;
    *pb = 1; /*primeiro valor possivel para b*/
    min = n;
    if(m < min) min = m; /*vamos garantir que nao percorramos valores invalidos da matriz, como vamos percorrer somente a diagonal podemos pegar a menor dimensao*/
    for(i=0; i<min && *pd==0 ; i++){ /*achar o parametro d*/
        if((D1[i][i]-D[i][i])){ /*seguindo a dica do enunciado*/
            *pd = i+1; /*Como o primeiro pixel de ocultacao utilizado guarda o valor de b, nesse caso y = b, assim podemos calcular b*/
        }
    }
    i=0;
    if(*pd){ /*se nao encontrar valor para d, ja sabemos que b nao tem valor e k = 0*/
        while(i<=8){ /*Como sao apenas 4 casos de valores possiveis para b, podemos rodar um for para achar d sem mto desperdicio de tempo e memoria*/
            if(*pb != (D1[*pd-1][*pd-1] - D[*pd-1][*pd-1] + 256)%pot(2,*pb)) *pb += 1; /*  y = (z-x+256)%2^b  */
            i++;
        }
    }
    else *pb = 0;
}

int DeCodifica( int D[MAX][MAX], int D1[MAX][MAX], int m, int n, int b, int d, char T[MAX2], int modo )
{
    int i, j, k=0, soma=0, passa=0, mais;
    if(b && d){
        for(i=d-1; i<=(m/d)*d-1; i += d){
            for(j=d-1; j<=(n/d)*d-1; j += d){
                if(k>0){ /*condicao para nao considerar o primeiro pixel de ocultacao que guarda b e d*/
                    mais = ((D1[i][j] - D[i][j] + 256)%pot(2,b))*pot(2,passa); /*aqui vamos fazer o processo inverso da Codifica, vamos remontar o numero espalhado*/
                    soma += mais;
                    passa += b;
                    if(modo) printf("(%d,%d) bits %02d original %02x codificado %02x\n", i, j, mais, D[i][j], D1[i][j]);
                    if(passa == 8){ /*atribuimos ao indice do vetor o valor na tabela ASCII do caractere apos o numero terminar de ser montado*/
                        if(soma){
                            T[k-1] = (char)soma; /*conversao do inteiro para char*/
                            k++;
                            passa = 0;
                            soma = 0;
                        }
                    }
                }
                else k++;
            }
        }
        return k-1;
    }
    else return 0;/*se b == 0 e d == 0, k == 0, ou seja, nao ha texto escondido na imagem*/
}

int EscreveTexto( char nomearq[FNMAX], char T[MAX2], int k )
{
    FILE *fp;
    int i;
    if (!(fp = fopen(nomearq, "w"))){
        printf("Erro ao abrir o arquivo %s\n", nomearq);
        return 1;
    }
    for(i=0; i<k; i++){
        if(!(fprintf(fp, "%c", T[i]))){
            printf("ERRO: O programa nao conseguiu escrever a mensagem no arquivo %s\n", nomearq);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void restart( int *opcao, int modo )
{
    if(modo == 0) printf("\nDigite a opcao desejada:\n\t1. Codificar\n\t2. Decodificar\n\t3. Mostrar mensagem\n\t4. Ativar modo verborragico\n\t0. Finalizar\n\nOPCAO: ");
    else printf("\nDigite a opcao desejada:\n\t1. Codificar\n\t2. Decodificar\n\t3. Mostrar mensagem\n\t4. Desativar modo verborragico\n\t0. Finalizar\n\nOPCAO: ");
    scanf("%d", &(*opcao));
}

int pot( int base, int expo )
{
    int i, k=1;
    for(i=0; i<expo;i++){
        k *= base;
    }
    return k;
}
