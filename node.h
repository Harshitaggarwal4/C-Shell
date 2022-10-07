#ifndef __node__
#define __node__
typedef struct _node
{
    int data;
    char *name;
    int process_number;
    struct _node *prev;
    struct _node *next;
} node;
#endif