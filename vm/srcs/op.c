/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/11/03 22:15:08 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_operations	op_tab[17] =
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
	{
		.name = "or",
		.argc = 3,
		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.opcode = 7,
		.cycle = 6,
		.comment = "ou  (or   r1, r2, r3   r1 | r2 -> r3",
		.argtype = 1,
		.dir_size = 4,
		.carry = 0
	},
	{
		.name = "xor",
		.argc = 3,
		.args = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.opcode = 8,
		.cycle = 6,
		.comment = "ou (xor  r1, r2, r3   r1^r2 -> r3",
		.argtype = 1,
		.dir_size = 4,
		.carry = 0
	},
	{
		.name = "zjmp",
		.argc = 1,
		.args = {T_DIR},
		.opcode = 9,
		.cycle =  20,
		.comment = "jump if zero",
		.argtype = 0,
		.dir_size = 2,
		.carry = 0
	},
	{
		.name = "ldi",
		.argc = 3,
		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.opcode = 10,
		.cycle = 25,
		.comment = "load index",
		.argtype = 1,
		.dir_size = 2,
		.carry = 0
	},
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
	{
		.name = "fork",
		.argc = 1,
		.args = {T_DIR},
		.opcode = 12,
		.cycle = 800,
		.comment = "fork",
		.argtype = 0,
		.dir_size = 2,
		.carry = 0
	},
	{
		.name = "lld",
		.argc = 2,
		.args = {T_DIR | T_IND, T_REG},
		.opcode = 13,
		.cycle = 10,
		.comment = "long load",
		.argtype = 1,
		.dir_size = 4,
		.carry = 1
	},
	{
		.name = "lldi",
		.argc = 3,
		.args = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.opcode = 14,
		.cycle = 50,
		.comment = "long load index",
		.argtype = 1,
		.dir_size = 2,
		.carry = 1
	},
	{
		.name = "lfork",
		.argc = 1,
		.args = {T_DIR},
		.opcode = 15,
		.cycle = 1000,
		.comment = "long fork",
		.argtype = 0,
		.dir_size = 2,
		.carry = 0
	},
	{
		.name = "aff",
		.argc = 1,
		.args = {T_REG},
		.opcode = 16,
		.cycle = 2,
		.comment = "aff",
		.argtype = 1,
		.dir_size = 4,
		.carry = 0
	}
};
