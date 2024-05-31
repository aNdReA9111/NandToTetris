#include "symbol_table.h"

const struct symbol defaultSymbols[DEFAULT_SYMBOLS] = {
    "SP", 0, "LCL", 1, "ARG", 2,
    "THIS", 3, "THAT", 4, "R0", 0,
    "R1", 1, "R2", 2, "R3", 3, "R4", 4,
    "R5", 5, "R6", 6, "R7", 7, "R8", 8,
    "R9", 9, "R10", 10, "R11", 11,
    "R12", 12, "R13", 13, "R14", 14, "R15", 15,
    "SCREEN", 0x4000, "KBD", 0x6000};

void symbol_copy(struct symbol *dest, const struct symbol src)
{
    strcpy(dest->name, src.name);
    dest->address = src.address;
}

struct symbol_table *init_table()
{
    struct symbol_table *head = malloc(sizeof(struct symbol_table));
    symbol_copy(&head->s, defaultSymbols[0]);
    head->next = NULL;
    struct symbol_table *p = head;
    for (size_t i = 1; i < DEFAULT_SYMBOLS; ++i)
    {
        p->next = malloc(sizeof(struct symbol_table));
        p = p->next;
        symbol_copy(&p->s, defaultSymbols[i]);
        p->next = NULL;
    }
    return head;
}

struct symbol_table *tail_insert(struct symbol_table *t, const struct symbol p)
{
    struct symbol_table *back = t;
    while (back->next)
        back = back->next;

    back = back->next = malloc(sizeof(struct symbol_table));

    symbol_copy(&back->s, p);
    back->next = NULL;
    return t;
}

int is_in_tab(const struct symbol_table *tab, const char *name)
{
    int is_in = 0;
    while (tab && !is_in)
    {
        if (!strcmp(tab->s.name, name))
            is_in = 1;

        tab = tab->next;
    }
    return is_in;
}

int get_address(const struct symbol_table *tab, const char *name)
{
    int address = -1;
    while (tab)
    {
        if (!strcmp(tab->s.name, name) && address == -1)
            address = tab->s.address;

        tab = tab->next;
    }
    return address;
}