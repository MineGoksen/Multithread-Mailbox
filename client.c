#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
struct mesg_buffer {
    long mesg_type;
    char mesg_arr[1000];
} message;

int main(int argc, char *argv[])
{
    key_t key;
    int msgid;
    key = ftok("181101065", 65);
    msgid = msgget(key, 0666 | IPC_CREAT); // create msg queue
    message.mesg_type = 1;

    while(1){
        printf("Çıkış yapmak istiyorsanız 1 e devam etmek için 0 a basınız: ");
        int cikis = 0;
        scanf(" %d", &cikis);
        if(cikis == 1){
            exit(1);
        }
    	char x[20];
        printf(" \n Enter message ");
        scanf(" %[^'\n']s", &message.mesg_arr);
        printf(" \nEnter client id ");
        scanf(" %s", &x);
        strcat(message.mesg_arr,";");
        strcat(message.mesg_arr,argv[1]);
        strcat(message.mesg_arr,";");
        strcat(message.mesg_arr,x);

        msgsnd(msgid, &message, sizeof(message), 0); 

        long tmp = strtol(argv[1],NULL,10);
        msgrcv(msgid, &message, sizeof(message), tmp, 0);
        printf("Gelen mesaj %s \n", message.mesg_arr); 
        printf("****************************")  ; 
        message.mesg_type = 1; 
        sleep(10);
    }
}
