#include "sql_processor.h"

sql_bytecode_t* SQL_processor(char* input){
    sql_bytecode_t* bytecode = bytecode_new(); // That will be temporaly stored in RAM

    if (strncmp(input, "cc", 2)==0){
        bytecode->op = CREATE;
        strcpy (bytecode->reg3, "table1");
    }
    else if (strncmp(input, "ii", 2)==0){
        bytecode->op = INSERT;
        strcpy (bytecode->reg3, "benitez");
        *(int*)bytecode->reg4 = 21;
        *(float*)bytecode->reg5 = 70.5;
    }
    else if (strncmp(input, "ss", 2)==0){
         bytecode->op = SELECT;
         bytecode->reg4 = 0;
    }
    else if (strncmp(input, "dd", 2)==0){
        bytecode->op = DROP;
    }
    else if (strncmp(input, "CREATE", 6)==0 || strncmp(input, "create", 6)==0){
            //TODO: leia de verdade
        bytecode->op = CREATE;
        strcpy (bytecode->reg3, "table1");
    }
    else if (strncmp(input, "INSERT", 6)==0 || strncmp(input, "insert", 6)==0){
        bytecode->op = INSERT;
        strcpy (bytecode->reg3, "benitez");
        *(int*)bytecode->reg4 = 21;
        *(float*)bytecode->reg5 = 70.5;
    }
    else if (strncmp(input, "SELECT", 6)==0 || strncmp(input, "select", 6)==0){
         bytecode->op = SELECT;
         bytecode->reg2 = 0;
    }
    else if (strncmp(input, "DROP", 4)==0 || strncmp(input, "drop", 4)==0){
        bytecode->op = DROP;
    }
    else
        bytecode->op = INSERT;
    return bytecode;
}

sql_bytecode_t* bytecode_new (){
    sql_bytecode_t* bytecode = malloc (sizeof(sql_bytecode_t));
    assert(bytecode != NULL);
    bytecode->reg2 = malloc (sizeof (char)*15);
    bytecode->reg3 = malloc (sizeof (char)*10);
    bytecode->reg4 =malloc (sizeof (int));
    bytecode->reg5 = malloc (sizeof (float));
    return bytecode;
}

int bytecode_free (sql_bytecode_t* bytecode){
    free (bytecode->reg2);
    free (bytecode->reg3);
    free (bytecode->reg4);
    free (bytecode->reg5);
    free (bytecode);
    return 0;
}



