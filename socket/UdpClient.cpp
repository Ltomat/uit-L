//���Ͷ˴���   
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
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	//2.������Ϣ   
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	sendto(sockClient, "hello", strlen("hello") + 1, 0,
		(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	closesocket(sockClient);
	WSACleanup();
}//endof main() 