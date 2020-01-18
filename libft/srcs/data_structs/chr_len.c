/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 09:22:22 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 09:22:31 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			chr_len(t_chr *chr)
{
	int		len;

	len = 0;
	while (chr)
	{
		len++;
		chr = chr->next;
	}
	return (len);
}
