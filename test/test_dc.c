#include "libft/includes/libft.h"

typedef struct			s_dlist
{
	void				*content;
	size_t				content_size;
	struct s_dlist		*prev;
	struct s_dlist		*next;
}						t_dlist;

t_dlist					*dct_lstnew(const void *content, size_t content_size)				//////////////////////////
{
	t_dlist	*node;
	void	*cont;

	node = (t_dlist*)malloc(sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->prev = node;
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

t_dlist					*dct_lstnew_sm(void *content, size_t content_size)					//////////////////////
{
	t_dlist	*node;

	node = (t_dlist*)malloc(sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->prev = node;
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

void	dct_lstremove(t_dlist **alst, t_dlist *place, void (*del)(void*, size_t))
{
	t_dlist		*curr;
	t_dlist		*tmp;

	if (!alst || !*alst || !del)
		return ;
	curr = *alst;
	while (curr != place)
		curr = curr->next;
	del(curr->content, curr->content_size);
	if (curr->prev == curr->next)
	{
		free(curr);
		curr->prev = NULL;
		curr->next = NULL;
		curr = NULL;
	}
	else
	{
		tmp = curr;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		curr = curr->prev;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
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

void	dct_lstdel(t_dlist **alst, void (*del)(void*, size_t))
{
	t_dlist		*curr;

	curr = *alst;
	while (curr && curr->next != *alst)
		curr = curr->next;
	curr->next = NULL;
	(*alst)->prev = NULL;
	dt_lstdel(alst, del);
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

void    dct_lstadd_last(t_dlist **alst, t_dlist* new)				//////////////////////////////////////
{
	t_dlist  *current;

	if (!new)
		return ;
	if (*alst)
	{
		current = *alst;
		while (current->next != *alst)
			current = current->next;
		current->next = new;
		new->next = *alst;
		new->prev = current;
		(*alst)->prev = new;
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
	int		i = 0;

	while (++i < 8)
	{
		ft_printf("%s -> ", (char*)alst->content);
		alst = alst->next;
	}
	ft_printf("NULL\n");
}

void		dt_print_dec(t_dlist *alst)							/////////////////////////
{
	int		i = 0;

	while (++i < 8)
		alst = alst->next;
	i = 0;
	while (++i < 8)
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
		node[i] = dct_lstnew_sm(av[i], sizeof(av[i]));
		dct_lstadd_last(&list, node[i]);
	}
	ft_printf("----------- === normal === ---------\n");
	dt_print_inc(list);
	dt_print_dec(list);
	ft_printf("----------- === Insert=== ---------\n");
	node[49] = list->next->next->next;
	tmp = dct_lstnew_sm("||||", sizeof(char*));
	dt_lstinsert(&list, node[49], tmp);
	dt_print_inc(list);
	dt_print_dec(list);
	ft_printf("----------- === delete=== ---------\n");
	node[49] = list->next->next->next;
	dct_lstremove(&list, node[49], delet);
	dt_print_inc(list);
	dt_print_dec(list);
	//ft_printf("\n======[ %d ]======\n", dt_lstlen(list));
	dct_lstdel(&list, delet);
	return (0);
}
