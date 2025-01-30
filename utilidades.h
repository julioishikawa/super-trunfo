#ifndef UTILIDADES_H
#define UTILIDADES_H

void limpar_buffer();
void formatar_numero_inteiro(char *resultado, unsigned long int numero);
void formatar_numero_flutuante(char *resultado, float numero);
void formatar_densidade_populacional(char *resultado, float densidade);
void formatar_pib_per_capita(char *resultado, float pib_per_capita);
void formatar_pib(char *resultado, float pib);
void formatar_super_poder(char *resultado, float super_poder);
float calcular_densidade_populacional(unsigned long int populacao, float area);
float calcular_pib_per_capita(float pib, unsigned long int populacao);
float calcular_super_poder(float pib, unsigned long int populacao, float area, int pontos_turisticos, float densidade, float pib_per_capita);

#endif // UTILIDADES_H
