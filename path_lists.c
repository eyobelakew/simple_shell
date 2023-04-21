#include "shell.h"

/**
 * _getenv - gets the value of the environmental variable "name"
 * @name: the name of the environmental variable
 *
 * Return: the value of the environmental variable, or NULL if it doesn't exist
 */
char *_getenv(const char *name)
{
    if (!name)
        return NULL;

    size_t namelen = strlen(name);

    for (char **envp = environ; *envp; envp++)
    {
        if (strncmp(name, *envp, namelen) == 0 && (*envp)[namelen] == '=')
        {
            return *envp + namelen + 1;
        }
    }

    return NULL;
}


/**
 * add_node_end - adds a new node at the end of a list
 * @head: pointer to the head of the list
 * @str: the string to be stored in the new node
 *
 * Return: a pointer to the new node, or NULL on failure
 */
list_path *add_node_end(list_path **head, char *str)
{
    list_path *new_node;
    list_path *last_node = *head;

    new_node = malloc(sizeof(list_path));
    if (new_node == NULL)
        return (NULL);

    new_node->dir = str;
    new_node->p = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return (new_node);
    }

    while (last_node->p != NULL)
        last_node = last_node->p;

    last_node->p = new_node;

    return (new_node);
}

/**
 * linkpath - creates a linked list of directories in the PATH variable
 * @path: the value of the PATH variable
 *
 * Return: a pointer to the head of the linked list
 */
list_path *linkpath(char *path)
{
    char *token, *path_cpy;
    list_path *head = NULL;
	path_cpy = strdup(path);

    token = strtok(path_cpy, ":");
    while (token != NULL)
    {
        add_node_end(&head, token);
        token = strtok(NULL, ":");
    }

    return (head);
}


/**
 * _which - searches for a file in the directories listed in "head"
 * @filename: the name of the file to search for
 * @head: a linked list of directories to search in
 *
 * Return: the full path to the file if found, or NULL if not found
 */
char *_which(char *filename, list_path *head)
{
    struct stat st;
    char *path;

    while (head != NULL)
    {
        path = malloc(strlen(head->dir) + strlen(filename) + 2);
        if (path == NULL)
            return (NULL);

        sprintf(path, "%s/%s", head->dir, filename);
        if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
            return (path);

        free(path);
        head = head->p;
    }

    return (NULL);
}

/**
 * free_list - frees a linked list of list_path nodes
 * @head: pointer to the head node of the list
 */
void free_list(list_path *head)
{
    list_path *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->p;
        free(temp->dir);
        free(temp);
    }
}






