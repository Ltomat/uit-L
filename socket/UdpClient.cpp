//发送端代码   
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
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	//2.发送消息   
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	sendto(sockClient, "hello", strlen("hello") + 1, 0,
		(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	closesocket(sockClient);
	WSACleanup();
}//endof main() 