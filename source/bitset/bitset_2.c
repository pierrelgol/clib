/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pollivie <pollivie.student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:20:14 by pollivie          #+#    #+#             */
/*   Updated: 2024/05/06 13:20:14 by pollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/clib.h"

t_bitset bitset_and(t_bitset *bitset1, t_bitset *bitset2)
{
	t_bitset result;

	for (int i = 0; i < 4; ++i)
	{
		result.set[i] = bitset1->set[i] & bitset2->set[i];
	}
	return result;
}

t_bitset bitset_or(t_bitset *bitset1, t_bitset *bitset2)
{
	t_bitset result;
	uint64_t index;

	index = 0;
	while (index < 4)
	{
		result.set[index] = bitset1->set[index] | bitset2->set[index];
		++index;
	}
	return (result);
}

t_bitset bitset_xor(t_bitset *bitset1, t_bitset *bitset2)
{
	t_bitset result;
	uint64_t index;

	index = 0;
	while (index < 4)
	{
		result.set[index] = bitset1->set[index] ^ (bitset2->set[index]);
		++index;
	}
	return (result);
}

t_bitset bitset_difference(t_bitset *bitset1, t_bitset *bitset2)
{
	t_bitset result;
	uint64_t index;

	while (index < 4)
	{
		result.set[index] = bitset1->set[index] & ~(bitset2->set[index]);
		++index;
	}
	return (result);
}
