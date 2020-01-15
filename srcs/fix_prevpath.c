#include "ft_select.h"

static void		clean_path(char **path, char **sub_paths,
							size_t len_subs, int p)
{
	char		**clean_subpaths;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	clean_subpaths = tabstr_new(len_subs - 2);
	while (i < len_subs)
	{
		if ((int)i == p - 1)
			i += 2;
		clean_subpaths[j++] = ft_strdup(sub_paths[i++]);
	}
	free(*path);
	*path = tabstr_join(clean_subpaths, "/");
	tabstr_free(&clean_subpaths);
}

static int		there_isprev(char **sub_paths, size_t len_subs)
{
	size_t		i;

	i = 0;
	while (i < len_subs)
	{
		if (!ft_strcmp(sub_paths[i], ".."))
			return (i);
		i++;
	}
	return (-1);
}

void			fix_prevpath(char **path)
{
	size_t		len_subs;
	char		**sub_paths;
	int			found;

	sub_paths = ft_strsplit(*path, '/');
	len_subs = tabstr_len(sub_paths);
	found = there_isprev(sub_paths, len_subs);
	if (found > 0 && len_subs > 2)
		clean_path(path, sub_paths, len_subs, found);
	tabstr_free(&sub_paths);
}
