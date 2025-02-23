#include <stdio.h>

typedef struct {
    char estado[30], cidade[30];
    char codigo[10];  // Código como string (ex: "P01")
    int populacao, pontos_turisticos;
    float area, pib;
} Carta;

int main() {
    Carta cartas[2];

    // Entrada de dados das cartas
    for (int i = 0; i < 2; i++) {
        printf("\n--- Digite os dados da carta %d ---\n", i + 1);
        
        printf("Código (ex: P01, C01): ");
        scanf("%s", cartas[i].codigo);
        
        printf("Estado: ");
        scanf(" %[^\n]", cartas[i].estado);
        
        printf("Cidade (Capital): ");
        scanf(" %[^\n]", cartas[i].cidade);
        
        printf("População: ");
        scanf("%d", &cartas[i].populacao);
        
        printf("Área (km²): ");
        scanf("%f", &cartas[i].area);
        
        printf("PIB (bilhões): ");
        scanf("%f", &cartas[i].pib);
        
        printf("Número de pontos turísticos: ");
        scanf("%d", &cartas[i].pontos_turisticos);
    }

    // Exibir todas as cartas cadastradas
    printf("\n--- Cartas cadastradas ---\n");
    for (int i = 0; i < 2; i++) {
        printf("\n--- Carta %d ---\n", i + 1);
        printf("Código: %s\n", cartas[i].codigo);
        printf("Estado: %s\n", cartas[i].estado);
        printf("Cidade (Capital): %s\n", cartas[i].cidade);
        printf("População: %d\n", cartas[i].populacao);
        printf("Área: %.2f km²\n", cartas[i].area);
        printf("PIB: R$ %.2f bilhões\n", cartas[i].pib);
        printf("Pontos turísticos: %d\n", cartas[i].pontos_turisticos);
    }

    return 0;
}
