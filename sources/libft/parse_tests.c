/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_tests.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/03 17:49:47 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/14 22:56:08 by qcharpen    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		ftprintf_is_conv(const char c)
{
	return (ft_strchr("%sdDioOuUxXcpfF", c) != NULL);
}

int		ftprintf_is_size(const char c)
{
	return (ft_strchr("hljz", c) != NULL);
}

int		ftprintf_is_flag(const char c)
{
	return (ft_strchr("0#-+ L", c) != NULL);
}

int		ftprintf_is_valid(const char c)
{
	return (ftprintf_is_conv(c) || ftprintf_is_size(c) || ftprintf_is_flag(c)
	|| ft_isdigit(c)
			|| c == '.');
}
