 #include <sys/msg.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <stdio.h>
 #include <string.h>

 typedef struct mymsg {
  long mtype;
  char mtext[24];
 }mymsg;

 int main()
 {
  int msqid;
  mymsg msg,buff;
  msqid=msgget("/home/vi/msg.tmp", 0666);

  if(msqid==-1){
  perror("FAiled to create message queue\n");
  }
  else{
  printf("Message queue id:%u\n",msqid);
  }
  msg.mtype=1; // was there failed to copy
  strcpy(msg.mtext,"This is a message");
  if(msgsnd(msqid,&msg,sizeof(msg.mtext),0)==-1){
   perror("msgsnd failed:");
  }
  else{
   printf("Message sent successfully\n");
  }
 //ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);

  msgrcv(msqid,&buff,sizeof(msg.mtext),1,0);
  printf("The message received is: %s\n",buff.mtext);
 }
