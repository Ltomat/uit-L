//得用控制台应用程序编写一个基于TCP的面向连接的服务端应用程序   
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
	}///...if   
	 //判断是否我们请求的winsocket版本，如果不是   
	 //则调用WSACleanup终止winsocket的使用并返回   
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}///...if   
	 //2.创建套接字   
	SOCKET sockSrv = socket(AF_INET,
		SOCK_STREAM,  //创建流式套接字   
		0);  //零表示自动选择协议   
			 //3.将套接字绑定到本地地址与端口上   
	SOCKADDR_IN addrSrv;   //定义一个地址结构体的变量   
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//用htonl()方法将INADDR_ANY转换为网络字节序   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000); //指定端口号   
									//htons把u_short类型从主机字节序转换为网络字节序   
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	//SOCKADDR大小写是一样的   
	//4.设置监听   
	listen(sockSrv, 5);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		SOCKET sockConn = accept(sockSrv,
			(SOCKADDR *)&addrClient, &len);
		char sendBuf[100];
		sprintf(sendBuf, "Welcome %s to \http://blog.csdn.net/teshorse",inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		printf("%s\n", recvBuf);
		closesocket(sockConn);
	}
}