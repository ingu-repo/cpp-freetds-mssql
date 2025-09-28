#include <stdio.h>
#include <stdlib.h>
#include <sybfront.h>
#include <sybdb.h>

int main() {
    LOGINREC *login;
    DBPROCESS *dbproc;

    dbinit();
    login = dblogin();
    DBSETLUSER(login, "your_username");
    DBSETLPWD(login, "your_password");
    DBSETLAPP(login, "RAISERROR_TEST");

    dbproc = dbopen(login, "your_server");
    if (dbproc == NULL) {
        fprintf(stderr, "Failed to connect to server.\n");
        return 1;
    }

    if (dbcmd(dbproc, "RAISERROR(1205, 13, 1)") == FAIL) {
        fprintf(stderr, "Failed to prepare RAISERROR command.\n");
        dbclose(dbproc);
        dbexit();
        return 1;
    }
    if (dbsqlexec(dbproc) == FAIL) {
        fprintf(stderr, "Failed to execute RAISERROR command.\n");
        dbclose(dbproc);
        dbexit();
        return 1;
    }

    while (dbresults(dbproc) != NO_MORE_RESULTS) {
        // Consume all results
    }

    dbclose(dbproc);
    dbexit();
    return 0;
}
