 #include <sys/shm.h>
 #include <sys/ipc.h>
 #include <stdio.h>
 #include <string.h>

//typedef struct 

int main()
{
    int project_id = 1;
    key_t key; // key_t é um tipo de inteiro específico que não varia em número de bits entre diferentes tipos de sistemas operacionais. 

    key = ftok("ponte", project_id);
    // A função ftok (File TO Key) é uma função presente em sistemas operacionais Unix e Linux que gera uma chave de sincronização a partir de um arquivo. Ela é utilizada para associar um arquivo a uma chave de sincronização, permitindo que vários processos possam acessar e sincronizar o acesso a esse arquivo. A chave gerada é única e depende do caminho do arquivo, do ID do projeto e do valor de um caractere de projeto passado como parâmetro. A função ftok é utilizada com outras funções de sincronização, como semaphores e shared memory.
    //O ID do projeto (project ID) é um valor numérico utilizado pela função ftok para diferenciar diferentes projetos ou aplicações que estão usando a mesma chave de sincronização.
    printf("key: %d\n", key);
    
    int shmem_id = shmget(key, 1024, 0666 | IPC_CREAT); // cria ou acessa uma área de memória compartilhada: 1- key: é a chave de sincronização gerada pela função ftok, que é utilizada para identificar a área de memória compartilhada. 2- size: é o tamanho, em bytes, da área de memória a ser criada ou acessada. 3- shmflg: é um conjunto de flags que especificam as permissões de acesso e as opções de criação da área de memória.
    printf("shmem_id: %d\n", shmem_id);

    int *shared_int = (int*) shmat(shmem_id, (void*)0, 0);
  
    *shared_int = 5; // atribui o valor 5 ao endereço apontado pelo ponteiro
    printf("Data read from memory: %d\n", *shared_int);

    //&i = (int*)shmat(shmem_id, NULL, 0); // SE CONECTA NA MEM_COMPART.... anexa o segmento de memória compartilhada associado ao identificador de memória compartilhada especificado por shmid para o espaço de endereço do processo de chamada. 1-id da memória compartilhada criada pela shmget    2- usando o NULL o segmento será anexado no primeiro endereço disponível conforme selecionado pelo sistema. 

    //strcpy (str, "texto que vai para o outro lado");
    //printf("STR QUE VAI: %s\n", str);

    shmdt(shared_int); //A função shmdt() desacopla (detaches)o segmento de memória compartilhada especificado pelo endereço shmaddr do espaço de endereçamento processo que a chama. Obviamente, o segmento desacoplado deve ser um dentre os segmentos previamente acoplados pelo processo usando shmat. Este segmento não poderá mais utilizado pelo processo após a chamada da função. Valor de retorno: 0 em caso de sucesso e -1 em caso de erro.
    return (0);
}

/*
IPC - inter prosses comunication

*(&i)





1. que que é - ideia geral do projeto 
Dois programas que conversem entre si por memória compartilhada, sendo que um o ENCODER compacta um texto e outro, o DECODER que descomprime o arquivo. 

2. Como funciona
- Pega o texto do terminal ou arquivo passado por ARG
     inicia o Algoritmo de Huffman
            - monta a tabela de frequência
            - monta uma lista ordenada com as frequências dos caracteres que aparecem
            - usa essa lista linkada para formar uma árvore binária, removendo os nós menos frequentes, conectando eles por um novo nó e reinserindo na lista, até formar uma árvore binária
            - monto o dicionário percorrendo a árvore até ter uma sequencia de 0 e 1 para cada caracter
            - uso o dicionário e codifico o texto, trocando os caracteres pela sequência de 0 e 1
            - essa sequência de 0 e 1 é passada de 8 em 8 para os bits de um char, fazendo assim a compactação
            .....
            - a descompactação ocorre observando os bits do texto codificado, e percorrendo a árvore, esquerda se for 0, ou á direita se for 1, até achar um nó folha, esse caracter já decodificado vai compor o texto descompactado
     Memória compartilhada
            - permite que uma mesma memória seja usada por dois processos e/ou programas
            - usamos um arquivo como "âncora", para que possamos encontrar o "caminho" para essa zona de memória compartilhada, mesmo que os programas finalizem
            - o ENCODER manda o texto comprimido e a árvore serializada
            - O DECODER manda o texto descomprimido e os dados de eficiência do programa

3. Como vc fez para implementar
- entender as partes do algoritmo de Huffman e implementar cada uma - nessa fase o encoder e o decoder estavam no mesmo programa
- aprendi a lidar com a memória compartilhada
- separar o encoder e o decoder

4. Desafios encontrados
- aprender em uma semana conteúdos/ estruturas que eu nunca tinha visto nem lido como "árvore binária"
- parar um programa enquanto o outro funciona
- aprender sobre memória compartilhada
- aprender no meu tempo enquanto os outros estavam em ritmo diferente

5. Parte que vc mais gostou
- fazer um projeto incrível e ver funcionar
- trabalhar em grupo tentando achar uma solução plausível
- discutir o que compreendemos sobre o desafio

6. Dá pra usar outra forma de codificar além da árvore (se n for usar o algoritmo de Huffman)
- Se a gente olhar o algoritmo de Lempel-Ziv-Welch ( do winrar), ele monta um dicionario com os caracteres e com as sub sequencias que apareciam, assim não se usa a árvore. (quanto maior o texto melhor a taxa de compressão)

7. Quanto tempo vc dedicou
- todo o tempo disponível, esse labs é muito importante para mim, então a semana do desafio só existia labs, mais nada (das 8h as 2h)
- 

8. Por que j = 7; no compact?
- Do 7 ao 0 temos 8 posições. Em um char temos 8 bits. Esse número serve para saber que já manipulamos um byte completo, e esse byte com a sequência certa já pode ser passado para a memória compartilhada.

9. 1a coisa q vc fez ao receber o desafio?
- ler sobre a compactação de arquivos e do algoritmo de Huffman montar uma lista de etapas a serem feitas (MIRO)
- conversar com a equipe para chegarmos a um concenso sobre o que era pedido
- fazer um esquema visual de como funcinaria ENCODER e DECODER (wimsical)

10. TESTAR O PROGRAMA

11. O que poderia melhorar
- Deixar mais limpo e aprimorar o nome de algumas variáveis
- Otimizar o código em alguns pontos 

12. Como vc sai desse projeto
- Saí uma nova pessoa, mais confiante e realizado de ver funcionando e com um Readme bom.
- Com um maior espírito de equipe.
- Mais forte e mais capaz de passar por dificuldades. 
- Vivi a experiencia de um "RUSH", mas com uma equipe amiga e durando 1 semana
- Gostei de poder viver o "codar" do mundo externo da 42, com funções livres e podendo 

13. Você gostaria de fazer alguma ponderação
- ser mais otimista, curtir mais as etapas (acertos e erros), fazer o código já comentado (melhoraria o nome das variáveis)
















*/