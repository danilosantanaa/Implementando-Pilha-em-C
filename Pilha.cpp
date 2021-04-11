# include <stdio.h>
# include <stdlib.h>
# include <locale.h>

// Declarando os elementos que vão compor minha pilha


// Criando a estrutura responsavel por salvar os registros
typedef struct registro {
	int valor;
} Registro;

// Criando uma estrutura que fica responsavel por armazenar os endereço dos nos
typedef struct no {
	Registro registro;
	struct no *prox;
} * No;

// Criando a estrutura responsavel por guardar informacao como o tamanho de elementos e o nos que vao compor a estrutura de dados pilha
typedef struct pilha {
	int tot;
	No prox;
} * Pilha;


/* Implementandos as funções */

// Funcao responsavel de criar uma nova Pilha
void criarPilha(Pilha *p) {
	(*p) = (Pilha) malloc(sizeof(struct pilha));
	(*p)->prox = NULL;
	(*p)->tot = 0;
}

// Verificar se a pilha está vazia
bool isVazia(Pilha p) {
	return p->prox == NULL;
}

// Funcao que retorna o valor que está no topo da pilha
Registro * topo(Pilha p) {
	return !isVazia(p) ? &(p->prox->registro) : NULL;
}

// Funcao que mostra a pilha
void print_p(Pilha p) {
	No aux = p->prox;
	
	printf("%d elementos: {", p->tot);
	
	while(aux != NULL) {
		printf("%d%s", aux->registro.valor, (aux->prox != NULL) ? ", ": "");
		aux = aux->prox;
	}
	printf("}\n");
}

// Funcao que adiciona elemento na pilha
bool push(Pilha * p, Registro registro) {
	No no = (No) malloc(sizeof(struct no));
	
	if(no != NULL){
		(*p)->tot++;
		no->registro = registro;
		no->prox = (*p)->prox;
		(*p)->prox = no;
		
		return true;
	} 
	
	printf("<<< Nao foi possivel alocar memoria >>>\n");
	
	return false;
}

// Funcao responsavel de tirar elemento da pilha
Registro* pop(Pilha *p) {
	Registro* r = NULL;
	
	if(!isVazia(*p)) {
		No no = (*p)->prox; // Guardar  o lixo
		(*p)->prox = (*p)->prox->prox; // Irá trocar o segundo elemento pelo primeiro
		(*p)->tot--;
		
		r = &(no->registro);
		
		free(no);
	} else {
		printf("<<< Underflow: Pilha está vazia\n >>>");
	}
	
	return r;
}

char operacoesPilha(Pilha * p) {
	char opcao;
	Registro r1, *r2;
	printf("~~~~~~~ OPERAÇÃO COM A PILHA ~~~~~~~\n");
	printf("[1] - INSERIR\n");
	printf("[2] - REMOVER\n");
	printf("[3] - VER TOPO\n");
	printf("[4] - MOSTRAR PILHA\n");
	printf("[5] - SAIR\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Opção >>> ");
	opcao = getchar();
	
	system("cls"); // Caso for Windows
	fflush(stdin);
	
	switch(opcao) {
		case '1':
			printf("Digite um valor: ");
			scanf("%d", &r1.valor);
			fflush(stdin);
			
			if(push(&(*p), r1)) {
				printf("<<< O valor %d foi inserido na pilha >>>\n", r1.valor);
			} else {
				printf("<<< ERRO ao inserir o valor %d >>>\n", r1.valor);
			}
			break;
		case '2':
			r2 = pop(&(*p));
			if(r2) {
				printf("<<< O valor %d foi apagado da pilha >>>\n");
			}
			
			break;
		case '3':
			
			r2 = topo(*p);
			
			if(r2 != NULL)
				printf("<<< O valor do topo: %d >>>\n", r2->valor);
			else
				printf("<<< A pilha esta vazia! >>>\n");
			break;
		case '4':
			print_p((*p));
			break;
		case '5':
			printf("<<< Fechando o programa >>>\n");
			break;
		default:
			printf("<<< Opção escolhida inválida! >>>\n");
	}
	
	return opcao;
}


int main() {
	setlocale(LC_ALL, "Portuguese");
	
	Pilha p;
	criarPilha(&p);
	
	char flag;
	
	do {
		flag = operacoesPilha(&p);
	} while(flag != '5');
	
	return 0;
}
