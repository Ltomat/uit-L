
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
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	//3.���ӷ������ˣ������   
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//�趨��������IP��ַ��"127.0.0.1"�Ǳ��ػ�·��ַ   
	//���ܱ�����������û�������������������IP��������   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000); //�˿ں�Ҫ��������˱���һ��   
	connect(sockClient, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	//4.���շ������˷��͵�����,������������˷�������   
	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s \n", recvBuf);
	send(sockClient, "I'm teshorse", strlen("I'm teshorse") + 1, 0);
	//5.�ر��׽��֣��ͷ���Դ,������ֹ���׽��ֿ��ʹ��   
	closesocket(sockClient);
	WSACleanup();
}//endof main()  