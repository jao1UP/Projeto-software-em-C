#include <stdio.h>
#include <string.h>

// Define constantes
#define MAX_NOME 50

// Estrutura para armazenar dados do aluno
typedef struct {
    char nome[MAX_NOME];
    float simulado1;    // Pontuação extra (0 a 1)
    float simulado2;    // Pontuação extra (0 a 1)
    float notaProva;    // Nota da prova (0 a 10)
    float notaAVS;      // Nota da AVS (0 a 10, se necessário)
    float media;        // Média final
    int precisaAVS;     // Indicador se AVS é necessária
} Aluno;

// Função para ler os dados do aluno
void lerDados(Aluno *aluno) {
    printf("Digite o nome do aluno: ");
    fgets(aluno->nome, MAX_NOME, stdin);
    // Remove o '\n' do final da string
    aluno->nome[strcspn(aluno->nome, "\n")] = 0;

    // Lê Simulado 1
    printf("Digite a nota do Simulado 1 (0 a 1): ");
    scanf("%f", &aluno->simulado1);
    while (aluno->simulado1 < 0 || aluno->simulado1 > 1) {
        printf("Nota inválida! Digite um valor entre 0 e 1: ");
        scanf("%f", &aluno->simulado1);
    }

    // Lê Simulado 2
    printf("Digite a nota do Simulado 2 (0 a 1): ");
    scanf("%f", &aluno->simulado2);
    while (aluno->simulado2 < 0 || aluno->simulado2 > 1) {
        printf("Nota inválida! Digite um valor entre 0 e 1: ");
        scanf("%f", &aluno->simulado2);
    }

    // Lê Nota da Prova
    printf("Digite a nota da Prova (0 a 10): ");
    scanf("%f", &aluno->notaProva);
    while (aluno->notaProva < 0 || aluno->notaProva > 10) {
        printf("Nota inválida! Digite um valor entre 0 e 10: ");
        scanf("%f", &aluno->notaProva);
    }

    // Verifica se AVS é necessária
    float somaProva = aluno->notaProva + aluno->simulado1 + aluno->simulado2;
    if (somaProva < 6) {
        aluno->precisaAVS = 1;
        printf("Soma da Prova (%.2f) + Simulados (%.2f + %.2f) = %.2f < 6. Digite a nota da AVS (0 a 10): ",
               aluno->notaProva, aluno->simulado1, aluno->simulado2, somaProva);
        scanf("%f", &aluno->notaAVS);
        while (aluno->notaAVS < 0 || aluno->notaAVS > 10) {
            printf("Nota inválida! Digite um valor entre 0 e 10: ");
            scanf("%f", &aluno->notaAVS);
        }
    } else {
        aluno->precisaAVS = 0;
        aluno->notaAVS = 0; // Não usada
    }

    // Limpa o buffer do teclado
    while (getchar() != '\n');
}

// Função para calcular a média do aluno
void calcularMedia(Aluno *aluno) {
    if (aluno->precisaAVS) {
        // Média com AVS: Nota AVS + Simulado 1 + Simulado 2
        aluno->media = aluno->notaAVS + aluno->simulado1 + aluno->simulado2;
    } else {
        // Média sem AVS: Nota da Prova + Simulado 1 + Simulado 2
        aluno->media = aluno->notaProva + aluno->simulado1 + aluno->simulado2;
    }
}

// Função para exibir os dados do aluno
void exibirDados(Aluno aluno) {
    printf("\n--- Dados do Aluno ---\n");
    printf("Nome: %s\n", aluno.nome);
    printf("Simulado 1 (extra): %.2f\n", aluno.simulado1);
    printf("Simulado 2 (extra): %.2f\n", aluno.simulado2);
    printf("Nota da Prova: %.2f\n", aluno.notaProva);
    if (aluno.precisaAVS) {
        printf("Nota da AVS: %.2f\n", aluno.notaAVS);
    } else {
        printf("Nota da AVS: Não necessária\n");
    }
    printf("Média: %.2f\n", aluno.media);
    printf("Situação: %s\n", aluno.media >= 6 ? "Aprovado" : "Reprovado");
}

int main() {
    Aluno aluno;

    printf("=== Sistema de Gerenciamento de Notas ===\n");
    
    // Leitura dos dados
    lerDados(&aluno);
    
    // Cálculo da média
    calcularMedia(&aluno);
    
    // Exibição dos dados
    exibirDados(aluno);

    return 0;
}
