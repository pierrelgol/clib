/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:24:02 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/05 17:24:03 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

void *gpa_dup(void *const handle, void *const ptr, const uint64_t size)
{
	void                   *result;

	result = gpa_alloc(handle, size);
	return (raw_copy(result, ptr, size));
}

void *gpa_dupz(void *const handle, void *const ptr)
{
	void                   *result;
	uint64_t                len;

	len = raw_search(ptr, 0x00, UINT64_MAX) - ptr;
	result = gpa_alloc(handle, len + 1);
	return (raw_copy(result, ptr, len));
}
