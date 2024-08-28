/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:11:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/08/28 10:29:34 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_single_position(char *line, int *i,
			float *position_component, t_scene *scene)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+' ))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", scene);
	*position_component = ft_atof(&line[start]);
	if (line[*i] == ',')
		(*i)++;
}

void	parse_position(char *line, int *i, t_light *light, t_scene *scene)
{
	parse_single_position(line, i, &light->position.x, scene);
	parse_single_position(line, i, &light->position.y, scene);
	parse_single_position(line, i, &light->position.z, scene);
}

void	parse_intensity_light(char *line, int *i,
			t_light *light, t_scene *scene)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", scene);
	light->intensity = ft_atof(&line[start]);
	if (light->intensity < 0.0 || light->intensity > 1.0)
		error("Light intensity out of range [0.0, 1.0]", scene);
}

