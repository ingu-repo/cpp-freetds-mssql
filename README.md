C program files connecting to Microsoft SQL server and fetching data from a table by using FreeTDS library which is Sybase compatible commands usages.

# Environment
Docker needs to be running in order to bring up SQL Server.
FreeTDS package needs to be installed.
sqlcmd is a client program - optional.

# Pre-Requisite
```
brew install freetds
brew install sqlcmd
```

> info. mssql command is not supporting multi-lines sql in prompt 

# Runtime Env
```
docker start mssql
```

# Build
```
make
```

# Execute
```
./test_sel.exe 
```

# SQL Server Client
```
sqlcmd -S localhost -U ingu -P m -d seodb
```

# DB Error Handling
SQL Server（およびFreeTDS経由での接続）でデッドロックが発生した場合、<br>
エラー番号は「1205」（deadlock victim）です。<br>
このときのエラーレベル（severity level）は「13」です。

> - エラー番号: 1205
> - エラーレベル: 13
> - メッセージ例:

- test.h
```
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

extern int last_db_error;
int my_err_handler(DBPROCESS *dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr);

#endif
```

- error_handler.c
```
#include "error_handler.h"
#include <stdio.h>
#include <sybfront.h>
#include <sybdb.h>

int last_db_error = 0;

int my_err_handler(DBPROCESS *dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr) {
    last_db_error = dberr;
    fprintf(stderr, "DB-Library error %d: %s\n", dberr, dberrstr);
    return INT_CANCEL;
}
```

- main.c
```
#include "error_handler.h"
// ...他のインクルード...

int main() {
    dberrhandle(my_err_handler);
    // ...
    if (last_db_error == 1205) {
        // デッドロック処理
    }
    // ...
}
```




