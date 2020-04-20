#include "lem_in.h"

void	clean_out(t_game *g)
{
	t_list	*next;
	t_list	*node;

	node = g->out_or_error;
	while (node)
	{
		next = node->next;
		free(node->content);
		free(node);
		node = next;
	}
	g->out_or_error = NULL;
}

void	reverse_list(t_list **begin)
{
	t_list	*back;
	t_list	*node;
	t_list	*go;

	if (!begin || !*begin || !((*begin)->next))
		return ;
	node = (*begin);
	go = node->next;
	node->next = NULL;
	back = node;
	while (go)
	{
		node = go;
		go = node->next;
		node->next = back;
		back = node;
	}
	*begin = node;
}

void	print_and_clean(t_game *g)
{
	t_list	*node;
	int		idx;

	reverse_list(&(g->out_or_error));
	node = g->out_or_error;
	idx = 0;
	while (node)
	{
		ft_printf("%s\n", node->content);
		node = node->next;
	}
	ft_printf("\n");
	clean_out(g);
}
