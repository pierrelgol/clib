/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:45:29 by pollivie          #+#    #+#             */
/*   Updated: 2024/02/03 11:45:30 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

uint64_t	string_length(const uint8_t *str)
{
	return ((uint64_t)((const uint8_t *)memory_search(str, 0x00, UINT64_MAX) - str));
}
