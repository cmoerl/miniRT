/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/20 13:26:12 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Helper function to parse intensity
float	parse_intensity_light(char *line, int *i)
{
	float	intensity;

	intensity = parse_float(line, i);
	if (intensity < 0.0 || intensity > 1.0)
		error("Light intensity out of range [0.0, 1.0]", NULL);
	return (intensity);
}

// Helper function to parse RGB values
void	parse_rgb(char *line, int *i, t_rgb *rgb)
{
	rgb->r = ft_atoi(&line[*i]);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	rgb->g = ft_atoi(&line[*i]);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
	rgb->b = ft_atoi(&line[*i]);
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (rgb->r < 0 || rgb->r > 255 || rgb->g < 0
		|| rgb->g > 255 || rgb->b < 0 || rgb->b > 255)
		error("Light color values out of range [0, 255]", NULL);
}

// Helper function to validate the end of line
void	validate_end_of_line_light(char *line, int i)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in light definition", NULL);
}

// Function to parse the light
void	parse_light(char *line, t_light *light)
{
	int	i;
	int	r;
	int	g;
	int	b;
	t_rgb rgb;

	i = 0;
	skip_whitespace(line, &i);
	validate_identifier_light(line[i], 'L');
	i++;
	skip_whitespace(line, &i);
	light->position = parse_vector_light(line, &i);
	skip_whitespace(line, &i);
	light->intensity = parse_intensity_light(line, &i);
	skip_whitespace(line, &i);
	if (line[i])
		parse_rgb(line, &i, &rgb);
	else
	{
		r = 255;
		g = 255;
		b = 255;
	}
	validate_end_of_line_light(line, i);
}
