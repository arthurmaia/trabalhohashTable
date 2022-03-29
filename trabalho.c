#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 19

typedef struct {
  int ocupado;
  char chave[4];
  char url[50];
} Url;

Url hashTable[M];

void initHashTable() {
  for (int i = 0; i < M; i++) hashTable[i].ocupado = -1;
}

int returnValue(char *chave) {
  int soma = 0;
  
  for (int i = 0; i < strlen(chave); i++) soma += chave[i];
  
  return soma;
}

int generateHashCode(int chave) {
  return chave % M;
}

Url readUrl() {
  Url u;
  printf("Digite a URL: ");
  fflush(stdin);
  scanf("%s", u.url);

  printf("Digite a URL curta (até 4 letras): ");
  fflush(stdin);
  scanf("%s", u.chave);

  u.ocupado = 1;

  return u;
}

void insert() {
  Url u = readUrl();
  int x = returnValue(u.chave);
  int i = generateHashCode(x);
  
  while (hashTable[i].ocupado != -1) {
    i = generateHashCode(i + 1);
  }  
  hashTable[i] = u;
}

Url *search(char *chave) {
  int i = generateHashCode(returnValue(chave));
  if (strcmp(hashTable[i].chave, chave) == 0) {
    return &hashTable[i];
  }
  else {
    return NULL;
  }
}

void remove(char *chave) {
  Url *u = search(chave);

  if (u) {
    u->ocupado = -1;
  } else {
    printf("URL não encontrada\n");
  }
}

void printTable() {
  printf("\n---TABELA---\n");

  for (int i = 0; i < M; i++) {
    if (hashTable[i].ocupado != -1) {
      printf("%d %d %s %s\n", i, hashTable[i].ocupado,
      hashTable[i].chave, hashTable[i].url);
    } else {
      printf("%2d =\n", i);
    }
  }

  printf("\n----------\n");
}

int main() {
  int op;
  Url *u = NULL;
  char chave[4];
  initHashTable();
  
  do {
    printf("1 Para inserir\n");
		printf("2 Para buscar\n");
		printf("3 Para excluir\n");
		printf("4 Para listar\n");
		printf("0 Para sair\n");
		printf("Digite a opção: ");
    scanf("%d", &op);
		
    switch (op) {
      case 1:
        insert();
        break;
      case 2:
        printf("Digite a URL encurtada: ");
        scanf("%s", chave);

        u = search(chave);

        if (u) {
          printf("URL: %s\n", u->url);
				} else {
          printf("URL não encontrada\n");
				}
				break;
      case 3:
        printf("Digite a URL encurtada: ");
        scanf("%s", chave);
        
        remove(chave);
        break;
      case 4:
        printTable();
        break;
      default:
        break;
    }
  } while (op != 0);

  return 0;
}