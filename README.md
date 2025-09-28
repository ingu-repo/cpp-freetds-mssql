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
