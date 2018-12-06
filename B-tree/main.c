/*
SUPOSIÇÕES
ordem correta das querys
busca se da unicamente pelo id serial
*/

#include <stdlib.h>
#include <stdio.h>
//#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "btree.h"
#include "sql_processor.h"
#include "pager.h"


#define MSG_LEN 100
#define MAX_INPUT 128
#define MIN_DEGREE 2

#define INPUT_ECO


int SQL_create (sql_bytecode_t* bytecode, BTree** Tcursor){
    #ifdef INPUT_ECO
    printf("CREATE TABLE %s (\n\
            \t integer row_id primary key, \n\
            \t varchar[10] name,           \n\
            \t integer age,                \n\
            \t real weight                 \n\
    )\n", (char*)bytecode->reg3);
    #endif // INPUT_ECO

    *Tcursor = btree_new(bytecode->reg3, MIN_DEGREE);
    bytecode_free(bytecode);
    if (Tcursor != NULL){
        printf("sucess: 1 table affected (%p)\n\n", Tcursor);
        return 0;
    } else {
        printf("fail: 0 table affected\n\n");
        return -1;
    }
}

int SQL_insert (sql_bytecode_t* bytecode, BTree* Tcursor){
    if (Tcursor == NULL){
        printf ("SQL_insert: invalid table\n");
        exit (1);
    }
    node_position pos;
    static int key = 0;
    page_t* page;

    page = pageNew();
    pageSetRowId (page, key);
    pageSetName (page, bytecode->reg3);
    pageSetAge (page, (int*)bytecode->reg4);
    pageSetWeight (page, (float*)bytecode->reg5);

    #ifdef INPUT_ECO
    printf("INSERT INTO %s ( \n\
                \t name, \n\
                \t age, \n\
                \t weight \n\
            ) VALUES (\n\
                \t %s, \n\
                \t %d, \n\
                \t %f, \n\
            );\n",
            btree_get_name(Tcursor),
            pageGetName (page),
            pageGetAge (page),
            pageGetWeight (page)
    );
    #endif
    pos = btree_insert(Tcursor, key, page);
    bytecode_free(bytecode);
    if (pos.node == NULL) {
        printf ("fail: 0 row affected\n\n");
        return -1;
    }
    else {
        printf ("sucess: 1 row affected\n\n");
        key++;
        return 0;
    }
}

int SQL_select(sql_bytecode_t* bytecode, BTree* Tcursor){
	node_position pos;

    pos = btree_find(Tcursor, *(int*)bytecode->reg4);
    page_t* value;
    page = node_get_value(pos);
    //TODO: verificar se a linha existe
    printf(" returned row %d: %s, %d, %f\n",
            pageGetRowId(page),
            pageGetName(page),
            pageGetAge(page),
            pageGetWeight(page)
    );
	return 0;
}



int main() {
	char input_buffer [MAX_INPUT];
    sql_bytecode_t* bytecode;
    BTree *Tcursor; // será utilizado na aplicação inteira para armazenar o DB


    printf("BenitezSQL Command Line Interface\n");
	printf("---------------------------------\n\n");

    /* BenitezSQL Virtual Machine */
	while (1) {
	    //scanf("%d%*c", &opt);
	    fgets (input_buffer, MAX_INPUT, stdin);
	    bytecode = SQL_processor(input_buffer);
		switch (bytecode->op) {
		case CREATE:
			SQL_create(bytecode, &Tcursor);
			break;
		case INSERT:
			SQL_insert(bytecode, Tcursor);
			break;
		case SELECT:
            SQL_select(bytecode, Tcursor);
            break;
		case DELETE:
		case DROP:
            printf("Exiting BenitezSQL\n\n");
            btree_delete_h(Tcursor);
            bytecode_free(bytecode);
            exit(EXIT_SUCCESS);
            break;
		}
	}



	return 0;
}
