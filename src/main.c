/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/08/01 12:11:15 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int main(int argc, char **argv)
{
     t_scene scene = {0};

    if (argc != 2)
    {
        printf("Usage: %s <scene.rt>\n", argv[0]);
        return 1;
    }

    // Test check_file function
    check_file(argv[1]);

    // If the file is valid, proceed with parsing (placeholder)
    scene = parse_scene(argv[1], scene);

    printf("File is valid and ready for parsing.\n");

    // Placeholder for further processing
    // render_scene(scene);
    // event_loop(scene);

    return 0;
}

 