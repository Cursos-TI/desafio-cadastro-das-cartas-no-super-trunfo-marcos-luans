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

// Função para comparar os atributos
void compararAtributos(Carta *carta1, Carta *carta2, int atributo1, int atributo2) {
    float valor1_1, valor2_1, valor1_2, valor2_2;
    char atributo_nome1[50], atributo_nome2[50];
    int inverso1 = 0, inverso2 = 0;

    // Primeiro atributo
    switch (atributo1) {
        case 1:
            valor1_1 = carta1->populacao;
            valor2_1 = carta2->populacao;
            strcpy(atributo_nome1, "População");
            break;
        case 2:
            valor1_1 = carta1->area;
            valor2_1 = carta2->area;
            strcpy(atributo_nome1, "Área");
            break;
        case 3:
            valor1_1 = carta1->pib;
            valor2_1 = carta2->pib;
            strcpy(atributo_nome1, "PIB");
            break;
        case 4:
            valor1_1 = carta1->pontos_turisticos;
            valor2_1 = carta2->pontos_turisticos;
            strcpy(atributo_nome1, "Pontos Turísticos");
            break;
        case 5:
            valor1_1 = carta1->densidade_populacional;
            valor2_1 = carta2->densidade_populacional;
            strcpy(atributo_nome1, "Densidade Demográfica");
            inverso1 = 1;
            break;
        default:
            printf("Opção inválida para o primeiro atributo!\n");
            return;
    }

    // Segundo atributo
    switch (atributo2) {
        case 1:
            valor1_2 = carta1->populacao;
            valor2_2 = carta2->populacao;
            strcpy(atributo_nome2, "População");
            break;
        case 2:
            valor1_2 = carta1->area;
            valor2_2 = carta2->area;
            strcpy(atributo_nome2, "Área");
            break;
        case 3:
            valor1_2 = carta1->pib;
            valor2_2 = carta2->pib;
            strcpy(atributo_nome2, "PIB");
            break;
        case 4:
            valor1_2 = carta1->pontos_turisticos;
            valor2_2 = carta2->pontos_turisticos;
            strcpy(atributo_nome2, "Pontos Turísticos");
            break;
        case 5:
            valor1_2 = carta1->densidade_populacional;
            valor2_2 = carta2->densidade_populacional;
            strcpy(atributo_nome2, "Densidade Demográfica");
            inverso2 = 1;
            break;
        default:
            printf("Opção inválida para o segundo atributo!\n");
            return;
    }

    // Comparação dos dois atributos
    printf("\n--- Comparação entre %s e %s ---\n", atributo_nome1, atributo_nome2);
    printf("%s (%s): %.2f x %.2f (%s)\n", carta1->cidade, carta1->estado, valor1_1, valor2_1, carta2->cidade);
    printf("%s (%s): %.2f x %.2f (%s)\n", carta1->cidade, carta1->estado, valor1_2, valor2_2, carta2->cidade);

    // Resultado para o primeiro atributo
    printf("Resultado para %s: %s\n", atributo_nome1,
        (valor1_1 == valor2_1) ? "Empate" :
        ((valor1_1 > valor2_1 && !inverso1) || (valor1_1 < valor2_1 && inverso1)) ? carta1->cidade : carta2->cidade);

    // Resultado para o segundo atributo
    printf("Resultado para %s: %s\n", atributo_nome2,
        (valor1_2 == valor2_2) ? "Empate" :
        ((valor1_2 > valor2_2 && !inverso2) || (valor1_2 < valor2_2 && inverso2)) ? carta1->cidade : carta2->cidade);

    // Soma dos atributos
    float soma1 = valor1_1 + valor1_2;
    float soma2 = valor2_1 + valor2_2;
    printf("\n--- Soma dos Atributos ---\n");
    printf("Soma para %s (%s): %.2f\n", carta1->cidade, carta1->estado, soma1);
    printf("Soma para %s (%s): %.2f\n", carta2->cidade, carta2->estado, soma2);

    // Verificando o vencedor
    if (soma1 == soma2) {
        printf("\nEmpate na rodada!\n");
    } else {
        printf("\nVencedor da rodada: %s (%s)\n", (soma1 > soma2) ? carta1->cidade : carta2->cidade, (soma1 > soma2) ? carta1->estado : carta2->estado);
    }
}

int main() {
    Carta cartas[100];
    int total_cartas = 0;
    carregarCartas(cartas, &total_cartas);

    // Mostrar as cartas carregadas
    mostrarCartas(cartas, total_cartas);

    // Escolher as cartas para comparação
    if (total_cartas < 2) {
        printf("\nÉ necessário ter pelo menos duas cartas para comparar!\n");
        return 0;
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
        return 0;
    }

    // Escolher atributos para comparar
    int atributo1, atributo2;
    printf("\nEscolha o primeiro atributo para comparar:\n");
    printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos turísticos\n5 - Densidade Demográfica\n");
    scanf("%d", &atributo1);

    // Garantir que o segundo atributo seja diferente do primeiro
    do {
        printf("\nEscolha o segundo atributo para comparar (não pode ser o mesmo que o primeiro):\n");
        printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos turísticos\n5 - Densidade Demográfica\n");
        scanf("%d", &atributo2);
    } while (atributo2 == atributo1);

    compararAtributos(carta1, carta2, atributo1, atributo2);

    return 0;
}