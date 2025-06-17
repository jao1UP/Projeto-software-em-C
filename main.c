#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções para manipulação de TXT
void menu_txt() {
    FILE *arquivo;
    char texto[100];

    arquivo = fopen("dados.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao criar/abrir arquivo TXT!\n");
        return;
    }

    // Entrada de dados
    printf("\n--- Modo TXT (digite 'sair' para encerrar) ---\n");
    while (1) {
        printf("Insira texto: ");
        fgets(texto, sizeof(texto), stdin);
        texto[strcspn(texto, "\n")] = '\0';  // Remove newline

        if (strcmp(texto, "sair") == 0) break;

        fprintf(arquivo, "%s\n", texto);
    }

    // Leitura e exibição
    rewind(arquivo);  // Volta ao início do arquivo
    printf("\nConteúdo do arquivo TXT:\n");
    while (fgets(texto, sizeof(texto), arquivo) != NULL) {
        printf("%s", texto);
    }

    fclose(arquivo);
}

// Funções para manipulação de CSV
void escrever_csv(FILE *arquivo, const char *conteudo) {
    fprintf(arquivo, "%s\n", conteudo);
}

void ler_csv(FILE *arquivo) {
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
}

void menu_csv() {
    FILE *arquivo;
    char entrada[256];

    arquivo = fopen("dados.csv", "w+");
    if (arquivo == NULL) {
        printf("Erro ao criar/abrir arquivo CSV!\n");
        return;
    }

    // Cabeçalho inicial
    escrever_csv(arquivo, "Nome,Idade,Cidade");

    // Entrada de dados
    printf("\n--- Modo CSV (digite 'sair' para encerrar) ---\n");
    printf("Formato: dados separados por vírgulas\n");
    while (1) {
        printf("Insira dados (Nome,Idade,Cidade): ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';  // Remove newline

        if (strcmp(entrada, "sair") == 0) break;

        escrever_csv(arquivo, entrada);
    }

    // Leitura e exibição
    rewind(arquivo);
    printf("\nConteúdo do arquivo CSV:\n");
    ler_csv(arquivo);

    fclose(arquivo);
}

// Menu principal
int main() {
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Trabalhar com arquivo TXT\n");
        printf("2. Trabalhar com arquivo CSV\n");
        printf("3. Sair do programa\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        while (getchar() != '\n');  // Limpa buffer do teclado

        switch(opcao) {
            case 1:
                menu_txt();
                break;
            case 2:
                menu_csv();
                break;
            case 3:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}