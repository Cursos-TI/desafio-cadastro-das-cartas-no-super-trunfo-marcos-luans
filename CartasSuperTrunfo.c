#include <stdio.h>
    
 int main(){
    
    char estado[20];
    char codigo]20;
    char cidade[20];
    int populacao;
    float area;
    float pib;
    int pontos;

    printf("Digite o Estado: \n");
    scanf("%s", &estado);

    printf("Digite o Código: \n");
    scanf("%s", &codigo);

    printf("Digite a Cidade: \n");
    scanf("%s", &cidade);

    printf("Digite a População: \n");
    scanf("%d",  &populacao);

    printf("Digite a Área: \n");
    scanf("%d", &area);

    printf("Digite o PIB: \n");
    scanf("%d", &pib);

    printf("Digite quantos pontos turisticos tem: \n");
    scanf("%d", &pontos);

    printf("Carta 1")
    printf("Nome do estado: %s\n", &estado);
    printf("Cidade: %s\n", &cidade);
    printf("Codigo: %s\n", &codigo);
    printf("População: %d\n", &populacao);
    printf("Área: %d\n", &area);
    printf("PIB: %d\n", &pib);
    printf("Pontos turisticos: %d\n", &pontos);

    return 0;
   
}