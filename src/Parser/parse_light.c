/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/11 12:06:24 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_light_properties(char *line, int *i, t_scene *scene)
{
	t_light	*light;

	light = &scene->light;
	skip_whitespace(line, i);
	parse_position(line, i, light, scene);
	skip_whitespace(line, i);
	parse_intensity_light(line, i, light, scene);
	skip_whitespace(line, i);
	if (line[*i] != '\0' && line[*i] != '\n')
		error("Invalid character in light definition", scene, line);
}

void	parse_light(char *line, t_scene *scene)
{
	int		i;

	i = 0;
	validate_line_format(line, scene);
	if (line[i + 1] != ' ')
		error("Missing space afer identifier for light", scene, line);
	skip_whitespace(line, &i);
	i++;
	parse_light_properties(line, &i, scene);
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in light definition", scene, line);
}
