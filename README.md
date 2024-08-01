# indexador_invertido
programa que lê um conjunto de arquivos texto e armazena suas informações num arquivo de índice invertido<br>
# info
indexador.c<br>
recebe como entrada um inteiro n correspondente ao numero de arquivos texto a serem indexados e em seguida o nome dos arquivos<br>
devolve um arquivo binario de indice invertido contendo informacoes sobre cada um dos termos dos arquivos passados na entrada i.e. id do documento e numero de ocorrencias correspondente<br>
pconsulta.c<br>
recebe como entrada um inteiro m correspondente ao numero de consultas a serem realizadas e em seguida cada uma das consultas seguindo o padrao (<termo1> operador <termo2>)<br>
o operador pode ser do tipo E (and) ou OU (or), e correponde a uma operacao logica aplicada nos indices do arquivo, retornando os ids dos documentos que atendem a condicao<br>
