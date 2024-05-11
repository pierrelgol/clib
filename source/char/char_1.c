/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:10:22 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/07 15:10:22 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

bool	is_alpha(int32_t ch)
{
	return ((ch | 32) >= 'a' && (ch | 32) <= 'z');
}

bool	is_digit(int32_t ch)
{
	return (ch >= '0' && ch <= '9');
}

bool	is_alnum(int32_t ch)
{
	return (is_alpha(ch) || is_digit(ch));
}

bool	is_spaces(int32_t ch)
{
	return (ch == ' ' || ch == 9 || (ch >= 10 && ch <= 13));
}

bool	is_blank(int32_t ch)
{
	return (ch == ' ' || ch == '\t');
}
