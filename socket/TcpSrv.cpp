//���ÿ���̨Ӧ�ó����дһ������TCP���������ӵķ����Ӧ�ó���   
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
	}///...if   
	 //�ж��Ƿ����������winsocket�汾���������   
	 //�����WSACleanup��ֹwinsocket��ʹ�ò�����   
	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}///...if   
	 //2.�����׽���   
	SOCKET sockSrv = socket(AF_INET,
		SOCK_STREAM,  //������ʽ�׽���   
		0);  //���ʾ�Զ�ѡ��Э��   
			 //3.���׽��ְ󶨵����ص�ַ��˿���   
	SOCKADDR_IN addrSrv;   //����һ����ַ�ṹ��ı���   
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//��htonl()������INADDR_ANYת��Ϊ�����ֽ���   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000); //ָ���˿ں�   
									//htons��u_short���ʹ������ֽ���ת��Ϊ�����ֽ���   
	bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));
	//SOCKADDR��Сд��һ����   
	//4.���ü���   
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