/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/29 11:53:57 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_single_color_component(char *line, int *i,
			int *color_component, t_scene *scene)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", scene, line);
	*color_component = ft_atoi(&line[start]);
	if (line[*i] == ',')
		(*i)++;
}

void	parse_rgb(char *line, int *i, t_rgb *color, t_scene *scene)
{
	parse_single_color_component(line, i, &color->r, scene);
	parse_single_color_component(line, i, &color->g, scene);
	parse_single_color_component(line, i, &color->b, scene);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
		error("Light color values out of range [0, 255]", scene, line);
}

void	parse_light_properties(char *line, int *i, t_rgb *color, t_scene *scene)
{
	t_light	*light;

	light = &scene->light;
	skip_whitespace(line, i);
	parse_position(line, i, light, scene);
	skip_whitespace(line, i);
	parse_intensity_light(line, i, light, scene);
	skip_whitespace(line, i);
	if (line[*i])
		parse_rgb(line, i, color, scene);
	else
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
}

void	parse_light(char *line, t_scene *scene)
{
	int		i;
	t_rgb	color;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] != 'L')
		error("Missing 'L' identifier for light", scene, line);
	i++;
	parse_light_properties(line, &i, &color, scene);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in light definition", scene, line);
}
