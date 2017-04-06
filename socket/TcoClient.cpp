
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
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	//3.连接服务器端，无须绑定   
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//设定服务器端IP地址，"127.0.0.1"是本地回路地址   
	//不管本地主机上有没有网卡，都可以用这个IP测试网络   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000); //端口号要与服务器端保持一致   
	connect(sockClient, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	//4.接收服务器端发送的数据,并且向服务器端发送数据   
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s \n", recvBuf);
	send(sockClient, "I'm teshorse", strlen("I'm teshorse") + 1, 0);
	//5.关闭套接字，释放资源,并且终止对套接字库的使用   
	closesocket(sockClient);
	WSACleanup();
}//endof main()  