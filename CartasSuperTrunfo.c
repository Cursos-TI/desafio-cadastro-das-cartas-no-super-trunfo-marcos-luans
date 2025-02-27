#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char estado[30], cidade[30];
    char codigo[10];
    int populacao, pontos_turisticos;
    float area, pib, densidade_populacional, pib_per_capita;
} Carta;

void salvarCarta(Carta carta, const char *modo) {
    FILE *arquivo = fopen("cartas.txt", modo);
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }
    
    fprintf(arquivo, "%s %s %s %d %.2f %.2f %d %.2f %.2f\n",
            carta.codigo, carta.estado, carta.cidade,
            carta.populacao, carta.area, carta.pib, carta.pontos_turisticos,
            carta.densidade_populacional, carta.pib_per_capita);
    
    fclose(arquivo);
}

int carregarCartas(Carta cartas[], int *total_cartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhuma carta cadastrada ainda.\n");
        return 0;
    }
    *total_cartas = 0;

    while (fscanf(arquivo, "%s %s %s %d %f %f %d %f %f",
                  cartas[*total_cartas].codigo, cartas[*total_cartas].estado, cartas[*total_cartas].cidade,
                  &cartas[*total_cartas].populacao, &cartas[*total_cartas].area, &cartas[*total_cartas].pib,
                  &cartas[*total_cartas].pontos_turisticos,
                  &cartas[*total_cartas].densidade_populacional, &cartas[*total_cartas].pib_per_capita) != EOF) {
        (*total_cartas)++;
    }
    fclose(arquivo);
    return *total_cartas;
}

// Função para mostrar todas as cartas carregadas
void mostrarCartas(Carta cartas[], int total_cartas) {
    if (total_cartas == 0) {
        printf("\nNão há cartas salvas para mostrar.\n");
        return;
    }

    printf("\n--- Cartas Salvas ---\n");
    for (int i = 0; i < total_cartas; i++) {
        printf("\nCódigo: %s\n", cartas[i].codigo);
        printf("Estado: %s\n", cartas[i].estado);
        printf("Cidade: %s\n", cartas[i].cidade);
        printf("População: %d\n", cartas[i].populacao);
        printf("Área: %.2f km²\n", cartas[i].area);
        printf("PIB: %.2f bilhões\n", cartas[i].pib);
        printf("Pontos turísticos: %d\n", cartas[i].pontos_turisticos);
        printf("Densidade populacional: %.2f habitantes/km²\n", cartas[i].densidade_populacional);
        printf("PIB per capita: %.2f\n", cartas[i].pib_per_capita);
        printf("\n-------------------------\n");
    }
}

void compararCartas(Carta cartas[], int total_cartas) {
    if (total_cartas < 2) {
        printf("\nÉ necessário ter pelo menos duas cartas cadastradas para comparar.\n");
        return;
    }

    char cod1[10], cod2[10];
    Carta *carta1 = NULL, *carta2 = NULL;

    printf("\nDigite o código da primeira carta: ");
    scanf("%s", cod1);
    printf("Digite o código da segunda carta: ");
    scanf("%s", cod2);

    for (int i = 0; i < total_cartas; i++) {
        if (strcmp(cartas[i].codigo, cod1) == 0) {
            carta1 = &cartas[i];
        }
        if (strcmp(cartas[i].codigo, cod2) == 0) {
            carta2 = &cartas[i];
        }
    }

    if (carta1 == NULL || carta2 == NULL) {
        printf("\nUma ou ambas as cartas não foram encontradas! Verifique os códigos e tente novamente.\n");
        return;
    }

    int opcao;
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos turísticos\n5 - Densidade Demográfica (Menor vence)\n");
    scanf("%d", &opcao);

    float valor1, valor2;
    int inverso = 0;
    char atributo[50];

    switch (opcao) {
        case 1:
            valor1 = carta1->populacao;
            valor2 = carta2->populacao;
            strcpy(atributo, "População");
            break;
        case 2:
            valor1 = carta1->area;
            valor2 = carta2->area;
            strcpy(atributo, "Área");
            break;
        case 3:
            valor1 = carta1->pib;
            valor2 = carta2->pib;
            strcpy(atributo, "PIB");
            break;
        case 4:
            valor1 = carta1->pontos_turisticos;
            valor2 = carta2->pontos_turisticos;
            strcpy(atributo, "Pontos Turísticos");
            break;
        case 5:
            valor1 = carta1->densidade_populacional;
            valor2 = carta2->densidade_populacional;
            strcpy(atributo, "Densidade Demográfica");
            inverso = 1;
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    printf("\n--- Comparação de %s ---\n", atributo);
    printf("%s (%s) - %.2f\n", carta1->cidade, carta1->estado, valor1);
    printf("%s (%s) - %.2f\n", carta2->cidade, carta2->estado, valor2);

    if (valor1 == valor2) {
        printf("\n🤝 Empate! Ambas as cartas possuem o mesmo valor para %s.\n", atributo);
    } else if ((valor1 > valor2 && !inverso) || (valor1 < valor2 && inverso)) {
        printf("\n🏆 Vencedor: %s (%s)\n", carta1->cidade, carta1->estado);
    } else {
        printf("\n🏆 Vencedor: %s (%s)\n", carta2->cidade, carta2->estado);
    }
}

int main() {
    Carta cartas[100];
    int total_cartas = 0;
    carregarCartas(cartas, &total_cartas);
    
    // Mostrar cartas salvas
    mostrarCartas(cartas, total_cartas);

    // Comparar cartas
    compararCartas(cartas, total_cartas);

    return 0;
}