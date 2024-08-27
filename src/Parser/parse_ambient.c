/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:41:08 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/27 09:30:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_intensity(char *line, int *i, float *intensity, t_scene *scene)
{
	int	start;

	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error("Invalid character in ambient lighting definition", scene);
	*intensity = ft_atof(&line[start]);
	if (*intensity < 0.0 || *intensity > 1.0)
		error("Ambient lighting intensity out of range [0.0, 1.0]", scene);
}

void	parse_color_value(char *line, t_color_params *params, int *color_value)
{
	int	start;

	start = *(params->i);
	while (line[*(params->i)] && ft_isdigit(line[*(params->i)]))
		(*(params->i))++;
	if (start == *(params->i))
		error("Invalid character in ambient lighting definition",
			params->scene);
	*color_value = ft_atoi(&line[start]);
	if (*color_value < 0 || *color_value > 255)
	{
		printf("Error: Ambient lighting %s value out of range [0, 255]\n",
			params->color_name);
		error(NULL, params->scene);
	}
}

void	parse_color_values(char *line, int *i, t_color *color, t_scene *scene)
{
	t_color_params	params;

	params.i = i;
	params.scene = scene;
	params.color_name = "red";
	parse_color_value(line, &params, &params.r);
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
		(*i)++;
	params.color_name = "green";
	parse_color_value(line, &params, &params.g);
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
		(*i)++;
	params.color_name = "blue";
	parse_color_value(line, &params, &params.b);
	while (line[*i] && (line[*i] == ' '
			|| line[*i] == '\t' || line[*i] == '\n'))
		(*i)++;
	color->r = params.r;
	color->g = params.g;
	color->b = params.b;
}

void	print_ambient_details(t_amblight *ambient, float intensity)
{
	int	r;
	int	g;
	int	b;

	r = (int)(ambient->color.r * 255);
	g = (int)(ambient->color.g * 255);
	b = (int)(ambient->color.b * 255);
	printf("Parsed Ambient Lighting:\n");
	printf("  Intensity: %f\n", intensity);
	printf("  Color: R=%d, G=%d, B=%d\n", r, g, b);
	printf("  Normalized Color: R=%f, G=%f, B=%f\n", ambient->color.r,
		ambient->color.g, ambient->color.b);
}

void	parse_ambient(char *line, t_amblight *ambient, t_scene *scene)
{
	int		i;
	float	intensity;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] != 'A')
		error("Missing 'A' identifier for ambient lighting", scene);
	i++;
	skip_whitespace(line, &i);
	parse_intensity(line, &i, &intensity, scene);
	skip_whitespace(line, &i);
	parse_color_values(line, &i, &ambient->color, scene);
	if (line[i] != '\0')
		error("Invalid character in ambient lighting definition", scene);
	ambient->intensity = intensity;
	print_ambient_details(ambient, intensity);
}
