#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sybfront.h>
#include <sybdb.h>

typedef struct {
    int employee_id;
    char first_name[100];
    char last_name[100];
    int department_id;
} Employee;

extern DBPROCESS* init_db();
int get_data(DBPROCESS *dbproc, Employee **employees);

int main() {
    DBPROCESS *dbproc = NULL;

    fprintf(stderr, "starting !! \n");

    // DB Login
    dbproc = init_db();
    if (dbproc == NULL) {
        fprintf(stderr, "Database connection failed.\n");
        return 1;
    }
    fprintf(stderr, "db logged in !! \n");

    // Get table data
    Employee **employees = NULL;
    employees = (Employee**)malloc(sizeof(Employee));
    Employee** init_pos = employees;

    int employee_count = get_data(dbproc, employees);
    fprintf(stderr, "get_data done\n");

    // Print all employees
    employees = init_pos;
    for (int i = 0; i < employee_count; i++) {
        // fprintf(stderr, "employee_count=%d|\n", i);
        // fprintf(stderr, "name=%s|\n",employees[i]->first_name);
        fprintf(stderr, "%d|%s|%s|%d\n"
            , employees[i]->employee_id
            , employees[i]->first_name
            , employees[i]->last_name
            , employees[i]->department_id
        );
    }

    // Free the allocated memory
    free(employees);
    dbclose(dbproc);
    dbexit();
    
    return 0;
}

int get_data(DBPROCESS *dbproc, Employee **employees) {
    char *query = "SELECT EmployeeID, FirstName, LastName, DepartmentID FROM Employees";

    // Bind columns to variables for each row
    Employee buff;
    // int employee_id;
    // char first_name[100];
    // char last_name[100];
    // int department_id;

    // Execute query: first prepare the command, then execute it separately
    if (dbcmd(dbproc, query) == FAIL) {
        fprintf(stderr, "Failed to prepare query.\n");
        dbclose(dbproc);
        dbexit();
        return 1;
    }
    fprintf(stderr, "dbcmd done !! \n");
    
    if (dbsqlexec(dbproc) == FAIL) {
        fprintf(stderr, "Failed to execute query.\n");
        dbclose(dbproc);
        dbexit();
        return 1;
    }
    fprintf(stderr, "dbsqlexec done !! \n");

    dbbind(dbproc, 1, INTBIND, 0, (BYTE *)&buff.employee_id);
    dbbind(dbproc, 2, NTBSTRINGBIND, sizeof(buff.first_name), (BYTE *)&buff.first_name);
    dbbind(dbproc, 3, NTBSTRINGBIND, sizeof(buff.last_name), (BYTE *)&buff.last_name);
    dbbind(dbproc, 4, INTBIND, 0, (BYTE *)&buff.department_id);

    int row_count = 0;
    while (dbresults(dbproc) != NO_MORE_RESULTS) {
        while (dbnextrow(dbproc) != NO_MORE_ROWS) {

            fprintf(stderr, "row_count=%d|%d|%s|%s|%d|\n", row_count,buff.employee_id,buff.first_name,buff.last_name,buff.department_id);

            Employee *employee = (Employee *)malloc(sizeof(Employee));
            memcpy(employee,&buff,sizeof(Employee));
            
            *employees = employee;
            fprintf(stderr, "row_count=%d|%d|%s|%s|%d|\n", row_count,(*employees)->employee_id,(*employees)->first_name,(*employees)->last_name,(*employees)->department_id);

            employees++;
            row_count++;
        }
    }
    fprintf(stderr, "dbnextrow done !!\n");

    return row_count;
}
