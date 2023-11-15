#include "shell.h"

/**
 * listsize - determines length of linked list
 * @h: pointer
 * Return: size of list
 */
size_t listsize(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * thelisttostr - returns an array of strings of the list->str
 * @head: pointer
 * Return: array of strings
 */
char **thelisttostr(list_t *head)
{
	list_t *node = head;
	size_t i = listsize(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = stringcp(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * despthelist - prints all elements of a list_t linked list
 * @h: pointer
 * Return: size of list
 */
size_t despthelist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convint(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * thenodstar - returns node whose string starts with prefix
 * @node: pointer
 * @prefix: string
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *thenodstar(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begwith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * thenodeloc - gets the index of a node
 * @head: pointer
 * @node: pointer
 * Return: index or -1
 */
ssize_t thenodeloc(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
