/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:38:08 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/07 15:38:09 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool is_printable(int32_t ch)
{
	return (is_control(ch) == false);
}

bool is_ascii(int32_t ch)
{
	return (ch >= 0 && ch <= 127);
}

bool is_newline(int32_t ch)
{
	return (ch == 10);
}

bool is_upper(int32_t ch)
{
	return (ch >= 'A' && ch <= 'Z');
}

bool is_lower(int32_t ch)
{
	return (ch >= 'a' && ch <= 'z');
}

