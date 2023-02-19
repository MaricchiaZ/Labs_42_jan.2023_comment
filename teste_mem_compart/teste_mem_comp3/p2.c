 #include <sys/shm.h>
 #include <sys/ipc.h>
 #include <stdio.h>
 #include <string.h>

int main()
{
int project_id = 1;

key_t key = ftok("ponte", project_id);

int shmem_id = shmget(key, 1024, 0066 | IPC_CREAT);

int *i = (int*) shmat(shmem_id, (void*)0, 0);

// bloco de print
printf("key: %d\n", key);
printf("shmem_id: %d\n", shmem_id);
//printf("STR QUE CHEGOU: %s\n", str);
printf("i QUE CHEGOU: %d\n", *i);
*i = 9;
printf("i modificado: %d\n", *i);

shmdt(i);
//shmdt(str);
//shmctl(shmem_id, IPC_RMID, NULL);
return (0); 
}