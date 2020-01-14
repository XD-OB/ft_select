#include "libft.h"

void		ft_strccombin(char **str, char c)
{
	char	*tmp;

	if (*str)
	{
		tmp = *str;
		*str = ft_strcjoin(*str, c);
		free(tmp);
	}
	else
		*str = ft_strcnew(1, c);
}
