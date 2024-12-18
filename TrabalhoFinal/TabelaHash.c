#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define M 53

typedef struct Node{
    char nome[100];
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Lista{
    struct Node *head;
    struct Node *tail;
    int size;
}Lista;

Lista* criaLista(){ //inicializar
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
    return lista;    
}

void inserir(Lista* lista, char nome[]){
    Node *novoNo = (Node*)malloc(sizeof(Node));
    strcpy(novoNo->nome, nome);
    novoNo->next = NULL;
    novoNo->prev = lista->tail;
    
    if(lista->tail != NULL){
        lista->tail->next = novoNo;
    }else{
        lista->head = novoNo;
    }
    lista->tail = novoNo;
    lista->size++;
}

void remover(Lista *lista, char nome[]){
    Node* atual = lista->head;
    
    while(atual != NULL && strcmp(atual->nome, nome)!=0){
        atual = atual->next;
    }
    
    if(atual == NULL){
        printf ("Nome %s nao encontrado na lista!\n",nome);
        return;
    }
    
    if(atual->prev != NULL){
        atual->prev->next =  atual->next;
    }else{
        lista->head = atual->next;
    }
    
    if (atual->next != NULL) {
        atual->next->prev = atual->prev;
    } else {
        lista->tail = atual->prev;
    }
    
    free(atual);
    lista->size--;
    printf("Nome %s removido com sucesso!\n", nome);
}

Node* buscar(Lista* lista, char nome[], int chave) {
    Node *atual = lista->head; 

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Nome %s encontrado na chave %d.\n", nome, chave);
            return atual;
        }
        atual = atual->next;
    }

    printf("Nome %s nao encontrado na lista.\n", nome); 
    return NULL;
}

typedef struct{
    Lista* tabela[M];
}TabelaHash;

TabelaHash* criarTabelaHash(){ //inicializa a tabela
    TabelaHash* tabelaHash = (TabelaHash*)malloc(sizeof(TabelaHash));
    for(int i=0; i<M; i++){
        tabelaHash->tabela[i] = criaLista();
    }
    return tabelaHash;
}

int funcaoHash(char nome[]) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % M;
}

void inserirTabelaHash(TabelaHash* tabelaHash, char nome[]){
    int indice = funcaoHash(nome);
    inserir(tabelaHash->tabela[indice], nome);
}

Node* buscarTabelaHash(TabelaHash* tabelaHash, char nome[]) {
    int indice = funcaoHash(nome);
    return buscar(tabelaHash->tabela[indice], nome, indice);
}

void removerTabelaHash(TabelaHash* tabelaHash, char nome[]) {
    int indice = funcaoHash(nome);
    remover(tabelaHash->tabela[indice], nome);
}

Node* ordenar(Node* baixo, Node* alto) {
    //pivo = nome do nó final (alto).
    char pivo[100];
    strcpy(pivo, alto->nome);

    Node* i = baixo->prev;

    // Percorre os nos da lista do inicio ao fim.
    for (Node* j = baixo; j != alto; j = j->next) {
        // Se o nome do no atual (j->nome) for menor ou igual ao pivo
        if (strcmp(j->nome, pivo) <= 0) {
            // Move o ponteiro i para o próximo nó 
            i = (i == NULL) ? baixo : i->next;

            char temp[100];
            strcpy(temp, i->nome);
            strcpy(i->nome, j->nome);
            strcpy(j->nome, temp);
        }
    }

    //coloca o pivo na posição correta na lista.
    i = (i == NULL) ? baixo : i->next;
    char temp[100];
    strcpy(temp, i->nome);
    strcpy(i->nome, alto->nome);
    strcpy(alto->nome, temp);

    return i;
}

void quickSortLista(Node* baixo, Node* alto) {
    if (alto != NULL && baixo != alto && baixo != alto->next) {
        Node* pivo = ordenar(baixo, alto);
        // Ordena a sublista a esquerda do pivo
        quickSortLista(baixo, pivo->prev);
        // Ordena a sublista a direita do pivo
        quickSortLista(pivo->next, alto);
    }
}

void ordenarTabelaHash(TabelaHash* tabelaHash) {
    for (int i = 0; i < M; i++) {
        if (tabelaHash->tabela[i]->head != NULL) {
            quickSortLista(tabelaHash->tabela[i]->head, tabelaHash->tabela[i]->tail);
        }
    }
}

void exibirQuantChave(TabelaHash* tabelaHash){
    for(int i=0; i<M; i++){
        int quantidade = tabelaHash->tabela[i]->size;
        printf("Chave %d: %d elementos\n",i, quantidade);
    }
}

