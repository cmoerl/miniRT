/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:33:12 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/04 23:33:17 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float ft_atof(const char *str)
{
    float result = 0.0;
    float sign = 1.0;
    float factor = 0.1;
    int i = 0;
    // Handle sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1.0;
        i++;
    }
    // Parse integer part
    while (ft_isdigit(str[i]))
    {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    // Parse fractional part
    if (str[i] == '.')
    {
        i++;
        while (ft_isdigit(str[i]))
        {
            result += (str[i] - '0') * factor;
            factor *= 0.1;
            i++;
        }
    }
    return result * sign;
}