#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 50

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

Item mochilaVetor[TAM_MAX];
int totalItensVetor = 0;
int vetorOrdenado = 0;

No* mochilaLista = NULL;

int comparacoes = 0;

void limparBuffer();
Item lerItemDoUsuario();
void imprimirItem(Item item);

void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void ordenarVetor();
int buscarSequencialVetor(char* nome);
int buscarBinariaVetor(char* nome);

void inserirItemLista();
void removerItemLista();
void listarItensLista();
No* buscarSequencialLista(char* nome);

void menuVetor();
void menuLista();

int main() {
    int escolha = 0;

    while (escolha != 3) {
        printf("\n--- COMPARACAO DE ESTRUTURAS DE DADOS (MOCHILA) ---\n");
        printf("Qual estrutura voce deseja testar?\n");
        printf("1. Mochila (Vetor / Lista Sequencial)\n");
        printf("2. Mochila (Lista Encadeada)\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        
        if (scanf("%d", &escolha) != 1) {
            escolha = 0;
        }
        limparBuffer();

        switch (escolha) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

    No* atual = mochilaLista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    return 0;
}

void menuVetor() {
    int escolha = 0;
    char nomeBusca[30];

    while (escolha != 7) {
        printf("\n--- MOCHILA (VETOR) [%d/%d] | Ordenado: %s ---\n", 
               totalItensVetor, TAM_MAX, vetorOrdenado ? "Sim" : "Nao");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar (Sequencial)\n");
        printf("5. ORDENAR Vetor (Selection Sort)\n");
        printf("6. Buscar (Binaria)\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha: ");
        
        if (scanf("%d", &escolha) != 1) {
            escolha = 0;
        }
        limparBuffer();

        switch (escolha) {
            case 1:
                inserirItemVetor();
                break;
            case 2:
                removerItemVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                printf("Nome do item para buscar: ");
                scanf("%29s", nomeBusca);
                limparBuffer();
                comparacoes = 0;
                int posSeq = buscarSequencialVetor(nomeBusca);
                if (posSeq != -1) {
                    printf("Item encontrado (Sequencial):\n");
                    imprimirItem(mochilaVetor[posSeq]);
                } else {
                    printf("Item '%s' nao encontrado.\n", nomeBusca);
                }
                printf("-> Comparacoes realizadas: %d\n", comparacoes);
                break;
            case 5:
                ordenarVetor();
                break;
            case 6:
                if (!vetorOrdenado) {
                    printf("!! ATENCAO: O vetor nao esta ordenado. Rode a opcao 5 primeiro.\n");
                    break;
                }
                printf("Nome do item para buscar (Binaria): ");
                scanf("%29s", nomeBusca);
                limparBuffer();
                comparacoes = 0;
                int posBin = buscarBinariaVetor(nomeBusca);
                if (posBin != -1) {
                    printf("Item encontrado (Binaria):\n");
                    imprimirItem(mochilaVetor[posBin]);
                } else {
                    printf("Item '%s' nao encontrado.\n", nomeBusca);
                }
                printf("-> Comparacoes realizadas: %d\n", comparacoes);
                break;
            case 7:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
}

void menuLista() {
    int escolha = 0;
    char nomeBusca[30];

    while (escolha != 5) {
        printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar (Sequencial)\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha: ");
        
        if (scanf("%d", &escolha) != 1) {
            escolha = 0;
        }
        limparBuffer();

        switch (escolha) {
            case 1:
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4:
                printf("Nome do item para buscar: ");
                scanf("%29s", nomeBusca);
                limparBuffer();
                comparacoes = 0;
                No* encontrado = buscarSequencialLista(nomeBusca);
                if (encontrado != NULL) {
                    printf("Item encontrado (Sequencial):\n");
                    imprimirItem(encontrado->dados);
                } else {
                    printf("Item '%s' nao encontrado.\n", nomeBusca);
                }
                printf("-> Comparacoes realizadas: %d\n", comparacoes);
                break;
            case 5:
                printf("Voltando...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Item lerItemDoUsuario() {
    Item item;
    printf("Nome do item (sem espacos): ");
    scanf("%29s", item.nome);
    limparBuffer();
    
    printf("Tipo do item (sem espacos): ");
    scanf("%19s", item.tipo);
    limparBuffer();

    printf("Quantidade: ");
    while (scanf("%d", &item.quantidade) != 1) {
        printf("Entrada invalida. Digite um numero: ");
        limparBuffer();
    }
    limparBuffer();
    
    return item;
}

void imprimirItem(Item item) {
    printf("  Nome: %s | Tipo: %s | Qtd: %d\n", 
           item.nome, item.tipo, item.quantidade);
}

void inserirItemVetor() {
    if (totalItensVetor >= TAM_MAX) {
        printf("Mochila (Vetor) esta cheia! Impossivel adicionar.\n");
        return;
    }
    
    printf("Inserindo no Vetor...\n");
    Item novoItem = lerItemDoUsuario();
    
    mochilaVetor[totalItensVetor] = novoItem;
    totalItensVetor++;
    
    vetorOrdenado = 0;
    printf("Item '%s' inserido no vetor.\n", novoItem.nome);
}

void removerItemVetor() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%29s", nome);
    limparBuffer();

    int indice = buscarSequencialVetor(nome);
    comparacoes = 0;

    if (indice == -1) {
        printf("Item '%s' nao encontrado no vetor.\n", nome);
        return;
    }

    for (int i = indice; i < totalItensVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    
    totalItensVetor--;
    vetorOrdenado = 0;
    printf("Item '%s' removido do vetor.\n", nome);
}

void listarItensVetor() {
    if (totalItensVetor == 0) {
        printf("Mochila (Vetor) esta vazia.\n");
        return;
    }
    printf("\n--- Itens na Mochila (Vetor) [%d/%d] ---\n", totalItensVetor, TAM_MAX);
    for (int i = 0; i < totalItensVetor; i++) {
        printf("Vetor[%d]: ", i);
        imprimirItem(mochilaVetor[i]);
    }
}

void ordenarVetor() {
    printf("Ordenando vetor com Selection Sort...\n");
    
    for (int i = 0; i < totalItensVetor - 1; i++) {
        int indiceMenor = i;
        for (int j = i + 1; j < totalItensVetor; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[indiceMenor].nome) < 0) {
                indiceMenor = j;
            }
        }
        if (i != indiceMenor) {
            Item temp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[indiceMenor];
            mochilaVetor[indiceMenor] = temp;
        }
    }
    
    vetorOrdenado = 1;
    printf("Vetor ordenado por nome.\n");
}

int buscarSequencialVetor(char* nome) {
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int buscarBinariaVetor(char* nome) {
    int inicio = 0;
    int fim = totalItensVetor - 1;

    while (inicio <= fim) {
        comparacoes++;
        
        int meio = inicio + (fim - inicio) / 2; 

        int cmp = strcmp(mochilaVetor[meio].nome, nome);

        if (cmp == 0) {
            return meio;
        } 
        else if (cmp < 0) {
            inicio = meio + 1;
        } 
        else {
            fim = meio - 1;
        }
    }
    
    return -1;
}

void inserirItemLista() {
    printf("Inserindo na Lista Encadeada...\n");
    Item novoItem = lerItemDoUsuario();

    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    novoNo->dados = novoItem;
    novoNo->proximo = mochilaLista;
    mochilaLista = novoNo;
    
    printf("Item '%s' inserido na lista.\n", novoItem.nome);
}

void removerItemLista() {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%29s", nome);
    limparBuffer();

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item '%s' nao encontrado na lista.\n", nome);
        return;
    }

    if (anterior == NULL) {
        mochilaLista = atual->proximo;
    }
    else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Item '%s' removido da lista.\n", nome);
}

void listarItensLista() {
    if (mochilaLista == NULL) {
        printf("Mochila (Lista) esta vazia.\n");
        return;
    }
    
    printf("\n--- Itens na Mochila (Lista) ---\n");
    No* atual = mochilaLista;
    
    while (atual != NULL) {
        imprimirItem(atual->dados);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char* nome) {
    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}
