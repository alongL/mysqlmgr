# mysqlmgr
A good c++ wrapper for mysql c API.  It's very easy to use.
When I  need to access mysql in my program, I find it's boring to join sql string ,and stmt prepare is a little complicated.
I found it's hard to find a good c++ wrapper for me. 




## How to use?
Just include "mysqlmgr.hpp"  to use all the function.
You can see main.cpp for mor demo.
main.cpp shows how to use this swiss knife.



## connect to db
```
auto &sqlmgr = Mysqlmgr::getinstance();
if (!sqlmgr.connect(host.c_str(), "root", "123", "goodboy", 0, 0, 0))
{
    printf("can not connect to mysql: %s\n", sqlmgr.geterror());
    return -1;
}
```

## run sql
```
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
```

## query and get result
```
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
```



## Thanks to 
[original author ](https://github.com/pstuifzand/mysql-cpp)

[some help](https://github.com/octocat9lee/tools/mysql-cpp/mysqlcpp.h)

[help about stmt](https://github.com/2731381914/mysqlPrepare)




