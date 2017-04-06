//编写一个基于UDP的聊天工具   
//发送端代码   
#include <Winsock2.h>   
#include <stdio.h>
#include<iostream>
using namespace std;
int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);//版本号1.1   
									   //1.加载套接字库     
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return 0;
	}//endof if   
	 //判断是否我们请求的winsocket版本，如果不是   
	 //则调用WSACleanup终止winsocket的使用并返回   
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return 0;
	}///endof if   
	 //2.创建套接字   
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[100];
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		if ('#' == recvBuf[0])//表示客户端想要退出   
		{
			sendto(sockSrv, "#", strlen("#") + 1, 0, (SOCKADDR*)&addrClient, len);
			printf("Chat end!\n");
			break;
		}
		sprintf(tempBuf, "%s say: %s", inet_ntoa(addrClient.sin_addr), recvBuf);
		printf("%s\n", tempBuf);
		printf("Please input data:\n");

		cin>>sendBuf;//可以得到一行数据   
		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0,
			(SOCKADDR*)&addrClient, len);//发送数据   
	}///..while   
	closesocket(sockSrv);
	WSACleanup();
	return 0; 
}//endof main()  
