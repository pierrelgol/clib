/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:38:13 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/07 15:38:13 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool is_control(int32_t ch)
{
	return (ch == 127 || (ch >= 0 && ch <= 31));
}

bool is_eof(int32_t ch)
{
	return (ch == -1);
}

bool is_graph(int32_t ch)
{
	return (!is_control(ch) && !is_spaces(ch));
}

bool is_hex(int32_t ch)
{
	return ((ch >= '0' && ch <= '9') || ((ch | 32) >= 'a' && (ch | 32) <= 'f'));
}

bool is_punct(int32_t ch)
{
	return (ch != 32 && !is_alnum(ch) && !is_control(ch));
}

