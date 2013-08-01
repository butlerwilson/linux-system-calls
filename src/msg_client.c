
#include "msgSrvClnt.h"

char* extendsStr(char *inStr, size_t newSize);
unsigned char getIntLen(int pid);
char* rcvMsgByMsgQ(int msgId, long type);

int getMsg(key_t key)
{
	int msgId;
	
	msgId = msgget(key, IPC_EXCL|0777);
	if(msgId < 0)
	{
		perror("createMsg Error");	
		exit(-1);
	}
	
	return msgId;
}

unsigned char getIntLen(int pid)
{
	unsigned char i;
	
	for(i = 0; pid; pid /= 10)
		i++;
		
	return i;
}

char* extendsStr(char *inStr, size_t newSize)
{
	char *retStr;
	
	retStr = (char *)malloc(sizeof(char) * newSize);
	strcpy(retStr, inStr);
	free(inStr);
	
	return retStr;
}

char* rcvMsgByMsgQ(int msgId, long type)
{
	char *retResult;
	MsgBuf buf;
	int vRet;
	int i = 0;
	
	retResult = (char*)malloc(sizeof(char) * 256);
	if(retResult == NULL)
	{
		perror("malloc");
		return NULL;	
	}
	retResult[0] = 0;
	while(1)
	{
		vRet = msgrcv(msgId, &buf, sizeof(buf), type, 0);
		if(vRet < 0)
		{
			perror("rcvMsgByMsgQ:msgrcv");	
			exit(-4);
		}
		if(buf.endFlag == 0)
			break;
		
		if(i > 0)
		{
			retResult = extendsStr(retResult, 256 * (i + 1));
		}
		printf(" retResult = [%s] \n", retResult);
		strncat(retResult, buf.text, 256);
		printf(" i = [%d] \n", i);
		i++;
	}
	
	return retResult;
}

int main(void)
{
	int msgId;
	char cmd[256];
	MsgBuf buf;
	char *resultStr;
	
	msgId = getMsg(KEY);
	if(msgId < 0)
	{
		exit(-1);	
	}
	
	if(read(0, cmd, sizeof(cmd)) < 0)
	{
		exit(-2);
	}
	cmd[strlen(cmd) - 1] = 0;
	buf.type = 1;
	sprintf(buf.text, "%c%d%s", getIntLen(getpid()),  getpid(), cmd);
	if(msgsnd(msgId, &buf, sizeof(buf) - sizeof(long), IPC_NOWAIT) < 0)
	{
		exit(-3);	
	}
	
	resultStr = rcvMsgByMsgQ(msgId, getpid());
	printf("result=[%s]\n", resultStr);
	free(resultStr);
}
