#pragma once
#include"string"
#include"queue"
#include"mutex"
#include"Connection.h"
#include"atomic"
#include"thread"
using namespace std;
/* 实现连接池模块
*/
class ConnectionPool {


public:
	//获取连接池对象实例
	static ConnectionPool* getConnectionPool();

private:
	ConnectionPool() {}//单例模式，构造函数私有化
	bool loadConfigFile();//从配置文件加载配置项

	string ip;//mysql ip
	unsigned short port;//mysql端口号
	string username;//MySQL用户名
	string password;//MySQL密码
	string dbname;//连接数据库名称
	int initSize;//连接池初始连接量
	int maxSize;//连接池最大连接量
	int maxIdleTime;//连接池最大空闲时间
	int ConnectionTimeout;//连接池获取连接的超时时间


	queue<Connection*> connectionQue;//存储MySQL连接队列
	mutex queMutex;//维护线程安全的互斥锁
	atomic_int connectionCnt;//记录所创建的connection连接的总数量


};