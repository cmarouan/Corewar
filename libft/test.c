#include "libft.h"
#include <stdio.h>
#include <limits.h>
int main(int argc, char **argv)
{
	t_list *list;
	t_list *node;
	t_list *head;
	int     number;

	number = -1;
	list = NULL;
	while (++number < 1000000)
	{
		if (!(node = (t_list *)ft_lstnew((void *)&number, sizeof(int))))
			return (1);
		ft_lstadd(&list, node);
	}
	head = list;
	while (head)
	{
		printf("%d\n", *((int *)head->content));
		head = head->next;
	}
}
