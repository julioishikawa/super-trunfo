#include <stdio.h>
#include <string.h>
#include <limits.h>

void limpar_buffer() {
    while (getchar() != '\n');
}

void formatar_numero_inteiro(char *resultado, unsigned long int numero) {
    char buffer[50];
    sprintf(buffer, "%lu", numero);
    int len = strlen(buffer);
    int pos = 0, contador = 0;

    for (int i = len - 1; i >= 0; i--) {
        resultado[pos++] = buffer[i];
        contador++;
        if (contador % 3 == 0 && i > 0) {
            resultado[pos++] = '.';
        }
    }
    resultado[pos] = '\0';

    for (int i = 0; i < pos / 2; i++) {
        char temp = resultado[i];
        resultado[i] = resultado[pos - i - 1];
        resultado[pos - i - 1] = temp;
    }
}

void formatar_numero_flutuante(char *resultado, float numero) {
    unsigned long int parte_inteira = (unsigned long int)numero;
    formatar_numero_inteiro(resultado, parte_inteira);

    float parte_decimal = numero - parte_inteira;
    
    if (parte_decimal > 0.0001f || parte_decimal < -0.0001f) {
        char decimal_formatado[10];
        sprintf(decimal_formatado, "%.2f", parte_decimal);
        
        if (decimal_formatado[0] == '0') {
            strcat(resultado, decimal_formatado + 1);
        } else {
            strcat(resultado, decimal_formatado);
        }
        
        int len = strlen(resultado);
        if (len >= 3 && strcmp(resultado + len - 3, ".00") == 0) {
            resultado[len - 3] = '\0';
        }
    }
}

void formatar_densidade_populacional(char *resultado, float densidade) {
    unsigned long int densidade_inteira = (unsigned long int)(densidade + 0.5);
    formatar_numero_inteiro(resultado, densidade_inteira);
}

void formatar_pib_per_capita(char *resultado, float pib_per_capita) {
    formatar_numero_flutuante(resultado, pib_per_capita);
    char pib_como_texto[50];
    sprintf(pib_como_texto, "R$ %s", resultado);
    strcpy(resultado, pib_como_texto);
}

void formatar_pib(char *resultado, float pib) {
    char buffer[50];

    if (pib >= 1000000000000) {
        pib /= 1000000000000;
        sprintf(buffer, "%.2f trilhões", pib);
    } else if (pib >= 1000000000) {
        pib /= 1000000000;
        sprintf(buffer, "%.2f bilhões", pib);
    } else if (pib >= 1000000) {
        pib /= 1000000;
        sprintf(buffer, "%.2f milhões", pib);
    } else {
        int pib_inteiro = (int)pib;
        formatar_numero_inteiro(buffer, pib_inteiro);
    }

    strcpy(resultado, buffer);
}

// Função para formatar o Super Poder com separadores de milhar e sem casas decimais
void formatar_super_poder(char *resultado, float super_poder) {
    // Limitar a 0 casas decimais (pois é um número inteiro)
    sprintf(resultado, "%.0f", super_poder);  // Utiliza %f para números float com 0 casas decimais
    int len = strlen(resultado);
    int pos = 0, contador = 0;

    // Adicionar os números com separadores de milhar
    char buffer[50];
    for (int i = len - 1; i >= 0; i--) {
        buffer[pos++] = resultado[i];
        contador++;

        // Adicionar separador de milhar a cada 3 dígitos
        if (contador % 3 == 0 && i > 0) {
            buffer[pos++] = '.';  // Adiciona o separador de milhar
        }
    }

    buffer[pos] = '\0';

    // Inverter a string para corrigir a ordem dos caracteres
    for (int i = 0; i < pos / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[pos - i - 1];
        buffer[pos - i - 1] = temp;
    }

    strcpy(resultado, buffer);  // Copiar para a variável final de resultado
}

float calcular_densidade_populacional(unsigned long int populacao, float area) {
    if (area == 0) return 0;
    return (float)populacao / area;
}

float calcular_pib_per_capita(float pib, unsigned long int populacao) {
    if (populacao == 0) return 0;
    return pib / populacao;
}

