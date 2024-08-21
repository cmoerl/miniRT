/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:13:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 19:19:33 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_color_sphere(char *line, int *i, t_sphere *sphere)
{
	int	r;
	int	g;
	int	b;

	r = parse_color_component(line, i,
			"Invalid character in sphere definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	g = parse_color_component(line, i,
			"Invalid character in sphere definition");
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	b = parse_color_component(line, i,
			"Invalid character in sphere definition");
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Sphere color values out of range [0, 255]", NULL);
	sphere->color.r = r / 255.0;
	sphere->color.g = g / 255.0;
	sphere->color.b = b / 255.0;
}
