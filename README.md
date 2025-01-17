# Indexador Invertido

Este projeto tem o objetivo de ler um conjunto de arquivos texto e armazenar suas informações em um arquivo de índice invertido que pode ser consultado pelo usuário.

## Informações

### `indexador.c`

- **Entrada**: Recebe um inteiro `n` que representa o número de arquivos de texto a serem indexados. Em seguida, recebe os nomes desses arquivos.
- **Saída**: Gera um arquivo binário contendo o índice invertido. Este arquivo inclui informações sobre cada termo nos arquivos de entrada, como o ID do documento e o número de ocorrências do termo.

### `pconsulta.c`

- **Entrada**: Recebe um inteiro `m` que representa o número de consultas a serem realizadas. Em seguida, processa cada consulta no formato `<termo1> operador <termo2>`.
- **Operadores**:
  - **E** (`and`): Realiza uma operação lógica "E" nos índices do arquivo.
  - **OU** (`or`): Realiza uma operação lógica "OU" nos índices do arquivo.
- **Saída**: Retorna os IDs dos documentos que atendem à condição especificada na consulta.
