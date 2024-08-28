/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:13:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 15:12:05 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_color_sphere(char *line, int *i, t_sphere *sphere, t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	r = parse_color_component(line, i,
			"Invalid character in sphere definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	g = parse_color_component(line, i,
			"Invalid character in sphere definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	b = parse_color_component(line, i,
			"Invalid character in sphere definition", scene);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Sphere color values out of range [0, 255]", NULL);
	sphere->color.r = r;
	sphere->color.g = g;
	sphere->color.b = b;
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
