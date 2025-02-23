#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char estado[30], cidade[30];
    char codigo[10];
    int populacao, pontos_turisticos;
    float area, pib;
} Carta;

void salvarCarta(Carta carta) {
    FILE *arquivo = fopen("cartas.txt", "a"); // "a" adiciona novas cartas sem apagar as antigas
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    // Salvando os dados no arquivo
    fprintf(arquivo, "%s %s %s %d %.2f %.2f %d\n",
            carta.codigo, carta.estado, carta.cidade,
            carta.populacao, carta.area, carta.pib, carta.pontos_turisticos);

    fclose(arquivo);
}

void carregarCartas() {
    FILE *arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhuma carta cadastrada ainda.\n");
        return;
    }

    Carta carta;
    printf("\n--- Cartas cadastradas ---\n");
    while (fscanf(arquivo, "%s %s %s %d %f %f %d",
                  carta.codigo, carta.estado, carta.cidade,
                  &carta.populacao, &carta.area, &carta.pib, &carta.pontos_turisticos) != EOF) {
        printf("\nCódigo: %s\nEstado: %s\nCidade: %s\nPopulação: %d\nÁrea: %.2f km²\nPIB: R$ %.2f bilhões\nPontos turísticos: %d\n",
               carta.codigo, carta.estado, carta.cidade,
               carta.populacao, carta.area, carta.pib, carta.pontos_turisticos);
    }

    fclose(arquivo);
}

int main() {
    int opcao;
    Carta novaCarta;

    // Carregar cartas já salvas
    carregarCartas();

    printf("\nDeseja adicionar uma nova carta? (1 - Sim, 0 - Não): ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("\n--- Digite os dados da nova carta ---\n");

        printf("Código: ");
        scanf("%s", novaCarta.codigo);

        printf("Estado: ");
        scanf(" %[^\n]", novaCarta.estado);

        printf("Cidade: ");
        scanf(" %[^\n]", novaCarta.cidade);

        printf("População: ");
        scanf("%d", &novaCarta.populacao);

        printf("Área (km²): ");
        scanf("%f", &novaCarta.area);

        printf("PIB (bilhões): ");
        scanf("%f", &novaCarta.pib);

        printf("Número de pontos turísticos: ");
        scanf("%d", &novaCarta.pontos_turisticos);

        // Salvar a nova carta no arquivo
        salvarCarta(novaCarta);

        printf("\nCarta salva com sucesso!\n");

        // Reexibir todas as cartas atualizadas
        carregarCartas();
    } else {
        printf("\nNenhuma nova carta foi adicionada.\n");
    }

    return 0;
}
