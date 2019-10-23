/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoussai <kmoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/10/22 15:54:09 by kmoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	op_tab[17] =
{
	{	.name = "live",
		.argc = 1,
		.args = {T_DIR},
		.opcode = 1,
		.cycle = 10,
		.comment = "alive",
		.argtype = 0,
		.dir_size = 4,
		.carry = 0
	},
	{
		.name = "ld",
		.argc = 2,
		.args = {T_DIR | T_IND, T_REG},
		.opcode = 2,
		.cycle = 5,
		.comment = "load",
		.argtype = 1,
		.dir_size = 4,
		.carry = 1
	},
	{
		.name = "st",
		.argc = 2,
		.args = {T_REG, T_IND | T_REG},
		.opcode = 3,
		.cycle = 5,
		.comment = "store",
		.argtype = 1,
		.dir_size = 4,
		.carry = 0
	},
	{
		.name = "add",
		.argc = 3,
		.args = {T_REG, T_REG, T_REG},
		.opcode = 4,
		.cycle = 10,
		.comment = "addition",
		.argtype = 1,
		.dir_size = 4,
		.carry = 1
	},
	{
		.name = "sub",
		.argc = 3,
		.args = {T_REG, T_REG, T_REG},
		.opcode = 5,
		.cycle = 10,
		.comment = "soustraction",
		.argtype = 1,
		.dir_size = 4,
		.carry = 0
	},
	{
		.name = "and",
		.argc = 3,
		.args = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.opcode = 6,
		.cycle = 6,
		.comment = "et (and  r1, r2, r3   r1&r2 -> r3",
		.argtype = 1,
		.dir_size = 4,
		.carry = 1
	},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 0},
	{
		.name = "sti",
		.argc = 3,
		.args = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.opcode = 11,
		.cycle = 25,
		.comment = "store index",
		.argtype = 1,
		.dir_size = 2,
		.carry = 0
	},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0}
};
