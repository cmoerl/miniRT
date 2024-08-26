/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:47:36 by csturm            #+#    #+#             */
/*   Updated: 2024/08/26 11:29:16 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// calculating the dot product of two vectors
float	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// calculating the cross product of two vectors
t_vector	cross_product(t_vector a, t_vector b)
{
	return ((t_vector){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x});
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}
