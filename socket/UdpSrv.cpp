//���ն˴���   
#include <Winsock2.h>   
#include <stdio.h>   
void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);//�汾��1.1   
									   //1.�����׽��ֿ�     
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;
	}//endof if   
	 //�ж��Ƿ����������winsocket�汾���������   
	 //�����WSACleanup��ֹwinsocket��ʹ�ò�����   
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}///endof if   
	 //2.�����׽���   
	SOCKET sockSrv = socket(AF_INET,
		SOCK_DGRAM/*���ݱ��׽���*/, 0);
	//3.�ڱ��ص�ַ��˿ڰ�   
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	//4.��������   
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];
	recvfrom(sockSrv, recvBuf, 100, 0,
		(SOCKADDR*)&addrClient, &len);
	printf("%s\n", recvBuf);
	closesocket(sockSrv);
	WSACleanup();
}//endof main()  