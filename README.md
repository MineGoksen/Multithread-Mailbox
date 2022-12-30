Clean the queue before run; 
> ipcs -q
> ipcrm -q <id>

Compile;
>gcc -o client client.c
>gcc -pthread -o server server.c

Run;
>./server
>./client <client id>
Client id is a numerical value.

**************************************************************************************************
Different clients can send message to each other. Each client must send a message before seeing the message.