void carregarNomes(TabelaHash* tabelaHash, const char* arquivoNomes){
    FILE* arquivo = fopen(arquivoNomes, "r"); //abre arquivo
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo %s\n",arquivoNomes);
        return;
    }   
    
    char nome[100];
    while(fgets(nome, sizeof(nome), arquivo)){
        nome[strcspn(nome, "\n")] = '\0'; //remover pular linha /n
        inserirTabelaHash(tabelaHash, nome);
    }
    
    fclose(arquivo);
    printf("Nomes carregados com sucesso do arquivo %s\n",arquivoNomes);
}

void imprimirNomesDaChave(TabelaHash* tabelaHash, int chave) {
    if (chave < 0 || chave >= M) {
        printf("Chave invalida! Escolha uma chave entre 0 e %d.\n", M - 1);
        return;
    }

    Lista* lista = tabelaHash->tabela[chave];
    if (lista->head == NULL) {
        printf("A chave %d nao possui elementos.\n", chave);
        return;
    }

    printf("Nomes na chave %d:\n", chave);
    Node* atual = lista->head;
    while (atual != NULL) {
        printf("- %s\n", atual->nome);
        atual = atual->next;
    }
}

void exibirDiferencaMaiorMenor(TabelaHash* tabelaHash) {
    int minChave = -1;
    int maxChave = -1;
    int minElementos = 100788;
    int maxElementos = -1;

    for (int i = 0; i < M; i++) {
        int quantidade = tabelaHash->tabela[i]->size;

        if (quantidade > 0 && quantidade < minElementos) {
            minElementos = quantidade;
            minChave = i;
        }

        if (quantidade > maxElementos) {
            maxElementos = quantidade;
            maxChave = i;
        }
    }

    if (minChave == -1 || maxChave == -1) {
        printf("Tabela hash vazia \n");
    } else {
        int diferenca = maxElementos - minElementos;
        printf("Menor chave: %d (%d elementos)\n", minChave, minElementos);
        printf("Maior chave: %d (%d elementos)\n", maxChave, maxElementos);
        printf("Diferenca: %d\n", diferenca);
    }
}

void liberarTabelaHash(TabelaHash* tabelaHash) {
    for (int i = 0; i < M; i++) {
        Lista* lista = tabelaHash->tabela[i];
        Node* atual = lista->head;
        while (atual != NULL) {
            Node* temp = atual;
            atual = atual->next;
            free(temp);
        }
        free(lista);
    }
    free(tabelaHash);
}

main(){
    TabelaHash* tabelaHash = criarTabelaHash();
    
    int opc;
    char nome[100];
    
    for(;;){
        printf("-------------------\n");
        printf("Escolha uma opcao\n");
        printf("1- Inserir nomes do arquivo\n");
        printf("2- Insirir nome \n");
        printf("3- Consultar Nome\n");
        printf("4- Exibir histograma\n");
        printf("5- Remover nome\n");
        printf("6- Listar nomes de uma chave\n");
        printf("7- Diferenca da menor chave para maior\n");
        printf("8- Finalizar\n");
        printf("-------------------\n");
        scanf("%d",&opc);
        
        if(opc==8){
            printf("Finalizando...");
            liberarTabelaHash(tabelaHash);
            break;
        }else if(opc==1){
            carregarNomes(tabelaHash, "nomes.txt");
            ordenarTabelaHash(tabelaHash);
        }else if(opc == 2){
            printf("Digite o nome que deseja inserir\n");
            scanf(" %[^\n]s", nome);  
            inserirTabelaHash(tabelaHash, nome);
            ordenarTabelaHash(tabelaHash);
        }else if(opc==3){
            printf("Digite um nome para buscar: \n");
            scanf(" %[^\n]s", nome);
            buscarTabelaHash(tabelaHash, nome);
        }else if(opc==4){
            exibirQuantChave(tabelaHash);
        }else if(opc==5){
            printf("Digite o nome para remover:\n");
            scanf(" %[^\n]s",nome);
            removerTabelaHash(tabelaHash, nome);
        }else if(opc == 6){
            int chave;
            printf("Digite o numero da chave para listar os nomes: ");
            scanf("%d", &chave);
           	imprimirNomesDaChave(tabelaHash, chave);
		}else if (opc==7){
		exibirDiferencaMaiorMenor(tabelaHash);
		}else{
			printf("Opcao invalida, tente novamente!");
		}
	}
	
	liberarTabelaHash(tabelaHash);
	return 0;
} 
