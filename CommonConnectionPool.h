#pragma once
#include"string"
#include"queue"
#include"mutex"
#include"Connection.h"
#include"atomic"
#include"thread"
using namespace std;
/* ʵ�����ӳ�ģ��
*/
class ConnectionPool {


public:
	//��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool();

private:
	ConnectionPool() {}//����ģʽ�����캯��˽�л�
	bool loadConfigFile();//�������ļ�����������

	string ip;//mysql ip
	unsigned short port;//mysql�˿ں�
	string username;//MySQL�û���
	string password;//MySQL����
	string dbname;//�������ݿ�����
	int initSize;//���ӳس�ʼ������
	int maxSize;//���ӳ����������
	int maxIdleTime;//���ӳ�������ʱ��
	int ConnectionTimeout;//���ӳػ�ȡ���ӵĳ�ʱʱ��


	queue<Connection*> connectionQue;//�洢MySQL���Ӷ���
	mutex queMutex;//ά���̰߳�ȫ�Ļ�����
	atomic_int connectionCnt;//��¼��������connection���ӵ�������


};