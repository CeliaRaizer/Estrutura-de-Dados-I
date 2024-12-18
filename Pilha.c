#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	char nome[50];
}nome;

typedef struct Node{
	nome n;
	struct Node *next;
	struct Node *prev;
}Node;

Node* criarNo(nome m){
	Node *novoNo = (Node*)malloc(sizeof(Node));
	
	strcpy(novoNo->n.nome, m.nome);
	
	novoNo->next=NULL;
	novoNo->prev=NULL;
	return novoNo;
}

void push(Node** topo, nome n){
	Node* novoNo = criarNo(n);
	
	if (*topo==NULL){
		*topo=novoNo;
	}else{
		novoNo->prev=*topo;
		(*topo)->next= novoNo;
		*topo=novoNo;
	}
	printf ("Empilhado!\n");
}

void pop(Node** topo){
	
	if(topo==NULL){
		printf ("Erro: a pilha esta vazia!\n"); //underflow
		return;
	}
	
	Node* temp = *topo;
	printf ("Desenpilhando: %s\n",temp->n.nome);
	
	*topo = (*topo)->prev;
	
	if (topo!=NULL){
		(*topo)->next = NULL;
	}
	
	free(temp);
}


int empty(Node* topo){
	return topo == NULL;
}

void stacktop(Node* topo){

	if(empty(topo)){
		printf ("Erro: a pilha esta vazia!\n");
		return;
	}
	printf("Topo da pilha: %s\n",topo->n.nome);
}

void imprimir(Node* topo){
	if(empty(topo)){
		printf ("A pilha esta vazia!\n");
		return;
	}
	Node* temp = topo;
	printf("Pilha:\n\n");
	while(temp!=NULL){
		printf ("%s\n",temp->n);
		temp = temp->prev;
	}
}

int main(){
	Node* topo = NULL;
	
	int opc;
	nome n;
	
	for(;;){
		printf("\nEscolha uma opcao:\n");
		
		printf("1 - Empilhar \n");
        printf("2 - Desempilhar \n");
        printf("3 - Verificar o topo da pilha\n");
        printf("4 - Verificar se a pilha esta vazia\n");
        printf("5 - Mostrar todos os elementos da pilha\n");
        printf("6 - Sair\n");
        scanf("%i", &opc);
        
        if(opc==6){
        	printf("Saindo...");
        	break;
		}else if (opc==1){
			 printf("Digite o nome para empilhar: ");
			 scanf (" %[^\n]s", n.nome);
			 push(&topo, n);
		}else if(opc==2){
			if(!empty(topo)){
				pop(&topo);
			}else{
				printf ("Pilha vazia!\n");
			}
		}else if (opc==3){
			if (!empty(topo)){
				stacktop(topo);
			}else{
				printf("Pilha vazia!\n");
			}
		}else if(opc==4){
			if(empty(topo)){
                printf("A pilha esta vazia!\n");
            } else {
                printf("A pilha nao esta vazia!\n");
            }
		}else if (opc==5){
			imprimir(topo);
		}else{
			printf("Opcao invalida!");
		}
	}
}