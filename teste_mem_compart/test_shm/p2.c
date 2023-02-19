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
    //char* str = NULL;
    // usando o id, reservamos a zona de memória que iremos usar (nesse caso usaremos uma string)
    char* str = (char*)shmat(shmid, NULL, 0);
    //char *strcp = strcpy(str, strcp);
    // printamos a string colocada na memória compartilhada pelo P1.c
    printf("Str: %s\n", str);

    // detach from shared memory
    // desconectamos dessa zona conectada
    shmdt(str);

    // destroy the shared memory
    // liberamos essa zona da memória que estava sendo usada para o compartilhamento
    shmctl(shmid, IPC_RMID, NULL);

    //_______________________________________________________________________________________________

    // ftok to generate unique key
    // criamos outra chave, atrelada ao arquivo shmfile2, para ancorar outra zona de memória compartilhada
    key_t key2 = ftok("./shmfile2", 68);
    printf("key2: %d\n", key2);

    // shmget returns an identifier in shmid
    // com essa chave gera-se um id para o compartilhamento
    int shmid2 = shmget(key2, 1024, 0666 | IPC_CREAT);
    printf("shmid2: %d\n", shmid2);

    // shmat to attach to shared memory
    //char* str = NULL;
    // usando o id, reservamos a zona de memória que iremos usar (nesse caso usaremos uma string)
    char* str2 = (char*)shmat(shmid2, NULL, 0);
    //char *strcp = strcpy(str, strcp);
    // printamos a string já colocada na memória compartilhada
    printf("Str2: %s\n", str2);

    // detach from shared memory
    // desconectamos dessa zona conectada
    shmdt(str2);

    // destroy the shared memory
    // liberamos essa zona da memória que estava sendo usada para o compartilhamento
    shmctl(shmid2, IPC_RMID, NULL);
// _______________________________________________________________________________________________________

    // ftok to generate unique key
    // criamos outra chave, atrelada ao arquivo shmfile3, para ancorar outra zona de memória compartilhada
    key_t key3 = ftok("./shmfile3", 69);
    printf("key3: %d\n", key3);

    // shmget returns an identifier in shmid
    // com essa chave gera-se um id para o compartilhamento
    int shmid3 = shmget(key3, 1024, 0666 | IPC_CREAT);
    printf("shmid3: %d\n", shmid3);

    // shmat to attach to shared memory
    // usando o id, reservamos a zona de memória que iremos usar (nesse caso usaremos uma string)
    char *str3 = (char*) shmat(shmid3, (void*)0, 0);

    // printamos a string já colocada na memória compartilhada
    printf("Str3: %s\n", str3);


    // detach from shared memory
    // desconectamos dessa zona conectada
    shmdt(str3);

    // destroy the shared memory
    // liberamos essa zona da memória que estava sendo usada para o compartilhamento
    shmctl(shmid3, IPC_RMID, NULL);

    return 0;
}
