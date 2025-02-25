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

    // Salvando os dados da carta no arquivo
    fprintf(arquivo, "%s %s %s %d %.2f %.2f %d %.2f %.2f\n",
            carta.codigo, carta.estado, carta.cidade,
            carta.populacao, carta.area, carta.pib, carta.pontos_turisticos,
            carta.densidade_populacional, carta.pib_per_capita);

    fclose(arquivo);
}

int carregarCartas(Carta cartas[], int *total_cartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhuma carta cadastrada ainda.\n");
        return 0;
    }

    *total_cartas = 0;

    printf("\n--- Cartas cadastradas ---\n");
    while (fscanf(arquivo, "%s %s %s %d %f %f %d %f %f",
                  cartas[*total_cartas].codigo, cartas[*total_cartas].estado, cartas[*total_cartas].cidade,
                  &cartas[*total_cartas].populacao, &cartas[*total_cartas].area, &cartas[*total_cartas].pib,
                  &cartas[*total_cartas].pontos_turisticos,
                  &cartas[*total_cartas].densidade_populacional, &cartas[*total_cartas].pib_per_capita) != EOF) {

        // Caso os cálculos não tenham sido feitos corretamente, recalcular
        if (cartas[*total_cartas].area > 0) {
            cartas[*total_cartas].densidade_populacional = cartas[*total_cartas].populacao / cartas[*total_cartas].area;
        }
        if (cartas[*total_cartas].populacao > 0) {
            cartas[*total_cartas].pib_per_capita = (cartas[*total_cartas].pib * 1000) / cartas[*total_cartas].populacao;
        }

        // Exibir os dados
        printf("\nCódigo: %s\nEstado: %s\nCidade: %s\nPopulação: %d\nÁrea: %.2f km²\nPIB: R$ %.2f bilhões\nPontos turísticos: %d\nDensidade Populacional: %.2f hab/km²\nPIB per capita: R$ %.2f mil\n",
               cartas[*total_cartas].codigo, cartas[*total_cartas].estado, cartas[*total_cartas].cidade,
               cartas[*total_cartas].populacao, cartas[*total_cartas].area, cartas[*total_cartas].pib,
               cartas[*total_cartas].pontos_turisticos,
               cartas[*total_cartas].densidade_populacional, cartas[*total_cartas].pib_per_capita);

        (*total_cartas)++;
    }
    fclose(arquivo);

    return *total_cartas;
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

    printf("\n--- Comparação entre as cartas ---\n");
    printf("\nCarta 1: %s (%s) - PIB per capita: R$ %.2f mil\n", carta1->cidade, carta1->estado, carta1->pib_per_capita);
    printf("Carta 2: %s (%s) - PIB per capita: R$ %.2f mil\n", carta2->cidade, carta2->estado, carta2->pib_per_capita);

    if (carta1->pib_per_capita > carta2->pib_per_capita) {
        printf("\n🏆 Vencedor: %s (%s) com PIB per capita de R$ %.2f mil!\n", carta1->cidade, carta1->estado, carta1->pib_per_capita);
        printf("\n📜 Carta vencedora:\n");
        printf("Código: %s\nEstado: %s\nCidade: %s\nPopulação: %d\nÁrea: %.2f km²\nPIB: R$ %.2f bilhões\nPontos turísticos: %d\nDensidade Populacional: %.2f hab/km²\nPIB per capita: R$ %.2f mil\n",
               carta1->codigo, carta1->estado, carta1->cidade,
               carta1->populacao, carta1->area, carta1->pib,
               carta1->pontos_turisticos,
               carta1->densidade_populacional, carta1->pib_per_capita);
    } else if (carta2->pib_per_capita > carta1->pib_per_capita) {
        printf("\n🏆 Vencedor: %s (%s) com PIB per capita de R$ %.2f mil!\n", carta2->cidade, carta2->estado, carta2->pib_per_capita);
        printf("\n📜 Carta vencedora:\n");
        printf("Código: %s\nEstado: %s\nCidade: %s\nPopulação: %d\nÁrea: %.2f km²\nPIB: R$ %.2f bilhões\nPontos turísticos: %d\nDensidade Populacional: %.2f hab/km²\nPIB per capita: R$ %.2f mil\n",
               carta2->codigo, carta2->estado, carta2->cidade,
               carta2->populacao, carta2->area, carta2->pib,
               carta2->pontos_turisticos,
               carta2->densidade_populacional, carta2->pib_per_capita);
    } else {
        printf("\n🤝 Empate! Ambas as cidades possuem o mesmo PIB per capita.\n");
    }
}

int main() {
    int opcao;
    Carta cartas[100];
    int total_cartas = 0;

    // Carregar cartas salvas e fazer cálculos
    carregarCartas(cartas, &total_cartas);

    printf("\nDeseja adicionar uma nova carta? (1 - Sim, 0 - Não): ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        Carta novaCarta;

        printf("\n--- Digite os dados da nova carta ---\n");

        printf("Código: ");
        scanf("%s", novaCarta.codigo);

        printf("Estado: ");
        scanf(" %[^\n]", novaCarta.estado);

        printf("Cidade (Capital): ");
        scanf(" %[^\n]", novaCarta.cidade);

        printf("População: ");
        scanf("%d", &novaCarta.populacao);

        printf("Área (km²): ");
        scanf("%f", &novaCarta.area);

        printf("PIB (bilhões): ");
        scanf("%f", &novaCarta.pib);

        printf("Número de pontos turísticos: ");
        scanf("%d", &novaCarta.pontos_turisticos);

        // Calculando a densidade populacional e PIB per capita
        novaCarta.densidade_populacional = novaCarta.populacao / novaCarta.area;
        novaCarta.pib_per_capita = (novaCarta.pib * 1000) / novaCarta.populacao;

        // Salvar a carta no arquivo
        salvarCarta(novaCarta, "a");

        // Carregar novamente todas as cartas, agora com a nova
        carregarCartas(cartas, &total_cartas);
    }

    // Comparar as cartas cadastradas
    compararCartas(cartas, total_cartas);

    return 0;
}