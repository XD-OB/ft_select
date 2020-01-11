#include "libft.h"

void	dct_lstremove(t_dlist **alst, t_dlist *place, void (*del)(void*, size_t))
{
	t_dlist		*curr;

	if (!alst || !*alst || !del)
		return ;
	curr = *alst;
	while (curr != place)
		curr = curr->next;
	del(curr->content, curr->content_size);
	if (curr->prev == curr->next)
	{
		free(*alst);
		*alst->prev = NULL;
		*alst->next = NULL;
		*alst = NULL;
	}
	else if (curr == *alst)
	{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		*alst = (*alst)->next;
		free(curr);
		curr = NULL;
	}
	else
	{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free(curr);
		curr = NULL;
		
	}
}
