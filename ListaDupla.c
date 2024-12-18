#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	char nome[50];
	int quant;
	float preco;
}medicamento;

typedef struct Elemento{
	medicamento medic;
	struct Elemento *next; //aponta para o proximo
	struct Elemento *prev; //aponta para o anterior
}Elemento;

typedef struct Lista{
	struct Elemento *head; //ponteiro cabeça da lista
	struct Elemento *tail; //ponteiro para o ultimo nodo
	int size; //tamanho da lista
}Lista;

medicamento lerMedicamento(){
	medicamento m;
	printf("Digite o nome do medicamento: \n");
	scanf (" %[^\n]s", m.nome);
	printf ("Digite a quantidade: \n");
	scanf ("%d",&m.quant);
	printf ("Digite o preco: \n");
	scanf ("%f",&m.preco);
	
	return m;
}

Elemento* criarNo(medicamento m){
	Elemento *novoElemento = (Elemento*)malloc(sizeof(Elemento)); //aloca memoria para o novo no
	
	novoElemento->medic = m;
	novoElemento->next = NULL;
	novoElemento->prev = NULL;
	return novoElemento;
}

void inserir(Lista *lista,Elemento *pivo,medicamento m){
	Elemento *novoElemento = criarNo(m);
	
	if (pivo==NULL && lista->head == NULL){ // se a lista estiver vazia
		lista->head=novoElemento;
		lista->tail=novoElemento;
	}else if (pivo == NULL) { //inserir no inicio
		novoElemento->next = lista->head;
		lista->head->prev = novoElemento;
		lista->head = novoElemento;
	} else {
		novoElemento->next = pivo->next;
		novoElemento->prev = pivo;
		
		if(pivo->next == NULL) {
			lista->tail = novoElemento;
		} else {
			pivo->next->prev = novoElemento;
		}
		pivo->next = novoElemento;
	}
	lista->size++;
}

void remover(Lista *lista, Elemento *elemento){
	if (elemento!= NULL && lista->head != NULL){
		if (elemento==lista->head){ //remove o primeiro no
			lista->head=elemento->next;
		if (lista->head==NULL){ 
			lista->head->prev=NULL;
		}else{ //lista ficou vazia, atualiza tail
			lista->tail =NULL;
		}
	}else{ // Remover no no meio ou no fim
		elemento->prev->next= elemento->next;
		if(elemento->next==NULL){ //remove o ultimo elemento
			lista->tail=elemento->prev;
		}else{ //atualiza o elemento prev para o proximo nodo
			elemento->next->prev= elemento->prev;
		}
		// Libera a memória do nodo removido
        free(elemento);
        lista->size--; // Atualiza o tamanho da lista
	}
}
}

Elemento* buscar(Lista *lista, char nome[]){
	Elemento *atual = lista->head;
	while(atual != NULL) {
		if (strcmp(atual->medic.nome, nome) == 0) {
			return atual;
		}
		atual = atual->next;
	}
}

void listaInicio(Lista *lista) {
	Elemento *atual = lista->head;
	while(atual != NULL) {
		printf("Nome: %s, Quantidade: %d, Preco: %.2f\n",atual->medic.nome,atual->medic.quant,atual->medic.preco);
		atual = atual->next;
	}
}

void listarFinal(Lista *lista) {
	Elemento *atual = lista->tail;
	while(atual != NULL) {
		printf("Nome: %s, Quantidade: %d, Preco: %.2f\n", atual->medic.nome,atual->medic.quant,atual->medic.preco);
		atual = atual->prev;
	}
}
main(){
	Lista lista;
	lista.head = NULL;
	lista.tail = NULL;
	lista.size = 0;
	int opc;
	
	for(;;)
	{
		printf ("\nEscolha uma opcao: \n");
		printf ("1- Inserir medicamento na lista\n");
		printf ("2- Remover medicamento da lista\n");
		printf ("3- Pesquisar medicamento da lista\n");
		printf ("4- Listar Medicamento do inicio\n");
		printf ("5- Listar Medicamento do final\n");
		printf ("6- Finalizar\n");
		scanf ("%i",&opc);
		
		if (opc == 6) {
			printf("\nFinalizando...");
			break;
		} 
		else if (opc == 1) {
			medicamento m = lerMedicamento();
			inserir(&lista, lista.tail, m); // Insere no final
		} 
		else if (opc == 2) {
			char nome[50];
			printf("\nDigite o nome do medicamento a ser removido: \n");
			scanf (" %[^\n]s", nome);
			Elemento *elemento = buscar(&lista, nome);
			remover(&lista, elemento);
		} 
		else if (opc == 3) {
			char nome[50];
			printf("\nQual medicamento deseja buscar?:\n");
			scanf(" %[^\n]s", nome);
			Elemento *elemento = buscar(&lista, nome);
			if(elemento != NULL) {
				printf("Medicamento encontrado: %s, Quantidade: %d, Preço: %.2f\n",elemento->medic.nome,elemento->medic.quant,elemento->medic.preco);
			} else {
				printf("Medicamento nao encontrado.\n");
			}
		}
		 else if (opc == 4) {
			listaInicio(&lista);
		}
		 else if (opc == 5) {
			listarFinal(&lista);
		} 
		else {
			printf("\nOpcao invalida!\n");
		}
	}
}
	

