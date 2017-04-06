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
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	//  char IPaddr[16];   
	//  printf("please input you IP address!");   
	//  gets(IPaddr);   
	//3.发送消息   
	SOCKADDR_IN addrSrv;
	//  if(''==IPaddr[0])   
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//  else    
	//      addrSrv.sin_addr.S_un.S_addr = inet_addr(IPaddr);   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[200];
	int len = sizeof(SOCKADDR);
	while (1)
	{
		printf("Please input data:\n");
		cin>>sendBuf;
		sendto(sockClient, sendBuf, strlen(sendBuf) + 1, 0,
			(SOCKADDR*)&addrSrv, len);
		recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR*)&addrSrv, &len);
		if ('#' == recvBuf[0])
		{
			sendto(sockClient, "#", strlen("#") + 1, 0,
				(SOCKADDR*)&addrSrv, len);
			printf("chat end!\n");
			break;
		}
		sprintf(tempBuf, "%s say: %s", inet_ntoa(addrSrv.sin_addr), recvBuf);
		printf("%s\n", tempBuf);

	}
	closesocket(sockClient);
	WSACleanup();
}//endof main()  
