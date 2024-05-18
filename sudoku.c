#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    int valid[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (j = 0; j < 9; j++) {
      if (n->sudo[i][j] != 0) {
        if (valid[n->sudo[i][j]] == 0) {
          valid[n->sudo[i][j]] = 1;
        } else
          return 0;
      }
    }
  }

  for (i = 0; i < 9; i++) {
    int valid[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (j = 0; j < 9; j++) {
      if (n->sudo[j][i] != 0) {
        if (valid[n->sudo[j][i]] == 0) {
          valid[n->sudo[j][i]] = 1;
        } else
          return 0;
      }
    }
  }

  for (int block = 0; block < 9; block++) {
    int valid[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
        int x = (block / 3) * 3 + i;
        int y = (block % 3) * 3 + j;
        if (n->sudo[x][y] != 0) {
          if (valid[n->sudo[x][y]] == 0) {
            valid[n->sudo[x][y]] = 1;
          } else
            return 0;
        }
      }
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n){
  List *list = createList();
    int i,j,k;
     for (i = 0; i < 9; i++){
        Node *new_node = createNode(); 
        for (j = 0; j < 9; j++){
           if(n->sudo[i][j] == 0){
              for(k=1;k<10;k++){
                 new_node = copy(n);
                 new_node->sudo[i][j] = k;
                 if(is_valid(new_node)){
                    pushBack(list, new_node);
                    }
                    else free(new_node);
                }
              return list;
             }
          }
       }
  return list;
}

int is_final(Node *n) { 
  for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
           if(n->sudo[i][j] == 0)
              return 0;
        }
     }
  return 1;
}

Node *DFS(Node *initial, int *cont) { 
  Stack *S = createStack();
  push(S, initial);
  while(first(S) != NULL){
    Node *aux = first(S);
    pop(S);
    if(is_final(aux)){
      return aux;
    }
    List *list = get_adj_nodes(aux);
    while(next(list) != NULL){
      Node *aux2 = first(list);
      push(S, aux2);
      aux2 = next(list);
    }
    free(initial);
    *cont = *cont + 1;
  }
  return NULL; 
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;

}*/