#include "libft/includes/libft.h"

typedef struct			s_dlist
{
	void				*content;
	size_t				content_size;
	struct s_dlist		*prev;
	struct s_dlist		*next;
}						t_dlist;

t_dlist					*dt_lstnew(const void *content, size_t content_size)				//////////////////////////
{
	t_dlist	*node;
	void	*cont;

	node = (t_dlist*)malloc(sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
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

t_dlist					*dt_lstnew_sm(void *content, size_t content_size)					//////////////////////
{
	t_dlist	*node;

	node = (t_dlist*)malloc(sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
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

void	dt_lstdelone(t_dlist **alst, void (*del)(void*, size_t))
{
	if (alst)
	{
		if (*alst && del)
		{
			del((*alst)->content, (*alst)->content_size);
			(*alst)->prev = NULL;
			(*alst)->next = NULL;
			free(*alst);
			*alst = NULL;
		}
	}
}

static void		ft_lstremove_p2(t_list **alst, t_list *prev, t_list *next)
{
	t_list		*tmp;

	if (!prev && !next)
	{
		free(*alst);
		*alst = NULL;
	}
	else if (!prev)
	{
		tmp = *alst;
		*alst = (*alst)->next;
		free(tmp);
	}
	else if (!next)
	{
		free(prev->next);
		prev->next = NULL;
	}
}

void	ft_lstremove(t_list **alst, t_list *place, void (*del)(void*, size_t))
{
	t_list		*next;
	t_list		*prev;

	if (!alst || !*alst || !del)
		return ;
	prev = NULL;
	if (place != *alst)
	{
		prev = *alst;
		while (prev && prev->next != place)
			prev = prev->next;
		if (!prev)
			return ;
	}
	next = place->next;
	del(place->content, place->content_size);
	if (prev && next)
	{
		free(place);
		prev->next = next;
	}
	else
		ft_lstremove_p2(alst, prev, next);
}

static void		lstremove_p2(t_dlist **alst)
{
	t_dlist		*tmp;

	tmp = *alst;
	if (!(*alst)->next)
	{
		*alst = (*alst)->prev;
		(*alst)->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	else
	{
		(*alst)->prev->next = (*alst)->next;
		(*alst)->next->prev = (*alst)->prev;
		*alst = (*alst)->prev;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	dt_lstremove(t_dlist **alst, t_dlist *place, void (*del)(void*, size_t))
{
	t_dlist		*curr;

	if (!alst || !*alst || !del)
		return ;
	curr = *alst;
	while (curr && curr != place)
		curr = curr->next;
	if (!curr)
		return ;
	del(curr->content, curr->content_size);
	if (!curr->prev && !curr->next)
	{
		free(curr);
		curr = NULL;
	}
	else if (!curr->prev)
	{
		curr = curr->next;
		curr->prev->next = NULL;
		free(curr->prev);
		curr->prev = NULL;
		*alst = curr;
	}
	else
		lstremove_p2(&curr);
}

void	dt_lstdel(t_dlist **alst, void (*del)(void*, size_t))
{
	t_dlist	*current_node;

	if (alst)
	{
		while (*alst != NULL)
		{
			current_node = *alst;
			if (del)
				del((*alst)->content, (*alst)->content_size);
			(*alst)->prev = NULL;
			*alst = (*alst)->next;
			free(current_node);
			current_node = NULL;
		}
	}
}

void	dt_lstadd(t_dlist **alst, t_dlist *new)						//////////////////////////////////////
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	new->prev = (*alst)->prev;
	(*alst)->prev = new;
	*alst = new;
}

void    dt_lstadd_last(t_dlist **alst, t_dlist* new)				//////////////////////////////////////
{
	t_dlist  *current;

	if (!new)
		return ;
	if (*alst)
	{
		current = *alst;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
	else
		*alst = new;
}

void		dt_lstinsert(t_dlist **alst, t_dlist *place, t_dlist *node)				///////////////////////////////////
{
	t_dlist		*curr;

	if (!*alst)
		*alst = node;
	else
	{
		curr  = *alst;
		while (curr && curr != place)
			curr = curr->next;
		if (!curr)
			return ;
		node->prev = curr;
		node->next = curr->next;
		if (curr->next)
			curr->next->prev = node;
		curr->next = node;
	}
}

void		ft_lstinsert(t_list **alst, t_list *place, t_list *node)				///////////////////////////////////
{
	t_list		*curr;

	if (!*alst)
		*alst = node;
	else
	{
		curr  = *alst;
		while (curr && curr != place)
			curr = curr->next;
		if (!curr)
			return ;
		node->next = curr->next;
		curr->next = node;
	}
}

void		dt_print_inc(t_dlist *alst)							/////////////////////////
{
	while (alst)
	{
		ft_printf("%s -> ", (char*)alst->content);
		alst = alst->next;
	}
	ft_printf("NULL\n");
}

void		dt_print_dec(t_dlist *alst)							/////////////////////////
{
	while (alst->next)
		alst = alst->next;
	while (alst)
	{
		ft_printf("%s -> ", (char*)alst->content);
		alst = alst->prev;
	}
	ft_printf("NULL\n");
}

void	dt_lstiter(t_dlist *lst, void (*f)(t_dlist *elem))
{
	if (f)
	{
		while (lst != NULL)
		{
			f(lst);
			lst = lst->next;
		}
	}
}

t_dlist		*dt_lstmap(t_dlist *lst, t_dlist *(*f)(t_dlist *elem))
{
	t_dlist	*new_lst;
	t_dlist	*ind[2];

	if (!lst || !f)
		return (NULL);
	new_lst = (t_dlist*)malloc(sizeof(t_dlist));
	ind[0] = new_lst;
	if (!new_lst)
		return (NULL);
	while (lst->next)
	{
		new_lst->next = (t_dlist*)malloc(sizeof(t_dlist));
		ind[1] = (*f)(lst);
		new_lst->content = malloc(ind[1]->content_size);
		ft_memcpy(new_lst->content, ind[1]->content, ind[1]->content_size);
		new_lst->content_size = ind[1]->content_size;
		new_lst = new_lst->next;
		lst = lst->next;
	}
	new_lst->next = NULL;
	ind[1] = (*f)(lst);
	new_lst->content = malloc(ind[1]->content_size);
	ft_memcpy(new_lst->content, ind[1]->content, ind[1]->content_size);
	new_lst->content_size = ind[1]->content_size;
	return (ind[0]);
}

int		dt_lstlen(t_dlist *alst)
{
	int		len;

	len = 0;
	while (alst)
	{
		alst = alst->next;
		len++;
	}
	return (len);
}

void	delet(void* content, size_t size)
{
}

int						main(int ac, char **av)
{
	t_dlist				*node[50];
	t_dlist				*list;
	t_dlist				*tmp;
	int					i;

	list = NULL;
	i = 0;
	while (++i < ac)
	{
		node[i] = dt_lstnew_sm(av[i], sizeof(av[i]));
		dt_lstadd_last(&list, node[i]);
	}
	ft_printf("----------- === normal === ---------\n");
	dt_print_inc(list);
	dt_print_dec(list);
	ft_printf("----------- === Insert=== ---------\n");
	node[49] = list->next->next->next;
	tmp = dt_lstnew_sm("||||", sizeof(char*));
	dt_lstinsert(&list, node[49], tmp);
	dt_print_inc(list);
	dt_print_dec(list);
	/*ft_printf("----------- === delete=== ---------\n");
	node[49] = list->next->next->next;
	dt_lstremove(&list, node[49], delet);
	dt_print_inc(list);
	dt_print_dec(list);*/
	ft_printf("\n======[ %d ]======\n", dt_lstlen(list));
	dt_lstdel(&list, delet);
	return (0);
}
