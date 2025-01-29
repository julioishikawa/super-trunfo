#include <stdio.h>
#include <string.h>

// Função para limpar o buffer de entrada
void limpar_buffer() {
    while (getchar() != '\n'); // Limpa todos os caracteres até o final da linha
}

// Função para formatar números inteiros com separadores de milhar (populacoes/areas)
void formatar_numero(char *resultado, int numero) {
    char buffer[50];
    sprintf(buffer, "%d", numero);
    int len = strlen(buffer);
    int pos = 0, contador = 0;

    for (int i = len - 1; i >= 0; i--) {
        resultado[pos++] = buffer[i];
        contador++;
        if (contador % 3 == 0 && i > 0) {
            resultado[pos++] = '.';  // Adiciona separador de milhares
        }
    }
    resultado[pos] = '\0';

    // Inverte a string para formar o número correto
    for (int i = 0; i < pos / 2; i++) {
        char temp = resultado[i];
        resultado[i] = resultado[pos - i - 1];
        resultado[pos - i - 1] = temp;
    }
}

// Função para formatar o PIB, com unidades de milhões, bilhões ou trilhões
void formatar_pib(char *resultado, double pib) {
    char buffer[50];

    if (pib >= 1000000000000) {  // Se o PIB for maior ou igual a 1 trilhão
        pib /= 1000000000000;  // Converte para trilhões
        sprintf(buffer, "%.2f trilhões", pib);  // Exibe com 2 casas decimais
    } else if (pib >= 1000000000) {  // Se o PIB for maior ou igual a 1 bilhão
        pib /= 1000000000;  // Converte para bilhões
        sprintf(buffer, "%.2f bilhões", pib);  // Exibe com 2 casas decimais
    } else if (pib >= 1000000) {  // Se o PIB for maior ou igual a 1 milhão
        pib /= 1000000;  // Converte para milhões
        sprintf(buffer, "%.2f milhões", pib);  // Exibe com 2 casas decimais
    } else {
        // Para PIBs abaixo de 1 milhão, exibe como um inteiro com separadores de milhar
        int pib_int = (int)pib;
        formatar_numero(buffer, pib_int);
        sprintf(buffer + strlen(buffer), "");  // Garantir a finalização da string
    }

    strcpy(resultado, buffer);  // Copia o resultado formatado
}

// Função para calcular a densidade populacional
double calcular_densidade(int populacao, int area) {
    if (area == 0) return 0;  // Evitar divisão por zero
    return (double)populacao / area;
}

// Função para calcular o PIB per capita
double calcular_pib_per_capita(double pib, int populacao) {
    if (populacao == 0) return 0;  // Evitar divisão por zero
    return pib / populacao;
}

// Função para formatar números flutuantes com separador de milhar e 2 casas decimais
void formatar_float(char *resultado, double numero) {
    int inteiro = (int)numero;
    formatar_numero(resultado, inteiro);

    // Calcula a parte decimal e adiciona com 2 casas decimais
    double decimal = numero - inteiro;
    char decimal_formatado[10];
    sprintf(decimal_formatado, "%.2f", decimal);
    // Remover o ponto extra entre a parte inteira e decimal
    if (decimal_formatado[0] == '0') {
        strcpy(resultado + strlen(resultado), decimal_formatado + 1); // Remove o '0' à esquerda
    } else {
        strcpy(resultado + strlen(resultado), decimal_formatado);
    }
}

#define NUM_ESTADOS 8
#define NUM_CIDADES 4

int main() {
    int populacoes[NUM_ESTADOS][NUM_CIDADES];
    int areas[NUM_ESTADOS][NUM_CIDADES];
    double pibs[NUM_ESTADOS][NUM_CIDADES];
    int pontosTuristicos[NUM_ESTADOS][NUM_CIDADES];

    char estados[] = "ABCDEFGH"; // Identificadores dos estados
    
    printf("Bem-vindo ao sistema de cadastro de cartas do Super Trunfo - Tema: Países\n");
    printf("Você cadastrará as cidades para cada estado.\n\n");
    printf("Não utilize pontos/virgulas, utilize apenas números. \n\n");

    // Cadastro de dados
    for (int i = 0; i < NUM_ESTADOS; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            char codigo[5];
            sprintf(codigo, "%c%02d", estados[i], j + 1);
            printf("Estado %c, Cidade %d (Código %s):\n", estados[i], j + 1, codigo);

            // Entrada e validação dos dados
            while (1) {
                printf("  População: ");
                if (scanf("%d", &populacoes[i][j]) == 1 && populacoes[i][j] >= 0) {
                    break;  // Sai do loop se a entrada for válida
                } else {
                    printf("Erro: A população não pode ser negativa ou não numérica. Tente novamente.\n");
                    limpar_buffer();  // Limpa o buffer de entrada para tentar novamente
                }
            }

            while (1) {
                printf("  Área (em km²): ");
                if (scanf("%d", &areas[i][j]) == 1 && areas[i][j] > 0) {
                    break;  // Sai do loop se a entrada for válida
                } else {
                    printf("Erro: A área deve ser um número positivo. Tente novamente.\n");
                    limpar_buffer();  // Limpa o buffer de entrada para tentar novamente
                }
            }

            while (1) {
                printf("  PIB: ");
                if (scanf("%lf", &pibs[i][j]) == 1 && pibs[i][j] >= 0) {
                    break;  // Sai do loop se a entrada for válida
                } else {
                    printf("Erro: O PIB deve ser um número válido e não negativo. Tente novamente.\n");
                    limpar_buffer();  // Limpa o buffer de entrada para tentar novamente
                }
            }

            while (1) {
                printf("  Número de pontos turísticos: ");
                if (scanf("%d", &pontosTuristicos[i][j]) == 1 && pontosTuristicos[i][j] >= 0) {
                    break;  // Sai do loop se a entrada for válida
                } else {
                    printf("Erro: O número de pontos turísticos não pode ser negativo ou não numérico. Tente novamente.\n");
                    limpar_buffer();  // Limpa o buffer de entrada para tentar novamente
                }
            }

            printf("Cidade %s cadastrada com sucesso!\n\n", codigo);
        }
    }

    // Exibição dos dados cadastrados
    printf("\nCartas cadastradas:\n");
    printf("=========================\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            char codigo[5];
            sprintf(codigo, "%c%02d", estados[i], j + 1);

            char populacao_formatada[50], area_formatada[50], pib_formatado[50];
            formatar_numero(populacao_formatada, populacoes[i][j]);
            formatar_numero(area_formatada, areas[i][j]);
            formatar_pib(pib_formatado, pibs[i][j]);

            // Cálculo da densidade e do PIB per capita
            double densidade = calcular_densidade(populacoes[i][j], areas[i][j]);
            double pib_per_capita = calcular_pib_per_capita(pibs[i][j], populacoes[i][j]);

            // Exibição
            printf("Código: %s\n", codigo);
            printf("População: %s habitantes\n", populacao_formatada);
            printf("Área: %s km²\n", area_formatada);
            printf("PIB: %s\n", pib_formatado);
            printf("Pontos turísticos: %d\n", pontosTuristicos[i][j]);

            // Exibir densidade e PIB per capita com formatação
            printf("Densidade Populacional: ");
            formatar_float(populacao_formatada, densidade);
            printf("%s habitantes/km²\n", populacao_formatada);

            printf("PIB per Capita: ");
            formatar_float(populacao_formatada, pib_per_capita);
            printf("R$ %s por habitante\n", populacao_formatada);

            printf("-------------------------\n");
        }
    }

    printf("Fim do programa.\n");
    return 0;
}
