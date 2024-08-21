/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:33:12 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 19:27:10 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	parse_integer_part(const char *str, int *i)
{
	float	result;

	result = 0.0;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

float	parse_fractional_part(const char *str, int *i)
{
	float	result;
	float	factor;

	result = 0.0;
	factor = 0.1;
	while (ft_isdigit(str[*i]))
	{
		result += (str[*i] - '0') * factor;
		factor *= 0.1;
		(*i)++;
	}
	return (result);
}

float	ft_atof(const char *str)
{
	float	result;
	float	sign;
	int		i;

	i = 0;
	sign = 1.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
			i++;
	}
	result = parse_integer_part(str, &i);
	if (str[i] == '.')
	{
		i++;
		result += parse_fractional_part(str, &i);
	}
	return (result * sign);
}
