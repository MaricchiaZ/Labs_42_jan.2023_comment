#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    // ftok to generate unique key
    // criamos uma chave atrelada ao arquivo shmfile para ancorar a memória compartilhada
    key_t key = ftok("./shmfile", 65);
    printf("key: %d\n", key);

    // shmget returns an identifier in shmid
    // com essa chave gera-se um id para o compartilhamento
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("shmid: %d\n", shmid);

    // shmat to attach to shared memory
    // usando o id, reservamos a zona de memória que iremos usar (nesse caso usaremos uma string)
    char* str = (char*)shmat(shmid, (void*)0, 0);

    // copiamos a string "Hj é o dia de terminar" para a memória compartilhada
    strcpy(str,"Hj é o dia de terminar");

    // printamos a string já colocada na memória compartilhada
    printf("Str: %s\n", str);

 // ______________________________________________________________________________________________________


    // ftok to generate unique key
    // criamos uma nova chave atrelada ao arquivo shmfile2 para ancorar outra memória compartilhada
    key_t key2 = ftok("./shmfile2", 68);
    printf("key2: %d\n", key2);

    // shmget returns an identifier in shmid
    // com essa chave gera-se um id para o compartilhamento
    int shmid2 = shmget(key2, 1024, 0666 | IPC_CREAT);
    printf("shmid2: %d\n", shmid2);

    // shmat to attach to shared memory
    // usando o id, reservamos a zona de memória que iremos usar (nesse caso usaremos uma string)
    char* str2 = (char*)shmat(shmid2, (void*)0, 0);

    // copiamos a string "2a string saindo do forno" para a memória compartilhada
    strcpy(str2,"2a string saindo do forno");

    // printamos a string já colocada na memória compartilhada
    printf("Str2: %s\n", str2);

// ________________________________________________________________________________________________________

    // ftok to generate unique key
    // criamos uma nova chave atrelada ao arquivo shmfile3 para ancorar outra memória compartilhada
    key_t key3 = ftok("./shmfile3", 69);
    printf("key3: %d\n", key3);

    // shmget returns an identifier in shmid
    // com essa chave gera-se um id para o compartilhamento
    int shmid3 = shmget(key3, 1024, 0666 | IPC_CREAT);
    printf("shmid3: %d\n", shmid3);

    // shmat to attach to shared memory
    // usando o id, reservamos a zona de memória que iremos usar (nesse caso usaremos uma string)
    char *test = "Que nessas frases tem um pouco de nós dois";
    char *str3 = (char*) shmat(shmid3, NULL, 0);
    memcpy(str, test, 44);

    // printamos a string já colocada na memória compartilhada
    printf("Str3: %s\n", str3);



    // detach from shared memory
    // desconectamos o programa 1 da memória compartilhada
    shmdt(str); // desconectando-se de cada uma das zonas conectadas
    shmdt(str2);
    shmdt(str3);

    return 0;
}
