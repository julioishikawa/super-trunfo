#include <stdio.h>
#include <string.h>
#include "cartas.h"
#include "utilidades.h"

char estados[] = "ABCDEFGH";

void cadastrar_cartas(unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES],
                      float areas[NUM_ESTADOS][NUM_CIDADES],
                      float pibs[NUM_ESTADOS][NUM_CIDADES],
                      int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES],
                      char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50])
{
    printf("\nVoce cadastrara as cidades para cada estado.\n");
    printf("Nao utilize pontos/virgulas, utilize apenas numeros.\n");

    for (int estado = 0; estado < NUM_ESTADOS; estado++) {
        for (int cidade = 0; cidade < NUM_CIDADES; cidade++) {
            printf("\nDigite os dados para a cidade %d do estado %c:\n", cidade + 1, estados[estado]);
            
            // Recebe o nome da cidade
            while (1) {
                printf("Nome da cidade: ");
                fgets(nomes_cidades[estado][cidade], 50, stdin);
                nomes_cidades[estado][cidade][strcspn(nomes_cidades[estado][cidade], "\n")] = '\0'; // Remove o newline
                
                if (strlen(nomes_cidades[estado][cidade]) > 0) {
                    break;
                } else {
                    printf("Erro: O nome da cidade nao pode ser vazio. Tente novamente.\n");
                }
            }

            // Recebe a população
            while (1) {
                printf("Populacao: ");
                if (scanf("%lu", &populacoes[estado][cidade]) == 1 && populacoes[estado][cidade] >= 0) {
                    limpar_buffer(); // Limpa o buffer após a entrada
                    break;
                } else {
                    printf("Erro: A populacao deve ser um numero valido e nao negativo. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            // Recebe a área
            while (1) {
                printf("Area (em km2): ");
                if (scanf("%f", &areas[estado][cidade]) == 1 && areas[estado][cidade] > 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: A area deve ser um numero positivo. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            // Recebe o PIB
            while (1) {
                printf("PIB: ");
                if (scanf("%f", &pibs[estado][cidade]) == 1 && pibs[estado][cidade] >= 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: O PIB deve ser um numero valido e nao negativo. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            // Recebe os pontos turísticos
            while (1) {
                printf("Pontos turisticos: ");
                if (scanf("%d", &pontos_turisticos[estado][cidade]) == 1 && pontos_turisticos[estado][cidade] >= 0) {
                    limpar_buffer();
                    break;
                } else {
                    printf("Erro: O numero de pontos turisticos nao pode ser negativo ou nao numerico. Tente novamente.\n");
                    limpar_buffer();
                }
            }

            printf("\nCidade %s cadastrada com sucesso!\n", nomes_cidades[estado][cidade]);
        }
    }

    // Espera que o usuário pressione ENTER para retornar ao menu
    printf("\nCadastro de cartas concluido!\nPressione ENTER para voltar ao menu...\n");
    getchar();  // Captura o ENTER que o usuário pressiona
}

void ver_cartas_cadastradas(char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50],
                            unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES],
                            float areas[NUM_ESTADOS][NUM_CIDADES],
                            float pibs[NUM_ESTADOS][NUM_CIDADES],
                            int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES])
{
    printf("\nVisualizando as cartas cadastradas...\n");

    char formato_numero[50]; // Para armazenar os números formatados

    for (int estado = 0; estado < NUM_ESTADOS; estado++) {
        printf("\nEstado: %c\n", estados[estado]);
        for (int cidade = 0; cidade < NUM_CIDADES; cidade++) {
            printf("\nCidade %d:\n", cidade + 1);
            printf("Nome: %s\n", nomes_cidades[estado][cidade]);

            // Formatar e exibir a população
            formatar_numero_inteiro(formato_numero, populacoes[estado][cidade]);
            printf("Populacao: %s habitantes\n", formato_numero);

            // Formatar e exibir a área
            formatar_numero_flutuante(formato_numero, areas[estado][cidade]);
            printf("Area: %s km2\n", formato_numero);

            // Formatar e exibir o PIB
            formatar_pib(formato_numero, pibs[estado][cidade]);
            printf("PIB: %s\n", formato_numero);

            // Exibir os pontos turísticos
            printf("Pontos turisticos: %d\n", pontos_turisticos[estado][cidade]);

            // Calcular densidade populacional, PIB per capita e super poder
            float densidade = calcular_densidade_populacional(populacoes[estado][cidade], areas[estado][cidade]);
            float pib_per_capita = calcular_pib_per_capita(pibs[estado][cidade], populacoes[estado][cidade]);
            float super_poder = calcular_super_poder(pibs[estado][cidade], populacoes[estado][cidade], areas[estado][cidade],
                                                    pontos_turisticos[estado][cidade], densidade, pib_per_capita);

            // Formatar e exibir a densidade populacional
            formatar_densidade_populacional(formato_numero, densidade);
            printf("Densidade Populacional: %s habitantes/km2\n", formato_numero);

            // Formatar e exibir o PIB per capita
            formatar_pib_per_capita(formato_numero, pib_per_capita);
            printf("PIB per Capita: R$ %s por habitante\n", formato_numero);

            // Formatar e exibir o super poder
            formatar_super_poder(formato_numero, super_poder);
            printf("Super Poder: %s\n", formato_numero);

            printf("-------------------------\n");
        }
    }

    // Espera o usuário pressionar ENTER para voltar ao menu
    printf("\nPressione ENTER para voltar ao menu...\n");
    getchar();  // Captura o ENTER que o usuário pressiona
}

void comparar_cartas(int estado1, int estado2, int cidade1, int cidade2, int propriedade,
                     unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES],
                     float areas[NUM_ESTADOS][NUM_CIDADES],
                     float pibs[NUM_ESTADOS][NUM_CIDADES],
                     int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES],
                     char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50])
{
    float valor1, valor2;
    char resultado1[50], resultado2[50];
    char *propriedade_str;
    char *simbolo_comparacao;  // Ponteiro para armazenar o símbolo de comparação

    // Coleta os valores das cidades com base na propriedade escolhida
    switch (propriedade) {
        case 1:  // População
            valor1 = populacoes[estado1][cidade1];
            valor2 = populacoes[estado2][cidade2];
            propriedade_str = "Populacao";
            formatar_numero_inteiro(resultado1, valor1);
            formatar_numero_inteiro(resultado2, valor2);
            break;
        case 2:  // Área
            valor1 = areas[estado1][cidade1];
            valor2 = areas[estado2][cidade2];
            propriedade_str = "Area";
            formatar_numero_flutuante(resultado1, valor1);
            formatar_numero_flutuante(resultado2, valor2);
            break;
        case 3:  // PIB
            valor1 = pibs[estado1][cidade1];
            valor2 = pibs[estado2][cidade2];
            propriedade_str = "PIB";
            formatar_pib(resultado1, valor1);
            formatar_pib(resultado2, valor2);
            break;
        case 4:  // Densidade populacional
            valor1 = calcular_densidade_populacional(populacoes[estado1][cidade1], areas[estado1][cidade1]);
            valor2 = calcular_densidade_populacional(populacoes[estado2][cidade2], areas[estado2][cidade2]);
            propriedade_str = "Densidade Populacional";
            formatar_densidade_populacional(resultado1, valor1);
            formatar_densidade_populacional(resultado2, valor2);
            break;
        case 5:  // PIB per capita
            valor1 = calcular_pib_per_capita(pibs[estado1][cidade1], populacoes[estado1][cidade1]);
            valor2 = calcular_pib_per_capita(pibs[estado2][cidade2], populacoes[estado2][cidade2]);
            propriedade_str = "PIB per Capita";
            formatar_pib_per_capita(resultado1, valor1);
            formatar_pib_per_capita(resultado2, valor2);
            break;
        case 6:  // Pontos turísticos
            valor1 = pontos_turisticos[estado1][cidade1];
            valor2 = pontos_turisticos[estado2][cidade2];
            propriedade_str = "Pontos Turisticos";
            formatar_numero_inteiro(resultado1, valor1);
            formatar_numero_inteiro(resultado2, valor2);
            break;
        case 7:  // Super Poder
            valor1 = calcular_super_poder(pibs[estado1][cidade1], populacoes[estado1][cidade1], areas[estado1][cidade1],
                                          pontos_turisticos[estado1][cidade1],
                                          calcular_densidade_populacional(populacoes[estado1][cidade1], areas[estado1][cidade1]),
                                          calcular_pib_per_capita(pibs[estado1][cidade1], populacoes[estado1][cidade1]));
            valor2 = calcular_super_poder(pibs[estado2][cidade2], populacoes[estado2][cidade2], areas[estado2][cidade2],
                                          pontos_turisticos[estado2][cidade2],
                                          calcular_densidade_populacional(populacoes[estado2][cidade2], areas[estado2][cidade2]),
                                          calcular_pib_per_capita(pibs[estado2][cidade2], populacoes[estado2][cidade2]));
            propriedade_str = "Super Poder";
            formatar_super_poder(resultado1, valor1);
            formatar_super_poder(resultado2, valor2);
            break;
        default:
            printf("Propriedade invalida!\n");
            return;
    }

    // Exibe a comparação
    printf("\nComparando %s:\n", propriedade_str);

    if (valor1 == valor2) {
        if (propriedade == 4) {
            printf("Empate! Ambas as cidades têm a mesma densidade populacional.\n");
        } else {
            printf("Empate! Ambas as cidades tem o mesmo valor para %s.\n", propriedade_str);
        }
    } else {
        // Define o símbolo de comparação com base na propriedade
        simbolo_comparacao = (propriedade == 4)
                             ? (valor1 < valor2 ? "<" : ">")
                             : (valor1 > valor2 ? ">" : "<");

        // Exibe a comparação dos resultados
        printf("(%s) %s <-> %s (%s)\n",
               nomes_cidades[estado1][cidade1],
               resultado1,
               resultado2,
               nomes_cidades[estado2][cidade2]);
        printf("%s %s %s\n", resultado1, simbolo_comparacao, resultado2);

        // Determina o vencedor utilizando operadores ternários aninhados
        printf("%s venceu! (%s)\n",
               (propriedade == 4)
                   ? (valor1 < valor2 ? nomes_cidades[estado1][cidade1] : nomes_cidades[estado2][cidade2])
                   : (valor1 > valor2 ? nomes_cidades[estado1][cidade1] : nomes_cidades[estado2][cidade2]),
               (propriedade == 4) ? "Menor densidade populacional" : "Maior valor");
    }

    // Aguarda o usuário pressionar ENTER para continuar
    printf("\nPressione ENTER para continuar...");
    limpar_buffer();
    getchar();
}

void exibir_menu_comparacao(unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES],
                             float areas[NUM_ESTADOS][NUM_CIDADES],
                             float pibs[NUM_ESTADOS][NUM_CIDADES],
                             int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES],
                             char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50])
{
    int estado1, estado2, cidade1, cidade2, propriedade;

    // Exibe os estados cadastrados
    printf("\nEscolha os estados para comparar:\n");
    for (int i = 0; i < NUM_ESTADOS; i++) {
        printf("%d. Estado %c (", i + 1, estados[i]);
        for (int cidade = 0; cidade < NUM_CIDADES; cidade++) {
            printf("%s", nomes_cidades[i][cidade]);
            if (cidade < NUM_CIDADES - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    // Escolhe o primeiro estado com verificação
    do {
        printf("\nDigite o numero do primeiro estado: ");
        scanf("%d", &estado1);
        estado1--;  // Ajusta para índice 0

        if (estado1 < 0 || estado1 >= NUM_ESTADOS) {
            printf("Erro: Estado invalido. Tente novamente.\n");
        }
    } while (estado1 < 0 || estado1 >= NUM_ESTADOS);

    // Escolhe o segundo estado com verificação
    do {
        printf("Digite o numero do segundo estado: ");
        scanf("%d", &estado2);
        estado2--;  // Ajusta para índice 0

        if (estado2 < 0 || estado2 >= NUM_ESTADOS) {
            printf("Erro: Estado invalido. Tente novamente.\n");
        }
    } while (estado2 < 0 || estado2 >= NUM_ESTADOS);

    // Exibe as cidades dos estados escolhidos
    printf("\nEscolha as cidades dos estados %c e %c para comparar:\n", estados[estado1], estados[estado2]);

    // Exibe as cidades do primeiro estado
    printf("\nCidades do estado %c:\n", estados[estado1]);
    for (int cidade = 0; cidade < NUM_CIDADES; cidade++) {
        printf("%d. %s\n", cidade + 1, nomes_cidades[estado1][cidade]);
    }

    // Exibe as cidades do segundo estado
    printf("\nCidades do estado %c:\n", estados[estado2]);
    for (int cidade = 0; cidade < NUM_CIDADES; cidade++) {
        printf("%d. %s\n", cidade + 1, nomes_cidades[estado2][cidade]);
    }

    // Escolhe a primeira cidade com verificação
    do {
        printf("\nDigite o numero da primeira cidade (do estado %c): ", estados[estado1]);
        scanf("%d", &cidade1);
        cidade1--;  // Ajusta para índice 0

        if (cidade1 < 0 || cidade1 >= NUM_CIDADES) {
            printf("Erro: Cidade invalida. Tente novamente.\n");
        }
    } while (cidade1 < 0 || cidade1 >= NUM_CIDADES);

    // Escolhe a segunda cidade com verificação
    do {
        printf("Digite o numero da segunda cidade (do estado %c): ", estados[estado2]);
        scanf("%d", &cidade2);
        cidade2--;  // Ajusta para índice 0

        if (cidade2 < 0 || cidade2 >= NUM_CIDADES) {
            printf("Erro: Cidade invalida. Tente novamente.\n");
        }
    } while (cidade2 < 0 || cidade2 >= NUM_CIDADES);

    // Exibe as propriedades para comparação
    printf("\nEscolha a propriedade para comparacao:\n");
    printf("1. Populacao\n");
    printf("2. Area\n");
    printf("3. PIB\n");
    printf("4. Densidade Populacional\n");
    printf("5. PIB per Capita\n");
    printf("6. Pontos Turisticos\n");
    printf("7. Super Poder\n");

    // Escolhe a propriedade com verificação
    do {
        printf("\nDigite o numero da propriedade: ");
        scanf("%d", &propriedade);

        if (propriedade < 1 || propriedade > 7) {
            printf("Erro: Propriedade invalida. Tente novamente.\n");
        }
    } while (propriedade < 1 || propriedade > 7);

    // Chama a função de comparação
    comparar_cartas(estado1, estado2, cidade1, cidade2, propriedade,
                    populacoes, areas, pibs, pontos_turisticos, nomes_cidades);
}

void exibir_menu()
{
    printf("Bem-vindo ao sistema de cadastro de cartas do Super Trunfo - Tema: Paises\n");
    printf("\n1. Cadastrar Cartas\n");
    printf("2. Ver Cartas Cadastradas\n");
    printf("3. Comparar Cartas\n\n");
    printf("Escolha uma opcao: \n");
}
