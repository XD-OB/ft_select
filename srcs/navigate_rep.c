/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_rep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 06:30:53 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/18 06:30:55 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char			*full_path(char *parent, char *name)
{
	char			*res;
	char			*tmp;

	if (parent[ft_strlen(parent) - 2] == '/')
		res = ft_strjoin(parent, name);
	else
	{
		tmp = ft_strjoin(parent, "/");
		res = ft_strjoin(tmp, name);
		free(tmp);
	}
	return (res);
}

static void			add_element(struct dirent *dirent,
								t_select *select, char *parent)
{
	t_dlist			*node;
	char			*path;
	t_arg			*arg;

	if (!ft_strcmp(dirent->d_name, "."))
		return ;
	path = full_path(parent, dirent->d_name);
	if (ft_strcmp(dirent->d_name, ".."))
		fix_prevpath(&path);
	arg = create_arg(path);
	free(path);
	node = dct_lstnew_sm(arg, sizeof(arg));
	dct_lstadd_last(&(select->args), node);
	select->nbr_args++;
}

static void			empty_select(t_select *select)
{
	if (select->lens_cols)
		free(select->lens_cols);
	if (select->args)
		dct_lstdel(&(select->args), delete_arg);
	select->args = NULL;
	select->lens_cols = NULL;
	select->nbr_cols = 0;
	select->len_search = 0;
	select->nbr_args = 0;
}

void				navigate_rep(t_select *select)
{
	struct dirent	*dirent;
	char			*parent;
	t_arg			*arg;
	DIR				*dir;

	arg = (t_arg*)select->current->content;
	dir = opendir(arg->str);
	if (!dir)
		return ;
	parent = ft_strdup(arg->str);
	empty_select(select);
	dirent = readdir(dir);
	while (dirent)
	{
		add_element(dirent, select, parent);
		dirent = readdir(dir);
	}
	free(parent);
	closedir(dir);
	select->current = select->args;
	draw_state(select, 1);
}
