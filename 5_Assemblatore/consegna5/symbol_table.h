#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#define DEFAULT_SYMBOLS 23

//include all necessary library
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//define the struct that contains the details of a symbol
struct symbol{
    char name[64];
    int address;
};

//define the symbol list
struct symbol_table{
    struct symbol s;
    struct symbol_table *next;
};

//array that contains 23 default symbols
extern const struct symbol defaultSymbols[];

//copy a symbol (like strcpy)
void symbol_copy(struct symbol *dest, const struct symbol src);

//init a struct list (dinamic, not static) with default symbols
struct symbol_table *init_table();

//append at a struct list a symble_table (symbol e next)
struct symbol_table *tail_insert(struct symbol_table *t, const struct symbol p);

//return 1 if a symbol (name) is in a table (tab), else 0
int is_in_tab(const struct symbol_table *tab, const char *name);

//get an address from the symbol table tab by name 
int get_address(const struct symbol_table *tab, const char *name);


#endif