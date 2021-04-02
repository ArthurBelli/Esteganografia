#include "utils.h"

int main() {
    /*setup inicial*/
    int opcao, b, d, m1, m2, n1, n2, k, max, i, modo=0;
    int D[MAX][MAX], D1[MAX][MAX];
    char nomearq[FNMAX], T[MAX2];
    printf("Digite a opcao desejada:\n\t1. Codificar\n\t2. Decodificar\n\t3. Mostrar mensagem\n\t4. Ativar modo verborragico\n\t0. Finalizar\n\nOPCAO: ");
    scanf("%d", &opcao);

    while(opcao) {
/*Codificar*/
        if (opcao == 1) {
            listFiles(".pgm");
            printf("Arquivo que contem o desenho orignal: ");
            scanf(" %[^\n]", nomearq);
            if (LeDesenho(nomearq, D, &m1, &n1, &max) == 0) {
                printf("m = %d n = %d\n", m1, n1);
                listFiles(".txt");
                printf("Arquivo que contem a mensagem a ser ocultada: ");
                scanf(" %[^\n]", nomearq);
                if (LeTexto(nomearq, T, &k) == 0) {
                    printf("k = %d\n", k);
                    if (k) { /*So' vamos codificar algo se houver o que ser codificado*/
                        if (BeDe(k, m1, n1, &b, &d) == 0) {
                            printf("b = %d d = %d\n", b, d);
                            Codifica(D, m1, n1, T, k, D1, b, d, modo);
                            max = Maximo(D1, m1, n1); /*temos de atualizar o valor maximo da imagem*/
                            printf("Gravar desenho esteganografado em: ");
                            scanf(" %[^\n]", nomearq);
                            if (EscreveDesenho(nomearq, D1, m1, n1, max) == 0) {
                                printf("Operacao concluida com sucesso!\n");
                                restart(&opcao, modo);
                            }
                            else restart(&opcao, modo);
                        }
                        else restart(&opcao, modo);
                    }
                    else { /*Para k=0, a imagem ocultada sera igual a original*/
                        printf("b = 0 d = 0\n");
                        printf("Gravar desenho esteganografado em: ");
                        scanf(" %[^\n]", nomearq);
                        if (EscreveDesenho(nomearq, D, m1, n1, max) == 0) {
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
        else if (opcao == 2) {
            listFiles(".pgm");
            printf("Arquivo que contem o desenho orignal: ");
            scanf(" %[^\n]", nomearq);
            if (LeDesenho(nomearq, D, &m1, &n1, &max) == 0) {
                printf("m = %d n = %d\n", m1, n1);
                listFiles(".pgm");
                printf("Arquivo que contem o desenho esteganografado: ");
                scanf(" %[^\n]", nomearq);
                if (LeDesenho(nomearq, D1, &m2, &n2, &max) == 0) {
                    printf("m = %d n = %d\n", m2, n2);
                    if (m1 == m2 && n1 == n2) { /*Vericar se os desenhos tem as mesmas dimensoes*/
                        DeBeDe(D, D1, m1, n1, &b, &d);
                        printf("b = %d d = %d\n", b, d);
                        k = DeCodifica(D, D1, m1, n1, b, d, T, modo);
                        printf("k = %d\n", k);
                        printf("Gravar mensagem decodificada em: ");
                        scanf(" %[^\n]", nomearq);
                        if (EscreveTexto(nomearq, T, k) == 0) {
                            printf("Operacao concluida com sucesso!\n");
                            restart(&opcao, modo);
                        }
                        else restart(&opcao, modo);
                    }
                    else {
                        printf("ERRO: Operacao abortada. Os desenhos devem ser do mesmo tamanho\n");
                        restart(&opcao, modo);
                    }
                }
                else restart(&opcao, modo);
            }
            else restart(&opcao, modo);
        }
/*Mostrar mensagem*/
        else if (opcao == 3) {
            listFiles(".txt");
            printf("Arquivo que contem a mensagem: ");
            scanf(" %[^\n]", nomearq);
            if (LeTexto(nomearq, T, &k) == 0) {
                printf("k = %d\n", k);
                printf("A mensagem contida em %s eh:(tudo entre ---> e <---)\n", nomearq);
                printf("--->");
                for (i = 0; i < k; i++) {
                    printf("%c", T[i]);
                }
                printf("<---");
            }
            printf("\n");
            restart(&opcao, modo);
        }
/*Ativar modo verborragico*/
        else if (opcao == 4) {
            if (modo == 0) {
                modo = 1;
                printf("Modo verborragico ativado!\n");
            }
            else {
                modo = 0;
                printf("Modo verborragico desativado!\n");
            }
            restart(&opcao, modo);
        }
    }
    return 0;
}
