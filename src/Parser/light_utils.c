/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:11:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/10 15:45:46 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_single_position(char *line, int *i,
            float *position_component, t_scene *scene)
{
    int	start;
    int	dot_count = 0;

    skip_whitespace(line, i);
    start = *i;
    while (line[*i] && (ft_isdigit(line[*i])
            || line[*i] == '.' || line[*i] == '-' || line[*i] == '+' ))
    {
        if (line[*i] == '.')
            dot_count++;
        (*i)++;
    }
    if (start == *i || dot_count > 1)
        error("Invalid character in light definition", scene, line);
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
    int	dot_count = 0;

    skip_whitespace(line, i);
    start = *i;
    while (line[*i] && (ft_isdigit(line[*i])
            || line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
    {
        if (line[*i] == '.')
            dot_count++;
        (*i)++;
    }
    if (start == *i || dot_count > 1)
        error("Invalid character in light definition", scene, line);
    light->intensity = ft_atof(&line[start]);
    if (light->intensity < 0.0 || light->intensity > 1.0)
        error("Light intensity out of range [0.0, 1.0]", scene, line);
}
