#include "../libft/includes/libft.h"

void		print_ct(t_list *alst)							/////////////////////////
{
	int		i = 0;

	while (++i < 8)
	{
		ft_printf("%s -> ", (char*)alst->content);
		alst = alst->next;
	}
	ft_printf("NULL\n");
}

void    ct_lstadd_last(t_list **alst, t_list* new)				////////////////////
{
	t_list  *current;

	if (!new)
		return ;
	if (*alst)
	{
		current = *alst;
		while (current->next != *alst)
			current = current->next;
		current->next = new;
		new->next = *alst;
	}
	else
		*alst = new;
}

t_list			*ct_lstnew_sm(void *content, size_t content_size)			////////////////////
{
	t_list		*node;

	node = (t_list*)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->next = node;
	if (content == NULL)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		node->content = content;
		node->content_size = content_size;
	}
	return (node);
}

t_list			*ct_lstnew(const void *content, size_t content_size)			////////////////////
{
	t_list		*node;
	void		*cont;

	node = (t_list*)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->next = node;
	if (content == NULL)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		cont = (void*)malloc(content_size);
		node->content = ft_memcpy(cont, content, content_size);
		node->content_size = content_size;
	}
	return (node);
}

void			ct_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list		*curr;

	curr = *alst;
	while (curr && curr->next != *alst)
		curr = curr->next;
	curr->next = NULL;
	ft_lstdel(alst, del);
}

void	ct_lstremove(t_list **alst, t_list *place, void (*del)(void*, size_t))
{
	t_list		*next;
	t_list		*prev;

	if (!alst || !*alst || !place || !del)
		return ;
	prev = *alst;
	if (place != *alst)
	{
		while (prev && prev->next != place)
			prev = prev->next;
		if (!prev)
			return ;
		next = place->next;
		del(place->content, place->content_size);
		free(place);
		prev->next = next;
		return ;
	}
	next = *alst;
	while (next->next != *alst)
		next = next->next;
	next->next = (*alst)->next;
	*alst = (*alst)->next;
	free(prev);
}

void	delet(void* content, size_t size)
{
}

int						main(int ac, char **av)
{
	t_list				*node[50];
	t_list				*list;
	t_list				*tmp;
	int					i;

	list = NULL;
	i = 0;
	while (++i < ac)
	{
		node[i] = ct_lstnew_sm(av[i], sizeof(av[i]));
		ct_lstadd_last(&list, node[i]);
	}
	ft_printf("----------- === normal === ---------\n");
	print_ct(list);
	ft_printf("----------- === Insert=== ---------\n");
	node[49] = list;
	tmp = ct_lstnew_sm("||||", sizeof(char*));
	ft_lstinsert(&list, node[49], tmp);
	print_ct(list);
	ft_printf("----------- === delete=== ---------\n");
	node[49] = list->next;
	ct_lstremove(&list, node[49], delet);
	print_ct(list);
	ct_lstdel(&list, delet);
	return (0);
}
