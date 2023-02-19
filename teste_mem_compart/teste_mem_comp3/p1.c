 #include <sys/shm.h>
 #include <sys/ipc.h>
 #include <stdio.h>
 #include <string.h>

//typedef struct 

int main()
{
    int project_id = 1;
    key_t key;

    key = ftok("ponte", project_id);
    printf("key: %d\n", key);
    
    int shmem_id = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("shmem_id: %d\n", shmem_id);

    int *i = (int*) shmat(shmem_id, (void*)0, 0);
  
    *i = 5;
    printf("i inicial: %d\n", *i);

    while(*i == 5); // trava o programa
    printf("i final: %d\n", *i);

    shmdt(i);
    shmctl(shmem_id, IPC_RMID, NULL);
    return (0);
}

/*
IPC - inter prosses comunication

*(&i)

*/