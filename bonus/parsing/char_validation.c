/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 22:10:55 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 17:36:45 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	parse_char(char c)
{
	if ((c >= 9 && c <= 13) || c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (0);
	else if (c == '\n')
		return (1);
	else
	{
		fprintf(stderr, "Error: Invalid character '%c' in map\n", c);
		return (1);
	}
	return (0);
}
