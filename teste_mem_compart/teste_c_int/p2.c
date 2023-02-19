 #include <sys/shm.h>
 #include <sys/ipc.h>
 #include <stdio.h>
 #include <string.h>

int main()
{
int project_id = 1;

key_t key = ftok("ponte", project_id);

int shmem_id = shmget(key, 1024, 0066 | IPC_CREAT);

int *shared_int = (int*) shmat(shmem_id, (void*)0, 0);

// bloco de print
printf("key: %d\n", key);
printf("shmem_id: %d\n", shmem_id);
//printf("STR QUE CHEGOU: %s\n", str);
printf("shared_int QUE CHEGOU: %d\n", *shared_int);

shmdt(shared_int);
//shmdt(str);
shmctl(shmem_id, IPC_RMID, NULL); // executa a operação de controle especificada por cmd no Segmento de memória compartilhada System V cujo identificador é dado em IPC_RMID que marca o segmento a ser destruído, com a flag IPC_RMID o NULL é ignorado
return (0); 
}