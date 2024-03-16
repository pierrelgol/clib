/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:52:27 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/20 11:52:28 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

int32_t	file_mode(char *mode)
{
	if (mode[0] == 'r')
		return (O_RDONLY);
	if (mode[0] == 'w')
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (mode[0] == 'a')
		return (O_WRONLY | O_CREAT | O_APPEND);
	if (mode[0] == 'r' && mode[1] == '+')
		return (O_RDWR);
	if (mode[0] == 'w' && mode[1] == '+')
		return (O_RDWR | O_CREAT | O_TRUNC);
	if (mode[0] == 'a' && mode[1] == '+')
		return (O_RDWR | O_CREAT | O_APPEND);
	return (0);
}
