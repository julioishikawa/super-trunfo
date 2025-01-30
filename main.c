#include <stdio.h>
#include <string.h>
#include "cartas.h"
#include "utilidades.h"

int main() {
    unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES];
    float areas[NUM_ESTADOS][NUM_CIDADES];
    float pibs[NUM_ESTADOS][NUM_CIDADES];
    int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES];
    char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50];
    
    int escolha;
    int sair = 0;
    
    while (!sair) {
        exibir_menu();

        // Agora usamos getchar() para capturar a tecla
        escolha = getchar();  // Captura um único caractere, sem o risco do ENTER causar problemas
        limpar_buffer();  // Limpa o buffer após a captura
        switch (escolha) {
            case '1': 
                cadastrar_cartas(populacoes, areas, pibs, pontos_turisticos, nomes_cidades);
                break;
            case '2':
                ver_cartas_cadastradas(nomes_cidades, populacoes, areas, pibs, pontos_turisticos);
                break;
            case '3':
                exibir_menu_comparacao(populacoes, areas, pibs, pontos_turisticos, nomes_cidades);
                break;
            default:
                printf("Opcao inválida. Tente novamente.\n");
                break;
        }
    }
    return 0;
}