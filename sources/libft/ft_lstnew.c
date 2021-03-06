/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 16:57:01 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 22:34:24 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_ftprintf	*ftprintf_lstnew(char *str, size_t len)
{
	t_ftprintf	*new;

	new = (t_ftprintf*)malloc(sizeof(*new));
	new->str = str;
	new->size = len;
	new->next = NULL;
	return (new);
}
