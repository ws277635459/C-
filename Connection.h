#pragma once
#include"string"
#include"mysql.h"
using namespace std;

/*
实现MySQL数据库的增删改查
*/
class Connection {
public:
	//初始化数据库连接
	Connection();
	//释放数据库连接资源
	~Connection();
	//连接数据库
	bool connect(string ip, unsigned short port, string user, string password, string dbname);
	//更新操作insert,delete,update
	bool update(string sql);
	//查询select
	MYSQL_RES* query(string sql);


private:
	MYSQL* _conn;//表示和MySQL Server的连接

};