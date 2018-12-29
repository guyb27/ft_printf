/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_char.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/16 22:02:16 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 21:56:00 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

t_ftprintf	*ftprintf_handle_char(t_ftprintf_flags *spec, va_list args)
{
	char	arg;
	char	*str;
	int		i;
	int		len;

	arg = va_arg(args, int);
	if (spec->size == L)
		return (ftprintf_lstnew(NULL, 0));
	i = 0;
	len = (spec->width == -1 ? 1 : spec->width);
	str = (char*)ft_memalloc(sizeof(*str) * (len + 1));
	if (spec->flags[MINUS])
		str[i++] = arg;
	while (i < len - !spec->flags[MINUS])
		str[i++] = (spec->flags[ZERO] ? '0' : ' ');
	if (i != len)
		str[i++] = arg;
	str[i] = '\0';
	return (ftprintf_lstnew(str, len));
}
