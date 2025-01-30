#include <stdio.h>
#include <string.h>
#include <math.h>
#include "utilidades.h"

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
    if (densidade >= 1) {
        unsigned long int densidade_inteira = (unsigned long int)(densidade + 0.5);
        formatar_numero_inteiro(resultado, densidade_inteira);
    } else {
        if (densidade == 0) {
            sprintf(resultado, "0");
        } else {
            int casas_decimais = (int) ceil(-log10(densidade)) + 1;
            char formato[10];
            sprintf(formato, "%%.%df", casas_decimais);
            sprintf(resultado, formato, densidade);
        }
    }
}

void formatar_pib_per_capita(char *resultado, float pib_per_capita) {
    formatar_numero_flutuante(resultado, pib_per_capita);
}

void formatar_pib(char *resultado, float pib) {
    char buffer[50];

    if (pib >= 1000000000000) {
        pib /= 1000000000000;
        sprintf(buffer, "%.2f trilhoes", pib);
    } else if (pib >= 1000000000) {
        pib /= 1000000000;
        sprintf(buffer, "%.2f bilhoes", pib);
    } else if (pib >= 1000000) {
        pib /= 1000000;
        sprintf(buffer, "%.2f milhoes", pib);
    } else {
        int pib_inteiro = (int)pib;
        formatar_numero_inteiro(buffer, pib_inteiro);
    }

    strcpy(resultado, buffer);
}

void formatar_super_poder(char *resultado, float super_poder) {
    sprintf(resultado, "%.0f", super_poder);  
    int len = strlen(resultado);
    int pos = 0, contador = 0;

    char buffer[50];
    for (int i = len - 1; i >= 0; i--) {
        buffer[pos++] = resultado[i];
        contador++;
        if (contador % 3 == 0 && i > 0) {
            buffer[pos++] = '.';
        }
    }

    buffer[pos] = '\0';

    for (int i = 0; i < pos / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[pos - i - 1];
        buffer[pos - i - 1] = temp;
    }

    strcpy(resultado, buffer);
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
    super_poder += area / 1000;
    super_poder += pib;
    super_poder += pontos_turisticos;
    super_poder += densidade;
    super_poder += pib_per_capita;
    
    return super_poder;
}
