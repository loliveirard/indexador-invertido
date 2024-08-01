#include <stdio.h>
#include <cstdlib>
#include <cstring>

#define INPUT_FILENAME "indice.bin" // nome do arquivo binário de entrada
#define MAX_INDEX_LENGTH 100 // comprimento máximo do índice invertido
#define MAX_NUM_PAIRS 10 // número máximo de pares por termo

// estrutura para armazenar pares de id de documento e frequência
struct pair {
  unsigned int doc_id;
  unsigned int freq_d_t;
};

// estrutura para armazenar o índice invertido
struct inverted_index {
  char term[50]; // termo do índice
  unsigned int num_pairs; // número de pares para o termo
  struct pair *pairs; // ponteiro para os pares
};

// lê o índice do arquivo binário
int read_index(struct inverted_index* index){
  FILE *fp;
  int counter, i, j;
  fp = fopen(INPUT_FILENAME, "rb"); // abre o arquivo binário para leitura
  counter = 0;
  while(feof(fp) == 0){ // lê até o final do arquivo
    fread(&index[counter].term, sizeof(char), 50, fp); // lê o termo
    fread(&index[counter].num_pairs, sizeof(int), 1, fp); // lê o número de pares
    for(j = 0; j < index[counter].num_pairs; j++){
      fread(&index[counter].pairs[j].doc_id, sizeof(int), 1, fp); // lê o id do documento
      fread(&index[counter].pairs[j].freq_d_t, sizeof(int), 1, fp); // lê a frequência
    }
    counter++;
  }
  fclose(fp); // fecha o arquivo
  return counter - 1; // retorna o número de termos lidos
}

// lê a consulta do usuário
void read_query(char* p1, char* p2, char* op){
  char query[85];
  char* buf;
  fgets(query, 85, stdin); // lê a linha de consulta
  buf = strtok(query, " \n"); // separa o primeiro termo
  strcpy(p1, buf);
  buf = strtok(NULL, " \n"); // separa o operador
  strcpy(op, buf);
  buf = strtok(NULL, " \n"); // separa o segundo termo
  strcpy(p2, buf);
}

// realiza a operação 'and' entre dois termos
void op_and(char* p1, char* p2, struct inverted_index* index, int num_terms){
  int p1_idx, p2_idx, i;
  bool p1_found = false, p2_found = false;
  for(i = 0; i < num_terms; i++){
    if(strcmp(p1, index[i].term) == 0){
      p1_found = true;
      p1_idx = i;
    } else if(strcmp(p2, index[i].term) == 0){
      p2_found = true;
      p2_idx = i;
    }
  }
  if(p1_found && p2_found){
    for(i = 0; i < index[0].num_pairs; i++){
      if(index[p1_idx].pairs[i].freq_d_t > 0 && index[p2_idx].pairs[i].freq_d_t > 0){
        printf("%d ", i); // imprime o id do documento se ambos os termos estão presentes
      }
    }
  }
}

// realiza a operação 'or' entre dois termos
void op_or(char* p1, char* p2, struct inverted_index* index, int num_terms){
  int p1_idx, p2_idx, i;
  bool p1_found = false, p2_found = false;
  
  for(i = 0; i < num_terms; i++){
    if(strcmp(p1, index[i].term) == 0){
      p1_found = true;
      p1_idx = i;
    } else if(strcmp(p2, index[i].term) == 0){
      p2_found = true;
      p2_idx = i;
    }
  }
  if(p1_found && p2_found){
    for(i = 0; i < index[0].num_pairs; i++){
      if(index[p1_idx].pairs[i].freq_d_t > 0 || index[p2_idx].pairs[i].freq_d_t > 0){
        printf("%d ", i); // imprime o id do documento se pelo menos um dos termos está presente
      }
    }
  }
}

int main(int argc, char** argv){
  struct inverted_index index[MAX_INDEX_LENGTH]; // array de índices invertidos
  int num_terms, m, i;
  char query[85], p1[40], p2[40], op[5];
  
  // aloca memória para pares em cada termo do índice
  for(i = 0; i < MAX_INDEX_LENGTH; i++){
    index[i].pairs = (struct pair*) malloc (MAX_NUM_PAIRS * sizeof(struct pair));
  }
  
  num_terms = read_index(index); // lê o índice do arquivo
  scanf("%d", &m); // lê o número de consultas
  getchar(); // consome o caractere de nova linha restante
  
  // processa cada consulta
  for(i = 0; i < m; i++){
    read_query(p1, p2, op); // lê a consulta
    if(strcmp(op, "and") == 0) {
      op_and(p1, p2, index, num_terms); // realiza a operação 'and'
    } else if(strcmp(op, "or") == 0) {
      op_or(p1, p2, index, num_terms); // realiza a operação 'or'
    }
    printf("\n"); // nova linha após a impressão dos resultados
  }
  
  return 0;
}