float calcular_super_poder(float pib, unsigned long int populacao, float area, int pontos_turisticos, float densidade, float pib_per_capita) {
    float super_poder = 0;
    
    super_poder += populacao;
    super_poder += area;
    super_poder += pib;
    super_poder += pontos_turisticos;
    super_poder += densidade;
    super_poder += pib_per_capita;
    
    return super_poder;
}

#define NUM_ESTADOS 1
#define NUM_CIDADES 1

int main() {
    unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES];
    float areas[NUM_ESTADOS][NUM_CIDADES];
    float pibs[NUM_ESTADOS][NUM_CIDADES];
    int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES];
    char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50];
    char estados[] = "ABCDEFGH";

    printf("Bem-vindo ao sistema de cadastro de cartas do Super Trunfo - Tema: Países\n");
    printf("Você cadastrará as cidades para cada estado.\n\n");
    printf("Não utilize pontos/virgulas, utilize apenas números. \n\n");

    for (int i = 0; i < NUM_ESTADOS; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            char codigo[5];
            sprintf(codigo, "%c%02d", estados[i], j + 1);
            printf("Estado %c, Cidade %d (Código %s):\n", estados[i], j + 1, codigo);

            while (1) {
                printf("  Nome da cidade: ");
                fgets(nomes_cidades[i][j], sizeof(nomes_cidades[i][j]), stdin);
                nomes_cidades[i][j][strcspn(nomes_cidades[i][j], "\n")] = '\0';
                if (strlen(nomes_cidades[i][j]) > 0) {
                    break;
                } else {
                    printf("Erro: O nome da cidade não pode ser vazio. Tente novamente.\n");
                }
            }

            while (1) {
                printf("  População: ");
                if (scanf("%lu", &populacoes[i][j]) == 1 && populacoes[i][j] >= 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: A população não pode ser negativa ou não numérica. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            while (1) {
                printf("  Área (em km²): ");
                if (scanf("%f", &areas[i][j]) == 1 && areas[i][j] > 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: A área deve ser um número positivo. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            while (1) {
                printf("  PIB: ");
                if (scanf("%f", &pibs[i][j]) == 1 && pibs[i][j] >= 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: O PIB deve ser um número válido e não negativo. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            while (1) {
                printf("  Número de pontos turísticos: ");
                if (scanf("%d", &pontos_turisticos[i][j]) == 1 && pontos_turisticos[i][j] >= 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: O número de pontos turísticos não pode ser negativo ou não numérico. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            printf("Cidade %s cadastrada com sucesso!\n\n", codigo);
        }
    }

    for (int i = 0; i < NUM_ESTADOS; i++) {
        for (int j = 0; j < NUM_CIDADES; j++) {
            char codigo[5];
            sprintf(codigo, "%c%02d", estados[i], j + 1);

            char populacao_formatada[50], area_formatada[50], pib_formatado[50], super_poder_formatado[50];
            formatar_numero_inteiro(populacao_formatada, populacoes[i][j]);
            formatar_numero_inteiro(area_formatada, (unsigned long int)areas[i][j]);
            formatar_pib(pib_formatado, pibs[i][j]);

            float densidade = calcular_densidade_populacional(populacoes[i][j], areas[i][j]);
            float pib_per_capita = calcular_pib_per_capita(pibs[i][j], populacoes[i][j]);

            float super_poder = calcular_super_poder(pibs[i][j], populacoes[i][j], areas[i][j], pontos_turisticos[i][j], densidade, pib_per_capita);

            printf("Código: %s\n", codigo);
            printf("Nome da Cidade: %s\n", nomes_cidades[i][j]);
            printf("População: %s habitantes\n", populacao_formatada);
            printf("Área: %s km²\n", area_formatada);
            printf("PIB: %s\n", pib_formatado);
            printf("Pontos turísticos: %d\n", pontos_turisticos[i][j]);

            printf("Densidade Populacional: ");
            formatar_densidade_populacional(populacao_formatada, densidade);
            printf("%s habitantes/km²\n", populacao_formatada);

            printf("PIB per Capita: ");
            formatar_pib_per_capita(populacao_formatada, pib_per_capita);
            printf("R$ %s por habitante\n", populacao_formatada);

            printf("Super Poder: ");
            formatar_super_poder(super_poder_formatado, super_poder);
            printf("%s\n", super_poder_formatado);

            printf("-------------------------\n");
        }
    }

    printf("Fim do programa.\n");
    return 0;
}
