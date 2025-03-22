#include <stdio.h>
#include <string.h>

#define MAX_JOGOS 100

int main(void) {
    char posicao[9];
    int opcao, movimento, jogadas, status, jogador_inicial, jogador;
    int pontos1 = 0, pontos2 = 0, rodadas = 0;
    int matriz_pontos[MAX_JOGOS][2] = {0}; // Matriz para registrar resultados de cada rodada
    char nome_jogador1[50], nome_jogador2[50];
    int idade_jogador1, idade_jogador2;

    do {
        printf("\n---------- JOGO DA VELHA ----------\n");
        printf("1 - Cadastrar Jogadores\n");
        printf("2 - Iniciar Jogo\n");
        printf("3 - Verificar Placar\n");
        printf("4 - Ranking Final e Encerrar\n");
        printf("Selecione a opção desejada: ");
        scanf("%d", &opcao);

        if (opcao > 4 || opcao < 1) {
            printf("\nOpção não reconhecida, tente novamente.\n");
            continue;
        }

        switch (opcao) {
        case 1:
            printf("\n---------- CADASTRO ----------\n");
            printf("Insira seu nome (jogador 1): ");
            scanf(" %[^\n]", nome_jogador1);
            printf("Insira sua idade (jogador 1): ");
            scanf("%d", &idade_jogador1);
            printf("Insira seu nome (jogador 2): ");
            scanf(" %[^\n]", nome_jogador2);
            printf("Insira sua idade (jogador 2): ");
            scanf("%d", &idade_jogador2);
            printf("\n%s será 'X' e %s será 'O'.\n", nome_jogador1, nome_jogador2);
            pontos1 = pontos2 = rodadas = 0;
            jogador_inicial = 1; // Define o jogador inicial como jogador 1
            memset(matriz_pontos, 0, sizeof(matriz_pontos)); // Zera a matriz de pontuações
            break;

        case 2:
            do {
                printf("\n---------- NOVA PARTIDA ----------\n");
                for (int i = 0; i < 9; i++) posicao[i] = '1' + i;
                jogadas = status = 0;
                jogador = jogador_inicial; // Alterna o jogador inicial a cada partida

                printf("\nJogo Iniciando...\n");
                printf("Nesta partida, %s começa jogando!\n", 
                       jogador == 1 ? nome_jogador1 : nome_jogador2);

                while (status == 0) {
                    printf("\n");
                    printf(" %c | %c | %c \n", posicao[0], posicao[1], posicao[2]);
                    printf("---|---|---\n");
                    printf(" %c | %c | %c \n", posicao[3], posicao[4], posicao[5]);
                    printf("---|---|---\n");
                    printf(" %c | %c | %c \n", posicao[6], posicao[7], posicao[8]);

                    printf("\n%s (%c), escolha um número: ", 
                        jogador == 1 ? nome_jogador1 : nome_jogador2, 
                        jogador == 1 ? 'X' : 'O');
                    scanf("%d", &movimento);
                    movimento--;

                    if (posicao < 0 || movimento > 8 || posicao[movimento] == 'X' || posicao[movimento] == 'O') {
                        printf("\nMovimento inválido, tente novamente.\n");
                        continue;
                    }

                    posicao[movimento] = (jogador == 1) ? 'X' : 'O';
                    jogadas++;

                    for (int i = 0; i < 3; i++) {
                        if ((posicao[i * 3] == posicao[i * 3 + 1] && posicao[i * 3 + 1] == posicao[i * 3 + 2]) ||
                            (posicao[i] == posicao[i + 3] && posicao[i + 3] == posicao[i + 6])) {
                            status = 1;
                        }
                    }

                    if ((posicao[0] == posicao[4] && posicao[4] == posicao[8]) ||
                        (posicao[2] == posicao[4] && posicao[4] == posicao[6])) {
                        status = 1;
                    }

                    if (status == 0 && jogadas == 9) {
                        status = -1;
                    }

                    if (status == 0) {
                        jogador = (jogador == 1) ? 2 : 1;
                    }
                }

                printf("\n");
                printf(" %c | %c | %c \n", posicao[0], posicao[1], posicao[2]);
                printf("---|---|---\n");
                printf(" %c | %c | %c \n", posicao[3], posicao[4], posicao[5]);
                printf("---|---|---\n");
                printf(" %c | %c | %c \n", posicao[6], posicao[7], posicao[8]);

                if (status == 1) {
                    printf("\n%s venceu!\n", jogador == 1 ? nome_jogador1 : nome_jogador2);
                    if (jogador == 1) {
                        pontos1++;
                        matriz_pontos[rodadas][0] = 1; // Jogador 1 ganha a rodada
                    } else {
                        pontos2++;
                        matriz_pontos[rodadas][1] = 1; // Jogador 2 ganha a rodada
                    }
                } else {
                    printf("\nO jogo empatou. Deu velha!\n");
                }

                rodadas++;
                printf("\nPlacar parcial: %s %d x %d %s\n", nome_jogador1, pontos1, pontos2, nome_jogador2);

                // Alterna o jogador inicial para a próxima partida
                jogador_inicial = (jogador_inicial == 1) ? 2 : 1;

                printf("\nDesejam jogar novamente? (1-Sim, 0-Não): ");
                scanf("%d", &opcao);
            } while (opcao == 1);
            break;

        case 3:
            printf("\n---------- PLACAR ----------\n");
            printf("Jogador 1: %s - %d pontos\n", nome_jogador1, pontos1);
            printf("Jogador 2: %s - %d pontos\n", nome_jogador2, pontos2);
            printf("Total de rodadas jogadas: %d\n", rodadas);
            break;

        case 4:
            printf("\n---------- RANKING FINAL ----------\n");
            printf("Jogador 1: %s - %d pontos\n", nome_jogador1, pontos1);
            printf("Jogador 2: %s - %d pontos\n", nome_jogador2, pontos2);
            printf("\nResultados detalhados:\n");
            for (int i = 0; i < rodadas; i++) {
                printf("Rodada %d: %s %d x %d %s\n", i + 1, nome_jogador1, matriz_pontos[i][0], matriz_pontos[i][1], nome_jogador2);
            }
            printf("\nObrigado por jogar!\n");
            break;
        }
    } while (opcao != 4);

    return 0;
}