/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:13:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/11 12:17:12 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_color_sphere(char *line, int *i, t_sphere *sphere, t_scene *scene)
{
	sphere->color.r = parse_color_component(line, i,
			"Invalid character in sphere definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	sphere->color.g = parse_color_component(line, i,
			"Invalid character in sphere definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	sphere->color.b = parse_color_component(line, i,
			"Invalid character in sphere definition", scene);
	if (sphere->color.r < 0 || sphere->color.r > 255 || sphere->color.g < 0
		|| sphere->color.g > 255 || sphere->color.b < 0
		|| sphere->color.b > 255)
		error("Sphere color values out of range [0, 255]", NULL, line);
}

void	add_sphere_to_list(t_sphere **spheres, t_sphere *new_sphere)
{
	t_sphere	*current;

	new_sphere->next = NULL;
	if (*spheres == NULL)
	{
		*spheres = new_sphere;
	}
	else
	{
		current = *spheres;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_sphere;
	}
}
