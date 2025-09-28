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
