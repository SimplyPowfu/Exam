#include "list.h"

void	swap_values(t_list *a, t_list *b)
{
	int swap = a->data;
	a->data = b->data;
	b->data = swap;
}

int ascending(int a, int b)
{
	return (a <= b);
}

t_list  *sort_list(t_list* lst, int (*cmp)(int, int))
{
	int swapped = 1;
	t_list *tmp = lst;

	while (swapped == 1)
	{
		swapped = 0;
		while (tmp != 0 && tmp->next != 0)
		{
			if (cmp(tmp->data, tmp->next->data) == 0)
			{
				swap_values(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		tmp = lst;
	}
	return (lst);
}

int main()
{
	t_list *Head;
	t_list *tmp;

	Head = malloc(sizeof(t_list));
	Head->data = 4;
	Head->next = malloc(sizeof(t_list));
	Head->next->data = 2;
	Head->next->next = malloc(sizeof(t_list));
	Head->next->next->data = 3;
	Head->next->next->next = malloc(sizeof(t_list));
	Head->next->next->next->data = 1;

	printf("%d,", Head->data);
	printf("%d,", Head->next->data);
	printf("%d,", Head->next->next->data);
	printf("%d\n", Head->next->next->next->data);

	tmp = Head;
	tmp = sort_list(tmp, ascending);
	printf("%d,", tmp->data);
	printf("%d,", tmp->next->data);
	printf("%d,", tmp->next->next->data);
	printf("%d\n", tmp->next->next->next->data);
}
