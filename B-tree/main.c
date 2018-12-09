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

int SQL_create (sql_bytecode_t* bytecode, BTree** Tcursor);
int SQL_insert (sql_bytecode_t* bytecode, BTree* Tcursor);
int SQL_select(sql_bytecode_t* bytecode, BTree* Tcursor);
int SQL_delete(sql_bytecode_t* bytecode, BTree* Tcursor);
int SQL_drop (sql_bytecode_t* bytecode, BTree* Tcursor);

int main() {
	char input_buffer [MAX_INPUT];
    sql_bytecode_t* bytecode;
    BTree *Tcursor; // será utilizado na aplicação inteira para armazenar o DB

    printf("BenitezSQL Command Line Interface\n");
	printf("---------------------------------\n\n");

    /* BenitezSQL Virtual Machine */
	while (1) {
	    printf("SQL> ");
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
            SQL_delete(bytecode, Tcursor);
            break;
        case ERROR:
            printf ("Sorry, invalid SQL\n\n");
            break;
        case DROP:
            SQL_drop (bytecode, Tcursor);
            printf("Exiting BenitezSQL\n\n");
            return 0;

		}
	}
}


int SQL_create (sql_bytecode_t* bytecode, BTree** Tcursor){
    #ifdef INPUT_ECO
    printf("CREATE TABLE %s (\n\
            \t integer row_id primary key, \n\
            \t varchar[10] name,           \n\
            \t integer age,                \n\
            \t real weight                 \n\
    )\n\n", (char*)getReg3(bytecode));
    #endif // INPUT_ECO

    *Tcursor = btree_new(getReg3(bytecode), MIN_DEGREE);
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
    static int key = 0; //Autoincrement rowid
    page_t* page;

    page = pageNew();
    pageSetRowId (page, key);
    pageSetName (page, getReg3(bytecode));
    pageSetAge (page, (int*)getReg4(bytecode));
    pageSetWeight (page, (float*)getReg5(bytecode));

    #ifdef INPUT_ECO
    printf("INSERT INTO %s ( \n\
                \t name, \n\
                \t age, \n\
                \t weight \n\
            ) VALUES (\n\
                \t %s, \n\
                \t %d, \n\
                \t %f, \n\
            );\n\n",
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
    if (Tcursor == NULL){
        printf ("SQL_insert: invalid table\n");
        exit (1);
    }

	node_position pos;
    page_t* page;

    #ifdef INPUT_ECO
    printf("SELECT * FROM %s \n\
            WHERE row_id=0;\n\n",
            btree_get_name(Tcursor)
    );
    #endif // INPUT_ECO

    pos = btree_find(Tcursor, *(int*)getReg4(bytecode));
    if (pos.node == NULL){
        printf ("Returned 0 rows\n\n");
        return 0;
    }
    page = node_get_value(pos);
    printf(" returned row %d: %s, %d, %f\n",
            pageGetRowId(page),
            pageGetName(page),
            pageGetAge(page),
            pageGetWeight(page)
    );
    bytecode_free(bytecode);
	return 0;
}

int SQL_delete(sql_bytecode_t* bytecode, BTree* Tcursor){
    if (Tcursor == NULL){
        printf ("SQL_insert: invalid table\n");
        exit (1);
    }

    node_position pos;

    #ifdef INPUT_ECO
    printf("DELETE * FROM %s;\n\
            WHERE row_id=%d\n",
            btree_get_name(Tcursor),
            *(int*)getReg4(bytecode)
    );
    #endif // INPUT_ECO
    pos = btree_remove(Tcursor, *(int*)getReg4(bytecode));
    if (pos.node == NULL) {
        printf("0 row removed\n\n");
    }
    else {
        printf("1 row removed\n\n");
    }
    bytecode_free(bytecode);
    return 0;
}

int SQL_drop (sql_bytecode_t* bytecode, BTree* Tcursor){
    if (Tcursor == NULL){
        printf ("SQL_insert: invalid table\n");
        exit (1);
    }

    #ifdef INPUT_ECO
    printf("DROP TABLE %s;\n\n", btree_get_name(Tcursor));
    #endif // INPUT_ECO

    btree_delete_h(Tcursor);
    bytecode_free(bytecode);
    return 0;
}

