#include <stdio.h>
#include <sybfront.h>
#include <sybdb.h>

DBPROCESS* init_db() {
    LOGINREC *login;
    DBPROCESS *dbproc;
    char *server = "localhost";
    char *user = "ingu";
    char *password = "m";
    char *database = "seodb";

    // Initialize DB-Library
    if (dbinit() == FAIL) {
        fprintf(stderr, "Failed to initialize DB-Library.\n");
        return NULL;
    }
    fprintf(stderr, "dbinit done !! \n");

    // dberrhandle((DBERRHANDLE_PROC) NULL);
    // dbmsghandle((DBMSGHANDLE_PROC) NULL);

    // Allocate and set up LOGINREC
    login = dblogin();
    DBSETLUSER(login, user);
    DBSETLPWD(login, password);
    fprintf(stderr, "dblogin done !! \n");

    // Connect to SQL Server
    dbproc = dbopen(login, server);
    if (dbproc == NULL) {
        fprintf(stderr, "Failed to connect to server.\n");
        dbexit();
        return NULL;
    }
    fprintf(stderr, "dbopen done !! \n");
    if (dbproc == NULL) fprintf(stderr, "oh no\n");

    // Select database
    if (dbuse(dbproc, database) == FAIL) {
        fprintf(stderr, "Failed to select database.\n");
        dbclose(dbproc);
        dbexit();
        return NULL;
    }
    fprintf(stderr, "dbuse done !! \n");
    if (dbproc == NULL) fprintf(stderr, "oh no\n");

    return dbproc;
}

