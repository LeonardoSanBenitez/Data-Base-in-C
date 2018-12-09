#ifndef SQL_PROCESSOR
#define SQL_PROCESSOR

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

enum sql_bytecode_op {
    CREATE, SELECT, INSERT, DROP, DELETE, ERROR
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
del
    Comando para debug
    delete a primeira linha (id=0)
dd
    Comando para debug
    deleta a tabela a saí do programa

Documentação do bytecode:
Se op = CREATE, reg2=tname;
Se op = INSERT, reg2=tname, reg3=nome,  reg4=age, reg5=weight;
Se op = SELECT, reg2=tname,,            reg4=id; (if select *, id=-1)
Se op = DELETE, reg2=tname,,            reg4=id;
TODO: change reg3 to reg2
*****/
sql_bytecode_t* SQL_processor(char* input);
sql_bytecode_t* bytecode_new ();
void* getReg2 (sql_bytecode_t* bytecode);
void* getReg3 (sql_bytecode_t* bytecode);
void* getReg4 (sql_bytecode_t* bytecode);
void* getReg5 (sql_bytecode_t* bytecode);
int bytecode_free (sql_bytecode_t* bytecode);

#endif
