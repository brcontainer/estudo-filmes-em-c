#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE 1024
#define MAX_ACTORS 20
#define MAX_MOVIES 100
#define MAX_NAME 81

typedef struct
{
    char ano[5];
    char nome[MAX_NAME];
    char diretor[MAX_NAME];
    char atores[MAX_NAME][MAX_ACTORS];
    int total_filmes;
    int total_atores;
} Filme;

void cls()
{
    system("cls||clear");
}

void analise(Filme *filme, const char *item)
{
    int i = 0;

    char *tmp = (void *) item;

    char *coluna = strtok(tmp, ",");

    while (coluna != NULL) {
        i++;

        if (i == 1) {
            strcpy_s(filme->nome, MAX_NAME, coluna);
        } else if (i == 2) {
            strcpy_s(filme->ano, 5, coluna);
        } else if (i == 3) {
            strcpy_s(filme->diretor, MAX_NAME, coluna);
        } else {
            strcpy_s(filme->atores[i - 4], MAX_NAME, coluna);
        }

        coluna = strtok(NULL, ",");
    }

    filme->total_atores = i - 4;
}

void carregar(Filme filmes[], char *csv)
{
    FILE *stream;
    int i = 0;

    errno_t err = fopen_s(&stream, csv, "r");

    if (err != 0) {
        printf("Erro ao abrir o arquivo: %s\n", csv);
    } else {
        char linha[MAX_LINE];

        while (fgets(linha, MAX_LINE, stream)) {
            analise(&filmes[i], linha);
            i++;
        }

        fclose(stream);
    }

    filmes->total_filmes = i;
}

void exibir(Filme filmes[])
{
    int x = 0, y = 0, z = 0, total = filmes->total_filmes;

    printf("Total de filmes: %d/%d\n", total, MAX_MOVIES);
    printf("----------------\n");

    for (; x < total; x++) {
        printf(" - Nome:    %s\n", filmes[x].nome);
        printf(" - Ano:     %s\n", filmes[x].ano);
        printf(" - Diretor: %s\n", filmes[x].diretor);

        for (y = 0, z = filmes[x].total_atores; y < z; y++) {
            printf(" - Ator %d:  %s\n", y + 1, filmes[x].atores[y]);
        }

        printf("----------------\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    Filme filmes[MAX_MOVIES];

    carregar(filmes, "C:/DATA/filmes.csv");

    int active = 1, opcao = 0;
    char d;

    while (active) {
        cls();

        printf("Escolha uma das opções:\n");
        printf("1 - Exibir\n");
        printf("2 - Buscar\n");
        printf("3 - Adicionar\n");
        printf("4 - Deletar\n");
        printf("5 - Fechar\n");

        d = getchar();

        getchar();
        cls();

        opcao = d - '0';

        switch (opcao)
        {
            case 1:
                exibir(filmes);
                break;

            case 2:
                printf("Não implementado\n");
                break;

            case 3:
                printf("Não implementado\n");
                break;

            case 4:
                printf("Não implementado\n");
                break;

            case 5:
                break;

            default:
                printf("Opção inválida\n");
                break;
        }

        //Finaliza o loop
        if (opcao == 5) {
            break;
        }

        printf("Precione <Enter> para continuar\n");
        getchar();
    }

    return 0;
}
