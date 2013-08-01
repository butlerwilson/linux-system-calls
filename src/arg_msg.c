#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<string.h>


#define KEY 0x9527

typedef struct msgbuf 
{
	long id;     /* message type, must be > 0 */
  char text[256]; /* message data */
}MsgBuf;

int MSG_ID;

void catchSIGINT(int sigNum)
{
	deleteMsg(MSG_ID);
}

/*
	以上结构体的定义只有一个约束： 
		必须两个及两个以上成员，第一个成员必须是 long 型。
*/

int createMsg(key_t key)
{
	int msgId;
	
	msgId = msgget(key, IPC_CREAT|IPC_EXCL|0777);
	if(msgId < 0)
	{
		perror("createMsg Error");	
		exit(-1);
	}
	
	return msgId;
}


int getMsg(key_t key)
{
	int msgId;
	
	msgId = msgget(key, IPC_EXCL|0777);
	if(msgId < 0)
	{
		perror("getMsg Error");	
		exit(-1);
	}
	
	return msgId;
}

int deleteMsg(int  msgId)
{
	msgctl(msgId, IPC_RMID, NULL);	
}

int main(void)
{
	int msgId;
	pid_t  pid;
	
	pid = fork();
	if(pid > 0)
	{
		int i;
		MsgBuf data;
		
		msgId = createMsg(KEY);
		MSG_ID = msgId;
		for(i = 0; i < 10; i++)
		{
			sleep(1);
			data.id = 1;
			sprintf(data.text, "Hello [%d]", i);
			if(msgsnd(msgId, &data, sizeof(MsgBuf), 0) < 0)
			{
				perror("msgsnd fail");	
				exit(-2);
			}
		}
		
	}else if(pid == 0)
	{
		sleep(1);
		MsgBuf data;
		
		msgId = getMsg(KEY);
		MSG_ID = msgId;
		while(1)
		{
			if(msgrcv(msgId, &data, sizeof(data), 1, 0) < 0)
			{
				perror("msgrcv fail");	
				exit(-2);
			}
			printf("data[%s] pid=%d\n", data.text, getpid());
		}
		
		exit(0);
	}else
	{
		perror("Fork Error");	
		exit(-2);
	}
}
