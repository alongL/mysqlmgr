#include <string>
#include <iostream>


#include "mysqlmgr.hpp"

#pragma comment(lib,"libmysql.lib")
#pragma comment(lib,"ws2_32.lib")

using namespace std;

const string  DROP_SAMPLE_TABLE = "DROP TABLE IF EXISTS test_table";
const string  CREATE_SAMPLE_TABLE = "CREATE TABLE test_table(id int, name VARCHAR(40))";
const string  INSERT_SAMPLE = "INSERT INTO test_table(id, name) VALUES(?,?)";
const string  QUERY_SAMPLE = "SELECT * FROM test_table";


void drop()
{
	auto &sqlmgr = Mysqlmgr::getinstance();

	int ret = sqlmgr.execSQL(DROP_SAMPLE_TABLE);
	if (ret == -1)
	{
		printf("drop table error! %s\n", sqlmgr.geterror());
	}
	printf("drop sucess.\n");
}

void create()
{
	auto &sqlmgr = Mysqlmgr::getinstance();
	int ret = sqlmgr.execSQL(CREATE_SAMPLE_TABLE);
	if (ret == -1)
	{
		printf("create table error! %s\n", sqlmgr.geterror());
	}
	printf("create table sucess.\n");
}

int insert()
{
	auto &sqlmgr = Mysqlmgr::getinstance();
	auto stmt = sqlmgr.getstmt(INSERT_SAMPLE);
	if (!stmt)
	{
		printf("insert error: %s", stmt.geterror());
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
		stmt.bindint(0, i);
		string name = "smith" + to_string(i);
		stmt.bindstring(1, name);
		if (stmt.execute())
		{
			printf("insert error: %s", stmt.geterror());
		}
	}
	printf("insert sucess.\n");
}

int query()
{
	auto &sqlmgr = Mysqlmgr::getinstance();
	Result r = sqlmgr.query(QUERY_SAMPLE);
	if (!r)
	{
		printf("query error %s\n", sqlmgr.geterror());
		return -1;
	}
	printf("query result:\n");
	while (Row row = r.next())
	{
		auto id = row.columnint(0);
		auto name = row.columntext(1);

		printf("id:%d, name: %s\n", id, name.c_str());
	}
}



int main(int argc, char** argv)
{
	std::string host = "localhost";
	
	/*
	run command to see result
	./test 192.168.1.200 
	
	*/
	if (argc < 2)
	{
		host = "localhost";
	}
	else
		host = argv[1];


	auto &sqlmgr = Mysqlmgr::getinstance();
	if (!sqlmgr.connect(host.c_str(), "root", "123", "goodboy", 0, 0, 0))
	{
		printf("can not connect to mysql: %s\n", sqlmgr.geterror());
		return -1;
	}
	printf("connected sucess!\n");

	
	drop();
	create();
	insert();
	query();

	
}

