#ifndef SQL_PROCESSOR
#define SQL_PROCESSOR

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

enum sql_bytecode_op {
    CREATE, SELECT, INSERT, DROP, DELETE
} sql_bytecode_op;

struct Sql_bytecode {
    enum sql_bytecode_op op;
    void* reg2;
    void* reg3;
    void* reg4;
    void* reg5;
};

typedef struct Sql_bytecode sql_bytecode_t;

/*****
@brief Processa uma string pseudo-SQL e retorna um bytecode
Documentação do pseudo-SQL (os comandos reais não são case-sensitive):
CREATE <tname>
    Comando real
    cria uma tabela com nome <table1>
    o nome da tabela pode ter até 15 caracteres
INSERT <name>, <age>, <weight>
    Comando real
    Inserse uma linha com os dados enviados
    o nome da pessoa pode ter até 10 caracteres
    age é um inteiro
    weight é um float
    Os parâmetros devem ser inseridos nessa ordem, sem elementos nulos
SELECT <id>
    Comando real
    Seleciona a primeira linha <id>
cc
    Comando para debug
    cria uma tabela com nome "table1"
ii
    Comando para debug
    Inserse uma linha (benitez, 21, 70.5)
ss
    Comando para debug
    Seleciona a primeira linha (id=0)
dd
    Comando para debug
    deleta a tabela a saí do programa

Documentação do bytecode:
Se op = CREATE, reg2=tname;
Se op = INSERT, reg2=tname, reg3=nome,  reg4=age, reg5=weight;
Se op = SELECT, reg2=tname,,            reg4=id;
Se op = DELETE, reg2=tname,,            reg4=id;
TODO: change reg3 to reg2
*****/
sql_bytecode_t* SQL_processor(char* input);
sql_bytecode_t* bytecode_new ();
int bytecode_free (sql_bytecode_t* bytecode);

#endif
