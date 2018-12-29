/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_str.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 04:06:07 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 06:13:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	mallsize(t_ftprintf_flags *spec, char *arg)
{
	int		tmp;

	if (spec->prec == -1 || spec->prec > ft_strlen(arg))
		spec->prec = ft_strlen(arg);
	tmp = MIN(spec->prec, ft_strlen(arg));
	return (MAX(tmp, spec->width));
}

t_ftprintf		*ftprintf_handle_str(t_ftprintf_flags *spec, va_list args)
{
	char	*arg;
	char	*rst;
	int		i[2];
	int		len;
	t_ftprintf	*ret;

	if ((arg = va_arg(args, char*)) == NULL)
		arg = "(null)";
	if (spec->size == L)
		return (ftprintf_lstnew(NULL, 0));
	len = mallsize(spec, arg);
	if ((rst = (char*)ft_memalloc(sizeof(*rst) * (len + 1))) == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	while (i[0] < (len - spec->prec) && !spec->flags[MINUS])
		rst[i[0]++] = (spec->flags[ZERO] ? '0' : ' ');
	while (i[0] < (spec->flags[MINUS] ? spec->prec : len))
		rst[i[0]++] = arg[i[1]++];
	while (i[0] < len)
		rst[i[0]++] = ' ';
	rst[i[0]] = '\0';
	return (ftprintf_lstnew(rst, len));
}
