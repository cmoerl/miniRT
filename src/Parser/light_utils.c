/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:11:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/08/21 16:55:26 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_single_position(char *line, int *i, float *position_component)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+' ))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", NULL);
	*position_component = ft_atof(&line[start]);
	if (line[*i] == ',')
		(*i)++;
}

void	parse_position(char *line, int *i, t_light *light)
{
	parse_single_position(line, i, &light->position.x);
	parse_single_position(line, i, &light->position.y);
	parse_single_position(line, i, &light->position.z);
}

void	parse_intensity_light(char *line, int *i, t_light *light)
{
	int	start;

	skip_whitespace(line, i);
	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error("Invalid character in light definition", NULL);
	light->intensity = ft_atof(&line[start]);
	if (light->intensity < 0.0 || light->intensity > 1.0)
		error("Light intensity out of range [0.0, 1.0]", NULL);
}
