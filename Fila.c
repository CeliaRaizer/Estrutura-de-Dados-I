#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//representa pessoa na fila
typedef struct Node{
	int senha;
	struct Node* next; //aponta para o proximo elemento
} Node;

typedef struct{
	Node* front; //head-Inicio
	Node* rear; //tail-Final
} Fila;

//inicializar fila
void inicializa(Fila* fila){
	fila->front=NULL;
	fila->rear=NULL;
}

void inserir(Fila* fila, int senha, const char* tipoFila){

	Node* novo = (Node*)malloc(sizeof(Node)); //alocar memoria
	
	if(novo==NULL){
		printf("Erro de alocacao de memoria");
		return;
	}
	
	novo->senha = senha;
	novo->next = NULL;
	
	if(fila->rear == NULL){ //se a fila estiver vazia
		fila->front = novo;
		fila->rear = novo;
	}else{
		fila->rear->next = novo;
		fila->rear = novo;
	}
	printf ("Senha %d  - Fila %s\n", senha, tipoFila);
}

void remover(Fila* fila, const char* tipoFila){
	if (fila->front == NULL){
		printf("A fila esta vazia!\n");
		return;
	}
	
	Node* temp = fila->front;
	printf("Atendendo a senha: %d (%s) \n",temp->senha, tipoFila);
	
	fila->front = fila->front->next;
	if(fila->front == NULL){
		fila->rear = NULL;
	}
	
	free(temp);
}
int filaVazia(Fila* fila) {
    return (fila->front == NULL);
}
void consultarFila(Fila* fila, const char* nomeFila) {
    if (fila->front == NULL) {
        printf("A fila %s esta vazia.\n",nomeFila);
        return;
    }

    Node* temp = fila->front;
    printf("Fila %s: ",nomeFila);
    while (temp != NULL) {
        printf("%d ", temp->senha);
        temp = temp->next;
    }
    printf("\n");
}
//likberar memoria
void liberarFila(Fila* fila) {
    Node* temp;
    while (fila->front != NULL) {
        temp = fila->front;
        fila->front = fila->front->next;
        free(temp);
    }
    fila->rear = NULL;
}

int main(){
	Fila filaNormal, filaPrioridade;
	inicializa(&filaNormal);
	inicializa(&filaPrioridade);
	
	int opc;
	int subOpc;
	int senhaNormal=1;
	int senhaPrioridade=1;
	
	for(;;){
		printf("--BANCO ESTRUTURA DE DADOS--\n");
		printf("-----Escolha uma opcao-----\n");
		printf("1- Incluir pessoa na fila Normal\n");
		printf("2- Incluir pessoa na fila prioritaria\n");
		printf("3- Atender cliente\n");
		printf("4- Consultar fila\n");
		printf("5- Sair\n");
		scanf("%d",&opc);
		
		if(opc==5){
			printf ("Finalizando...");
			liberarFila(&filaNormal);
  			liberarFila(&filaPrioridade);
			break;
		}
		if(opc==1){
			inserir(&filaNormal, senhaNormal++, "Normal \n");
		}else if(opc==2){
			inserir(&filaPrioridade, senhaPrioridade++,"Prioritaria\n");
		}else if(opc==3){
			 if (!filaVazia(&filaPrioridade)) {
                    remover(&filaPrioridade, "Prioritaria");
                } else if (!filaVazia(&filaNormal)) {
                    remover(&filaNormal, "Normal");
                } else {
                    printf("Todas as filas estao vazias.\n");
                }
		}else if(opc==4){
			printf ("Qual fila deseja consultar?:\n");
			printf("1- Fila Normal\n");
			printf("2- Fila Prioritaria\n");
			printf("3- Consultar 2 filas\n");
			scanf ("%d",&subOpc);
			
			if (subOpc==1){
				consultarFila(&filaNormal,"Normal");
			}else if(subOpc==2){
				consultarFila(&filaPrioridade,"Prioritaria");
			}else if(subOpc==3){
				consultarFila(&filaPrioridade,"Prioritaria");
				consultarFila(&filaNormal,"Normal");
			}else{
				printf("Opcao invalida!\n");
			}
		}else{
			printf("Opcao invalida!");
		}
	}
}