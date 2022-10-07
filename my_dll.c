#include "my_dll.h"
#include "headers.h"
void insert(dll *list, int x, char *namex, int number)
{
    //  if there is no node initially
    if (list->last == NULL)
    {
        list->last = (node *)malloc(sizeof(node));
        list->root->next = list->last;
        list->last->data = x;
        list->last->name = (char *)malloc(sizeof(char) * 1000);
        strcpy(list->last->name, namex);
        list->last->process_number = number;
        list->last->next = NULL;
        list->last->prev = list->root;
        return;
    }
    // if there are nodes before
    list->last->next = (node *)malloc(sizeof(node));
    list->last->next->data = x;
    list->last->next->name = (char *)malloc(sizeof(char) * 1000);
    strcpy(list->last->next->name, namex);
    list->last->next->process_number = number;
    list->last->next->prev = list->last->prev->next;
    list->last = list->last->next;
    list->last->next = NULL;
    return;
}

void delete (dll *list, int chpid)
{
    char name_of_process[1000];
    int number;
    int i = find(list, chpid, name_of_process, &number);
    i--;
    int count = 0;
    node *temp = list->root->next;
    // if we need to delete node from the first position
    if (i == 0)
    {
        // if there is no node from before
        if (temp->next == NULL)
        {
            list->last = NULL;
            free(list->root);
            list->root = NULL;
            list->root = (node *)malloc(sizeof(node));
            list->root->next = NULL;
            return;
        }
        // if there is node from before
        node *temp2 = list->root->next;
        list->root->next = list->root->next->next;
        list->root->next->prev = list->root;
        free(temp2);
        return;
    }
    // make temp point at the node prev to the required node
    while (1)
    {
        count++;
        if (count == i)
        {
            break;
        }
        temp = temp->next;
    }
    // if we delete from the end
    if (temp->next->next == NULL)
    {
        free(temp->next);
        temp->next = NULL;
        list->last = temp;
        return;
    }
    // if we delete anywhere inside the linked list
    temp->next->next->prev = temp;
    node *temp2 = temp->next;
    temp->next = temp->next->next;
    free(temp2);
    return;
}

int find(dll *list, int x, char *name_of_process, int *number)
{
    int count = 0;
    node *temp = list->root->next;
    while (1)
    {
        count++;
        if (temp == NULL)
        {
            return 0;
        }
        //  return 0 if the required number is not present
        if (temp->data == x)
        {
            strcpy(name_of_process, temp->name);
            (*number) = temp->process_number;
            break;
        }
        temp = temp->next;
    }
    return count;
}

int get_size(dll *list)
{
    int count = 0;
    node *temp = list->last;
    if (temp == NULL)
    {
        return 0;
    }
    while (1)
    {
        if (temp->prev == NULL)
        {
            break;
        }
        count++;
        temp = temp->prev;
    }
    return count;
}
void find_max(dll *list, int *max_number_of_processes)
{
    int max = 0;
    node *temp = list->last;
    if (temp == NULL)
    {
        (*max_number_of_processes) = 0;
        return;
    }
    while (1)
    {
        if (temp->prev == NULL)
        {
            break;
        }
        max = max > temp->process_number ? max : temp->process_number;
        temp = temp->prev;
    }
    (*max_number_of_processes) = max;
    return;
}
int find_via_process_number(dll *list, int x, char *name_of_process)
{
    int count = 0;
    node *temp = list->root->next;
    while (1)
    {
        count++;
        if (temp == NULL)
        {
            return 0;
        }
        if (temp->process_number == x)
        {
            strcpy(name_of_process, temp->name);
            return temp->data;
            break;
        }
        temp = temp->next;
    }
    return count;
}
void delete_all_background(dll *list)
{
    node *temp = list->last;
    if (temp == NULL)
    {
        return;
    }
    while (1)
    {
        if (temp->prev == NULL)
        {
            break;
        }
        kill(temp->data, SIGKILL);
        temp = temp->prev;
    }
    return;
}