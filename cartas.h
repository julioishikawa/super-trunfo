#ifndef CARTAS_H
#define CARTAS_H

#define NUM_ESTADOS 8
#define NUM_CIDADES 4

extern char estados[];

void cadastrar_cartas(unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES], float areas[NUM_ESTADOS][NUM_CIDADES],
                      float pibs[NUM_ESTADOS][NUM_CIDADES], int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES],
                      char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50]);
void ver_cartas_cadastradas(char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50], unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES], 
                             float areas[NUM_ESTADOS][NUM_CIDADES], float pibs[NUM_ESTADOS][NUM_CIDADES], 
                             int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES]);
void comparar_cartas(int estado1, int estado2,int cidade1, int cidade2, int propriedade, unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES], 
                     float areas[NUM_ESTADOS][NUM_CIDADES], float pibs[NUM_ESTADOS][NUM_CIDADES], 
                     int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES], char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50]);
void exibir_menu_comparacao(unsigned long int populacoes[NUM_ESTADOS][NUM_CIDADES], float areas[NUM_ESTADOS][NUM_CIDADES],
                             float pibs[NUM_ESTADOS][NUM_CIDADES], int pontos_turisticos[NUM_ESTADOS][NUM_CIDADES], 
                             char nomes_cidades[NUM_ESTADOS][NUM_CIDADES][50]);
void exibir_menu();

#endif // CARTAS_H
