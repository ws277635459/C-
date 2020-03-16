#include"CommonConnectionPool.h"
#include"public.h"

//线程安全的懒汉单例函数接口
ConnectionPool* ConnectionPool::getConnectionPool()
{
	//懒汉单例模式
	static ConnectionPool pool;//lock和unlock
	return &pool;

}

//从配置文件加载配置项
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
		if (idx == -1)//无效的配置项
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

//连接池的构造
ConnectionPool::ConnectionPool()
{

	if (!loadConfigFile())
	{
		return;
	}
	//创建初始数量的连接
	for (int i = 0; i < initSize; ++i)
	{
		Connection* p = new Connection();
		p->connect(ip,port, username, password, dbname);
		connectionQue.push(p);
		connectionCnt++;
	}
	//启动一个新的生产者，作为连接的生产者



}