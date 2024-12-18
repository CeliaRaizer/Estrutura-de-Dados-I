#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	char nome[50];
	int quant;
	float preco;
}medicamento; 

typedef struct Node{ 
	medicamento medic;
	struct Node *next;  //aponta para o proximo no
} Node; 

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

void imprimirMedicamento(medicamento m){
	printf ("Medicamento: %s \n",m.nome);
	printf ("Quantidade: %d \n",m.quant);
	printf ("Preco: %.2f \n",m.preco);
}

Node* criarNode(medicamento m){
	Node *novoElemento=(Node*)malloc(sizeof(Node)); //armazena o endereco do novo nó, aloca dinamicamente memoria suficiente

	novoElemento->medic = m; //atribui os dados dos medicamentos ao nó
	novoElemento->next= NULL; //indica que o no nao aponta para nenhum outro no 
	return novoElemento; 
}

void inserir (Node **head, medicamento m)
{
	Node *novoElemento = criarNode(m); //cria um novo no com o medicamento
	
	if(*head == NULL){ 
		*head=novoElemento;
	}else{
		Node *temp=*head;
		while (temp->next != NULL) { 
            temp = temp->next; //temp aponta para o ultimo no
		}
		temp->next = novoElemento;  // Conecta o novo no ao final da lista
	}
}

void removerMedicamento(Node **head, char *nome){
	Node *temp = *head;
	Node *anterior= NULL;
	while (temp != NULL && strcmp(temp->medic.nome, nome)!=0){
		anterior=temp;
		temp=temp->next; //Move temp para o proximo no na lista.
	}
	if (temp==NULL){
		printf ("Medicamento nao encontrado");
		return;
	}
	if(anterior != NULL){ // Se o no a ser removido nao for o primeiro
		anterior->next=temp->next;
	}else{
		*head=temp->next; //atualiza o inicio da lista
	}
	free(temp); // Libera a memoria do no removido
}

void imprimirLista(Node *head){
	Node *temp=head;
	while (temp !=NULL){ 
		imprimirMedicamento(temp->medic); 
		temp=temp->next;  // Avanca para o proximo no
	}
}
// Função para liberar a memória 
void liberarLista(Node *head) {
    while (head != NULL) {
        Node *temp = head; 
        head = head->next; // Avanca para o proximo no
        free(temp);  // Libera a memoria do no atual
    }
}

main(){
	int opc;
	Node *listaMedicamentos = NULL; //inicializa a lista como vazia
	
	for(;;){
		printf ("\nEscolha uma opcao: \n");
		printf ("1- Inserir medicamento na lista\n");
		printf ("2- Remover medicamento da lista\n");
		printf ("3- pesquisar medicamento da lista\n");
		printf ("4- Lista de Medicamento\n");
		printf ("5- Finalizar\n");
		scanf ("%i",&opc);
		
	if (opc==5){
		printf ("\nFinalizando...");
		break;
	}
	if (opc==1){
		medicamento m = lerMedicamento();
        inserir(&listaMedicamentos, m);
	}
	else if (opc==2)
	{
		char nome[50];
		printf ("\nDigite o nome do medicamento a ser removido: \n");
		scanf (" %[^\n]s", nome);
		removerMedicamento(&listaMedicamentos, nome);
	}
	else if(opc==3){
		char nome[50];
		printf ("\nQual medicamento deseja buscar?:\n");
		scanf (" %[^\n]s",nome);
		Node *temp = listaMedicamentos;
		while (temp !=NULL){
			if (strcmp(temp->medic.nome, nome)==0){
				imprimirMedicamento(temp->medic);
				break;
			}
			temp=temp->next;
		}
		if (temp==NULL){
			printf ("Medicamento nao encontrado!\n");
		}
	}
	else if(opc==4){
		imprimirLista(listaMedicamentos);
	}
}
	liberarLista(listaMedicamentos);
}