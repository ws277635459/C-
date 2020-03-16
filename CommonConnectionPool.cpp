#include"CommonConnectionPool.h"
#include"public.h"

//�̰߳�ȫ���������������ӿ�
ConnectionPool* ConnectionPool::getConnectionPool()
{
	//��������ģʽ
	static ConnectionPool pool;//lock��unlock
	return &pool;

}

//�������ļ�����������
bool ConnectionPool::loadConfigFile()
{
	FILE* pf = fopen("mysql.ini", "r");
	if (pf == nullptr)
	{


		LOG("mysql.ini file is not exist!");
		return false;
	}
	while (!feof(pf))
	{
		char line[1024] = { 0 };
		fgets(line, 1024, pf);
		string str = line;
		int idx = str.find('=', 0);
		if (idx == -1)//��Ч��������
		{
			continue;
		}
		
		int endidx = str.find('\n', idx);
		string key = str.substr(0, idx);
		string value = str.substr(idx + 1, endidx - idx - 1);

		if (key == "_ip")
		{
			ip = value;
		}
		else if (key == "_port")
		{
			port = atoi(value.c_str());
		}
		else if (key == "_username")
		{
			username = value;
		}
		else if (key == "_password")
		{
			password = value;
		}
		else if (key == "_dbname")
		{
			dbname = atoi(value.c_str());
		}
		else if (key == "_initSize") 
		{
			initSize = atoi(value.c_str());
		}
		else if (key == "_maxSize")
		{
			maxSize = atoi(value.c_str());
		}
		else if (key == "_maxIdleTime")
		{
			maxIdleTime = atoi(value.c_str());
		}
		else if (key == "_connectionTimeOut")
		{
			ConnectionTimeout = atoi(value.c_str());
		}

	}



	return true;

}

//���ӳصĹ���
ConnectionPool::ConnectionPool()
{

	if (!loadConfigFile())
	{
		return;
	}
	//������ʼ����������
	for (int i = 0; i < initSize; ++i)
	{
		Connection* p = new Connection();
		p->connect(ip,port, username, password, dbname);
		connectionQue.push(p);
		connectionCnt++;
	}
	//����һ���µ������ߣ���Ϊ���ӵ�������



}