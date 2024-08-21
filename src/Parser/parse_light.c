/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 13:53:21 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_single_color_component(char *line, int *i, int *color_component)
{
	int	start;

	start = *i;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", NULL);
	*color_component = ft_atoi(&line[start]);
	if (line[*i] == ',')
		(*i)++;
}

void	parse_rgb(char *line, int *i, t_rgb *color)
{
	parse_single_color_component(line, i, &color->r);
	parse_single_color_component(line, i, &color->g);
	parse_single_color_component(line, i, &color->b);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
		error("Light color values out of range [0, 255]", NULL);
}

void	parse_light_properties(char *line, int *i, t_light *light, t_rgb *color)
{
	skip_whitespace(line, i);
	parse_position(line, i, light);
	skip_whitespace(line, i);
	parse_intensity_light(line, i, light);
	skip_whitespace(line, i);
	if (line[*i])
		parse_rgb(line, i, color);
	else
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
}

void	parse_light(char *line, t_light *light)
{
	int		i;
	t_rgb	color;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] != 'L')
		error("Missing 'L' identifier for light", NULL);
	i++;
	parse_light_properties(line, &i, light, &color);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in light definition", NULL);
	printf("Parsed Light:\n");
	printf("  Position: x=%f, y=%f, z=%f\n",
		light->position.x, light->position.y, light->position.z);
	printf("  Intensity: %f\n", light->intensity);
	printf("  Color: r=%d, g=%d, b=%d\n", color.r, color.g, color.b);
}
