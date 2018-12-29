/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstprint.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 21:35:10 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/14 22:52:51 by qcharpen    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void		ftprintf_lstjoin(t_ftprintf *lst2, t_ftprintf **lst)
{
	int			i;
	int			j;
	char		*s;

	s = ft_memalloc(sizeof((*lst)->str) * ((*lst)->size + lst2->size + 1));
	i = 0;
	j = 0;
	while (i < (*lst)->size)
	{
		s[i] = (*lst)->str[i];
		i++;
	}
	while (j < lst2->size)
		s[i++] = lst2->str[j++];
	s[i] = '\0';
	(*lst)->size = (*lst)->size + lst2->size;
	free((*lst)->str);
	(*lst)->str = s;
}

static t_ftprintf	*ftprintf_lstjoin_free(t_ftprintf *lst)
{
	t_ftprintf		*rst;
	t_ftprintf		*tmp;

	while (lst->next)
	{
		tmp = lst->next;
		ftprintf_lstjoin(tmp, &lst);
		lst->next = tmp->next ? tmp->next : NULL;
		free(tmp->str);
		free(tmp);
	}
	return (lst);
}

int				ftprintf_lstfprint(void **str, t_ftprintf *lst)
{
	t_ftprintf		*tmp;
	int			fd;

	if (access((char*)*str, W_OK))
	{
		if ((fd = open((char*)*str,
			O_CREAT | O_APPEND | O_WRONLY, 0770)))
		{
			tmp = ftprintf_lstjoin_free(lst);
			write(fd, tmp->str, tmp->size);
		}
		else
			lst->size = 0;
	}
	else
		lst->size = 0;
	free(tmp->str);
	return (tmp->size);
}

int				ftprintf_lstsprint(void **str, t_ftprintf *lst)
{
	t_ftprintf		*tmp;

	tmp = lst;
	tmp = ftprintf_lstjoin_free(lst);
	*str = tmp->str;
	return (tmp->size);
}

int				ftprintf_lstprint(void **fd, t_ftprintf *lst)
{
	t_ftprintf		*tmp;

	tmp = ftprintf_lstjoin_free(lst);
	write(*((int*)fd[0]), tmp->str, tmp->size);
	free(tmp->str);
	return (tmp->size);
}
