#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

const size_t BUFFER_SIZE = 80;

struct node_t_;
typedef struct node_t_
{
    char* data;
    struct node_t_* next;
} node_t;

void on_error(const char* message)
{
    printf("%s with code %d (%s), aborted.\n", message, errno, strerror(errno));
    exit(1);
}

int add_node(node_t** root, void* data)
{
    node_t* node = (node_t*) malloc(sizeof(node_t));
    
    if (!node)
    {
        return 1;
    }
    
    node->data = data;
    node->next = *root;
    *root = node;
    return 0;
}

void delete_list(node_t** root)
{
    node_t* next;

    while (*root)
    {
        next = (*root)->next;
        free((*root)->data);
        free(*root);
        *root = next;
    }
}

node_t* read_lines(char* buffer)
{
    node_t* root = (node_t*) NULL;
    int stop = 0;

    while (!stop)
    {
        char* read = fgets(buffer, BUFFER_SIZE, stdin);
        
        if (!read)
        {
            on_error("Reading error");
        }

        stop = (read[0] == '.')? 1 : 0;
        char* data = strdup((const void*) (read + stop));

        if (!data)
        {
            on_error("Memory allocation failed");
        }
        
        if (add_node(&root, data))
        {
            on_error("Can't insert a node");
        }

    }

    return root;
}

void write_lines(const node_t* root)
{
    if (root)
    {
        write_lines(root->next);
        printf(root->data);
    }
}

int main()
{
    char buffer[BUFFER_SIZE];
    node_t* lines = read_lines(buffer);
    write_lines(lines);
    delete_list(&lines);
}

