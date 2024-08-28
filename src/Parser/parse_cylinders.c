/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:53:37 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 14:58:23 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_radius(char *line, int *i, t_cylinder *cylinder, t_scene *scene)
{
	cylinder->radius = parse_float(line, i,
			"Invalid character in cylinder definition", scene) / 2;
	if (cylinder->radius <= 0)
		error("Cylinder radius must be positive", scene);
}

void	parse_height(char *line, int *i, t_cylinder *cylinder, t_scene *scene)
{
	cylinder->height = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	if (cylinder->height <= 0)
		error("Cylinder height must be positive", scene);
}

void	parse_color(char *line, int *i, t_cylinder *cylinder, t_scene *scene)
{
	int	r;
	int	g;
	int	b;

	r = parse_color_component(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	g = parse_color_component(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	b = parse_color_component(line, i,
			"Invalid character in cylinder definition", scene);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Cylinder color values out of range [0, 255]", scene);
	cylinder->color.r = r;
	cylinder->color.g = g;
	cylinder->color.b = b;
}

void	parse_cylinder_properties(char *line, int *i,
				t_cylinder *cylinder, t_scene *scene)
{
	skip_whitespace(line, i);
	parse_center(line, i, cylinder, scene);
	skip_whitespace(line, i);
	parse_axis(line, i, cylinder, scene);
	skip_whitespace(line, i);
	parse_radius(line, i, cylinder, scene);
	skip_whitespace(line, i);
	parse_height(line, i, cylinder, scene);
	skip_whitespace(line, i);
	parse_color(line, i, cylinder, scene);
	skip_whitespace(line, i);
}

void	parse_cylinder(char *line, t_cylinder **cylinders, t_scene *scene)
{
	int			i;
	t_cylinder	*new_cylinder;

	i = 0;
	skip_whitespace(line, &i);
	validate_cylinder_identifier(line, &i);
	skip_whitespace(line, &i);
	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_cylinder)
	{
		error("Memory allocation failed", scene);
	}
	add_cylinder_to_list(cylinders, new_cylinder);
	parse_cylinder_properties(line, &i, new_cylinder, scene);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
	{
		i++;
	}
	if (line[i] != '\0')
	{
		error("Invalid character in cylinder definition", scene);
	}
}
