//接收端代码   
#include <Winsock2.h>   
#include <stdio.h>   
void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);//版本号1.1   
									   //1.加载套接字库     
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;
	}//endof if   
	 //判断是否我们请求的winsocket版本，如果不是   
	 //则调用WSACleanup终止winsocket的使用并返回   
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}///endof if   
	 //2.创建套接字   
	SOCKET sockSrv = socket(AF_INET,
		SOCK_DGRAM/*数据报套接字*/, 0);
	//3.在本地地址与端口绑定   
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	//4.接收数据   
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	recvfrom(sockSrv, recvBuf, 100, 0,
		(SOCKADDR*)&addrClient, &len);
	printf("%s\n", recvBuf);
	closesocket(sockSrv);
	WSACleanup();
}//endof main()  