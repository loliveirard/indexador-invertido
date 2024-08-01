#include <stdio.h> // entrada e saida padrao
#include <cstdlib> // alocacao dinamica de memoria
#include <cstring> // manipulacao de strings

#define OUTPUT_FILENAME "indice.bin" // nome do arquivo binario gerado
#define MAX_INDEX_LENGTH 100         // numero maximo de termos distintos

// estrutura para um par (doc_id, freq_d_t)
struct pair {
  unsigned int doc_id;
  unsigned int freq_d_t;
};

// estrutura para o indice invertido de um termo
struct inverted_index {
  char term[50];              // termo
  unsigned int num_pairs;     // numero de pares (doc_id, freq_d_t)
  struct pair *pairs;         // array de pares (doc_id, freq_d_t)
};

// retorna o indice de um termo no indice invertido
int get_index(char* term, struct inverted_index* index){
  int i;
  for(i = 0; i < MAX_INDEX_LENGTH; i++){
    if(strcmp(index[i].term, term) == 0){
      return i;
    }
  }
  return -1;
}

// indexa um novo termo
void index_term(char* term, int doc_id, struct inverted_index* index, int idx){
  strcpy(index[idx].term, term);
  index[idx].pairs[doc_id].freq_d_t = 1;
}

// atualiza o indice de um termo existente
void update_index(char* term, int doc_id, struct inverted_index* index, int idx){
  index[idx].pairs[doc_id].freq_d_t += 1;
}

// indexa um arquivo
int index_file(char* filename, int doc_id, struct inverted_index* index, int num_terms){
  FILE *fp;
  int term_counter, idx;
  char line[100];
  char* buf;
  
  fp = fopen(filename, "r");
  if (fp == NULL){
    return -1;   // falha na abertura do arquivo
  }
  
  term_counter = num_terms;
  while(fgets(line, 100, fp)){    // le cada linha do arquivo
    buf = strtok(line, " \n");    // quebra a linha em tokens (palavras)
    while(buf != NULL){
      idx = get_index(buf, index);   // obtem o indice do termo no indice invertido
      if (idx >= 0) {
	      update_index(buf, doc_id, index, idx);   // atualiza o indice se o termo ja existe
      } else {
	      index_term(buf, doc_id, index, term_counter);   // indexa um novo termo
	      term_counter++;
      }
      buf = strtok(NULL, " \n");   // move para o proximo token
    }
  }
  
  fclose(fp);   // fecha o arquivo
  return term_counter - num_terms;   // retorna o numero de novos termos indexados
}

// salva o indice em um arquivo binario
void save_index(struct inverted_index* index, int num_terms){
  FILE* fp;
  int i, j;
  
  fp = fopen(OUTPUT_FILENAME, "wb");   // abre o arquivo binario para escrita
  for(i = 0; i < num_terms; i++){
    fwrite(index[i].term, sizeof(char), 50, fp);   // escreve o termo
    fwrite(&index[i].num_pairs, sizeof(int), 1, fp);   // escreve o numero de pares
    for(j = 0; j < index[i].num_pairs; j++){
      fwrite(&index[i].pairs[j].doc_id, sizeof(int), 1, fp);   // escreve doc_id
      fwrite(&index[i].pairs[j].freq_d_t, sizeof(int), 1, fp);   // escreve freq_d_t
    }
  }
  
  fclose(fp);   // fecha o arquivo
}

// funcao principal
int main(int argc, char** argv){
  struct inverted_index index[MAX_INDEX_LENGTH];   // array de indices invertidos
  int num_terms, n, i, j;
  char* filename[50];   // array de nomes de arquivos
  
  scanf("%d", &n);   // le o numero de arquivos a serem indexados
  
  // aloca memoria para cada nome de arquivo
  for(i = 0; i < n; i++){
    filename[i] = (char*)malloc(50*sizeof(char));
  }
  
  // inicializa cada indice invertido
  for(i = 0; i < MAX_INDEX_LENGTH; i++){
    index[i].pairs = (struct pair*)malloc(n * sizeof(struct pair));
    index[i].num_pairs = n;
    for(j = 0; j < index[i].num_pairs; j++){
      index[i].pairs[j].doc_id = j;
      index[i].pairs[j].freq_d_t = 0;
    }
  }
  
  // le os nomes dos arquivos
  for(i = 0; i < n; i++){
    scanf("%s", filename[i]);
  }
  
  num_terms = 0;
  
  // indexa cada arquivo e atualiza o numero total de termos indexados
  for(i = 0; i < n; i++){
    num_terms += index_file(filename[i], i, index, num_terms);
  }
  
  // salva o indice no arquivo binario
  save_index(index, num_terms);
  
  // libera a memoria alocada dinamicamente
  for(i = 0; i < n; i++){
    free(filename[i]);
    free(index[i].pairs);
  }
  
  return 0;
}
