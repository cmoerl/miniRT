/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:41:08 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/11 12:15:17 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//parse the intensity of the ambient light
//check if the intensity is in the range [0.0, 1.0]
//convert the intensity to a float 
void	parse_intensity(char *line, int *i, float *intensity, t_scene *scene)
{
	int	start;
	int	dot_count;

	start = *i;
	dot_count = 0;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
	{
		if (line[*i] == '.')
			dot_count++;
		(*i)++;
	}
	if (start == *i || dot_count > 1)
		error("Invalid character in ambient lighting definition", scene, line);
	*intensity = ft_atof(&line[start]);
	if (*intensity < 0.0 || *intensity > 1.0)
		error("Ambient lighting intensity out of range[0.0, 1.0]", scene, line);
}

void	parse_color_value(char *line, int *i,
		t_color_info *color_info, t_scene *scene)
{
	int	start;
	int	error_overflow;

	start = *i;
	validate_line_format(line, scene);
	if (line[*i] == '-' || line[*i] == '+')
		(*i)++;
	while (line[*i] && (ft_isdigit(line[*i])))
		(*i)++;
	if (start == *i)
		error("Invalid character in ambient lighting definition", scene, line);
	*(color_info->color_value) = ft_atoi_overflow(&line[start],
			&error_overflow);
	if (error_overflow)
	{
		printf("Error: Ambient lighting %s value out of range [0, 255]\n",
			color_info->color_name);
		error(NULL, scene, line);
	}
	if (*(color_info->color_value) < 0 || *(color_info->color_value) > 255)
	{
		printf("Error: Ambient lighting %s value out of range [0, 255]\n",
			color_info->color_name);
		error(NULL, scene, line);
	}
}

void	parse_color_values(char *line, int *i, t_color *color, t_scene *scene)
{
	float				r;
	float				g;
	float				b;
	t_color_info		color_info;

	color_info.color_value = &r;
	color_info.color_name = "red";
	parse_color_value(line, i, &color_info, scene);
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
		(*i)++;
	color_info.color_value = &g;
	color_info.color_name = "green";
	parse_color_value(line, i, &color_info, scene);
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == ','))
		(*i)++;
	color_info.color_value = &b;
	color_info.color_name = "blue";
	parse_color_value(line, i, &color_info, scene);
	while (line[*i] && (line[*i] == ' '
			|| line[*i] == '\t' || line[*i] == '\n'))
		(*i)++;
	color->r = r;
	color->g = g;
	color->b = b;
}

void	parse_ambient(char *line, t_amblight *ambient, t_scene *scene)
{
	int		i;
	float	intensity;

	i = 0;
	skip_whitespace(line, &i);
	i++;
	if (line[i] != ' ')
		error("Missing space after 'A' identifier for ambient lighting",
			scene, line);
	validate_line_format(line, scene);
	skip_whitespace(line, &i);
	parse_intensity(line, &i, &intensity, scene);
	skip_whitespace(line, &i);
	parse_color_values(line, &i, &ambient->color, scene);
	if (line[i] != '\0')
		error("Invalid character in ambient lighting definition", scene, line);
	ambient->intensity = intensity;
}
