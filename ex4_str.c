#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

const size_t BUFFER_SIZE = 200;

typedef struct node {
    char* data;
    struct node* next;
} node;

void catchError(node** head)
{
	deleteList(head);
    printf("%d %s", errno, strerror(errno));
    exit(-1);
}

int pushNode(node** head, char* data) //data это указатель!!!
{
    node* newNode = (node*) malloc(sizeof(node)); 
    if (!newNode) return -1; //pushNode вернет ошибку, если не смог вернуть память под конкретный новый узел  
    newNode->data = data;
    newNode->next = *head;
    *head = newNode; //значение head это указатель!!!!!!!
    return 0;
}

void deleteList(node** head)
{
    node* next;

    while (*head)
    {
        next = (*head)->next;
        free((*head)->data); //удалили строку
        free(*head); //очистили память под саму структуру
        *head = next;
    }
}

node* readLines(char* buffer)
{
	node* head = (node*) NULL;
    while (1)
    {
        char* line = fgets(buffer, BUFFER_SIZE, stdin);   
        if (!line) //не получилось считать строчку
        {
        	deleteList(head);
        	printf("%d %s", errno, strerror(errno));
    		exit(-1);
        }
        if (line[0] == '.') break;
        char* data = strndup((const char*) line, strlen(line));
        // The  strdup()  function returns a pointer to a new string which is a duplicate of the string s.  
        //Memory for the new string is obtained with malloc(3), and can be freed with free(3).
		//The strndup() function is similar, but copies at most n bytes.  
		//If s is longer than n, only n bytes are copied, and a terminating null byte ('\0') is added.

        if (!data)
        {
        	deleteList(head);
        	printf("%d %s", errno, strerror(errno));
    		exit(-1);
        }
        if (pushNode(&head, data) == -1)
        {
        	deleteList(head);
        	free(data);
        	printf("%d %s", errno, strerror(errno));
    		exit(-1);
        }
    }
    return head;
}

void printLines(const node* head)
{
    if (head)
    {
    	printLines(head->next);
        printf(head->data);
    }
}

int main()
{
	char* buffer = (char*) malloc(BUFFER_SIZE);
    node* lines = readLines(buffer);
    printLines(lines);
    deleteList(&lines);
    free(buffer);
}