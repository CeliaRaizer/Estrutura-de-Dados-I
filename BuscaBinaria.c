#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int cod;       
    char nome[50];  
    float preco;    
} Produto;

//armazena o resultado da busca
typedef struct { 
    int *posicoes; 
    int tamanho;    //quantidade de produtos encontrados
} ResultadoBusca;

// Função de comparação (qsort) 
int compara(const void *a, const void *b) {
    Produto *produtoA = (Produto *)a;
    Produto *produtoB = (Produto *)b;
    return strcmp(produtoA->nome, produtoB->nome);
}

ResultadoBusca busca_binaria(Produto lista[], int tamanho, char chave[]) {
    ResultadoBusca resultado;
    resultado.posicoes = NULL;  
    resultado.tamanho = 0;      // nenhuma posição encontrada

    int inicio = 0;         //indice inicial da busca
    int fim = tamanho - 1;  //indice final da busca

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;  //indice do meio
        int comparacao = strcmp(lista[meio].nome, chave);  //comparando a chave com o elemento do meio

        if (comparacao == 0) {  // se o produto foi encontrado
            resultado.tamanho++;  // incrementa o tamanho do resultado
            int *temp = (int*)realloc(resultado.posicoes, resultado.tamanho * sizeof(int));//realoca memoria
            if (temp == NULL) {//erro de alocação  
                free(resultado.posicoes);
                resultado.posicoes = NULL;
                resultado.tamanho = 0;
                printf("Erro ao alocar memória para as posições.\n");
                return resultado;
            }
            resultado.posicoes = temp;
            resultado.posicoes[resultado.tamanho - 1] = meio;  // armazena a posição do produto encontrado

            // Busca para a esquerda 
            int esquerda = meio - 1;
            while (esquerda >= inicio && strcmp(lista[esquerda].nome, chave) == 0) {
                resultado.tamanho++;
                temp = (int*)realloc(resultado.posicoes, resultado.tamanho * sizeof(int));  // realoca mais memoria
                if (temp == NULL) {  //erro de alocação
                    free(resultado.posicoes);
                    resultado.posicoes = NULL;
                    resultado.tamanho = 0;
                    printf("Erro ao alocar memoria para as posições.\n");
                    return resultado;
                }
                resultado.posicoes = temp;
                resultado.posicoes[resultado.tamanho - 1] = esquerda;  // armazena a posição encontrada
                esquerda--;
            }

            // Busca para a direita 
            int direita = meio + 1;
            while (direita <= fim && strcmp(lista[direita].nome, chave) == 0) {
                resultado.tamanho++;
                temp = (int*)realloc(resultado.posicoes, resultado.tamanho * sizeof(int));  // realoca mais memória
                if (temp == NULL) {  //erro de alocação
                    free(resultado.posicoes);
                    resultado.posicoes = NULL;
                    resultado.tamanho = 0;
                    printf("Erro ao alocar memoria para as posições.\n");
                    return resultado;
                }
                resultado.posicoes = temp;
                resultado.posicoes[resultado.tamanho - 1] = direita;  // armazena a posição encontrada
                direita++;
            }

            return resultado;  // retorna resultado se encontrar o produto
        }
        if (comparacao > 0) {
            fim = meio - 1;  // ajusta fim se o nome procurado for menor que o do meio
        } else {
            inicio = meio + 1;  // ajusta início se o nome procurado for maior que o do meio
        }
    }

    return resultado; 
}

void liberar_resultado(ResultadoBusca *resultado) {
    free(resultado->posicoes);
    resultado->posicoes = NULL;
    resultado->tamanho = 0;
}

void remover_produto(Produto lista[], int *tamanho, int indice) {
    if (indice < 0 || indice >= *tamanho) {
        printf("indice invalido.\n");
        return;
    }
    //ajusta indice
    for (int i = indice; i < (*tamanho) - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*tamanho)--;  // diminui o tamanho da lista
    printf("Produto removido com sucesso!\n");
}

int main() {
    int opc;  
    int tamanho = 0; 
    int capacidade = 5; 
    Produto *produtos = (Produto *)malloc(capacidade * sizeof(Produto));  //alocação de memória

    for (;;) {  
        printf("\nQual opcao deseja realizar?:\n");
        printf("1- Cadastrar produto\n");
        printf("2- Buscar produto\n");
        printf("3- Consultar todos os produtos\n");
        printf("4- Remover produto\n");
        printf("5- Sair \n");
        scanf("%d", &opc);  
        
        if (opc == 5) { 
        	free(produtos); 
            break;
        } else if (opc == 1) { 
            if (tamanho >= capacidade) {  // verifica se e necessário aumentar a capacidade
                capacidade *= 2;
                produtos = (Produto *)realloc(produtos, capacidade * sizeof(Produto));  // realoca memória
            }
            
            printf("Qual o codigo do produto?: ");
            scanf("%d", &produtos[tamanho].cod);  
            printf("Qual o nome do produto?: ");
            scanf("%49s", produtos[tamanho].nome);
            printf("Qual o preco do produto?: ");
            scanf("%f", &produtos[tamanho].preco); 
            tamanho++;
            
            qsort(produtos, tamanho, sizeof(Produto), compara);  // ordena a lista de produtos pelo nome
            printf("Produto cadastrado com sucesso!\n");

        } else if (opc == 2) {  
            char chave[50];
            printf("Digite o nome do produto a ser buscado: ");
            scanf("%s", chave);
            ResultadoBusca resultado = busca_binaria(produtos, tamanho, chave);  // realiza busca binária
            
            if (resultado.tamanho > 0) {
                printf("Produto(s) encontrado(s) nas posicoes:\n");
                for (int i = 0; i < resultado.tamanho; i++) {
                    printf("Posicao: %d, Cod: %d, Nome: %s, Preco: %.2f\n",
                           resultado.posicoes[i], 
                           produtos[resultado.posicoes[i]].cod,
                           produtos[resultado.posicoes[i]].nome,
                           produtos[resultado.posicoes[i]].preco);  // exibe produtos encontrados
                }
            } else {
                printf("Produto nao encontrado.\n");
            }

            liberar_resultado(&resultado);  // libera memória alocada para o resultado

        } else if (opc == 3) {  // consultar todos os produtos cadastrados
            printf("Lista de Produtos:\n");
            for (int i = 0; i < tamanho; i++) {
                printf("Cod: %d, Nome: %s, Preco: %.2f\n", produtos[i].cod, produtos[i].nome, produtos[i].preco); 
            }

        } else if (opc == 4) {  
            char chave[50];
            printf("Digite o nome do produto a ser removido: ");
            scanf("%s", chave);
            ResultadoBusca resultado = busca_binaria(produtos, tamanho, chave);  
            
            if (resultado.tamanho > 0) {
                int indice = resultado.posicoes[0];  // usa a primeira posição encontrada para remover
                remover_produto(produtos, &tamanho, indice);  
            } else {
                printf("Produto nao encontrado para remocao.\n");
            }

            liberar_resultado(&resultado);  // libera memória alocada para o resultado
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

  
    return 0;
}
