#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_arr[1000];
} message;

int msgid;
pthread_t ptid;
void *worker_thread(void * mes) {
    
    key_t key;
    key = ftok("181101065", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    
    char msg[1000];
    char my_id[100];
    char to_id[100];
    
    strcpy(msg,strtok(message.mesg_arr,";"));
    strcpy(my_id,strtok(NULL,";"));
    strcpy(to_id,strtok(NULL,";"));

    message.mesg_type = (long)(atoi(to_id));
    strcpy(message.mesg_arr,msg);

    printf("MESAJ ID %d", msgid );
    msgsnd(msgid,&message,sizeof(message),0);
    printf("Mesaj yollandı\n");
}

int main() {

    key_t key;
    key = ftok("181101065", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    while(1){

        msgrcv(msgid, &message, sizeof(message), 1, 0);
        //struct mesg_buffer * tmp = (struct mesg_buffer *)malloc(sizeof(struct mesg_buffer));

        pthread_create(&ptid, NULL, &worker_thread, &message);
        pthread_join(ptid, NULL);
        printf("Data Received is : %s \n", message.mesg_arr);
    }
  
    return 0;

}
