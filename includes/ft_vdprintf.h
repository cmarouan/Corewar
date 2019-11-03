/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmney <hmney@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:17:05 by hmney             #+#    #+#             */
/*   Updated: 2019/11/03 21:25:48 by hmney            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VDPRINTF_H
# define FT_VDPRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"
# define ED 2047
# define EL 32767
# define ABS(value) (value < 0 ? -value : value)

typedef struct			s_singleprecision
{
	unsigned long		mantissa:52;
	unsigned int		exponent:11;
	unsigned int		sign:1;
}						t_singleprecision;

typedef struct			s_extendedprecision
{
	unsigned long		mantissa:63;
	unsigned int		integer_part:1;
	unsigned int		exponent:15;
	unsigned int		sign:1;
}						t_extendedprecision;

union					u_extendedprecision
{
	long double			float_number;
	t_extendedprecision	data;
}						extendedprecision;

union					u_singleprecision
{
	double				float_number;
	t_singleprecision	data;
}						singleprecision;

typedef struct			s_float
{
	char				*data;
	char				*final_data;
	char				*mantissa_binary;
	char				*mantissa;
	char				*exponent;
	int					comma;
	int					bias;
	unsigned long		mantissa_number;
	unsigned int		exponent_number;
	unsigned int		sign;
	unsigned int		integer_part;
}						t_float;

typedef struct			s_vdprintf
{
	int 				fd;
	int					flag_plus;
	int					flag_minus;
	int					flag_zero;
	int					flag_space;
	int					flag_hashtag;
	int					field_width;
	int					precision;
	int					h;
	int					hh;
	int					l;
	int					ll;
	int					longdouble;
	int					z;
	int					j;
	char				conversion_character;
	int					spaces;
	int					zeros;
	int					length_result;
}						t_vdprintf;

int						ft_vdprintf(int fd, const char *format, va_list ap);
int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
int						management_format(t_vdprintf *store, char *format,
		va_list ap);
void					management_display_u(va_list ap, t_vdprintf *store);
void					management_display_o(va_list ap, t_vdprintf *store);
void					management_display_d(va_list ap, t_vdprintf *store);
void					management_display_x(va_list ap, t_vdprintf *store);
void					management_display_f(va_list ap, t_vdprintf *store);
int						conversion_character(t_vdprintf store, char c);
int						conversion_string(t_vdprintf store, char *str);
int						conversion_pointer(t_vdprintf store, void *ptr);
int						conversion_decimal(t_vdprintf store, intmax_t number);
int						conversion_octal(t_vdprintf store, uintmax_t number);
int						conversion_unsigned(t_vdprintf store, uintmax_t number);
int						conversion_hexadecimal(t_vdprintf store, uintmax_t number,
		char c);
int						conversion_percent(t_vdprintf store);
int						conversion_invalid(t_vdprintf store,
char conversion_character);
int						conversion_float(t_vdprintf store, long double number);
int						conversion_binary(t_vdprintf store, int number,
		char c);
char					*ft_itoa_base_uintmaxt(uintmax_t number, int base,
		char c);
void					ft_print_character(t_vdprintf store, int number, int c);
int						is_a_conversion_character(char c);
int						is_a_flag(char c);
int						is_a_lengthmodifier(char c);
int						get_number(char *format, int *counter);
char					*calcul_float(t_vdprintf *store, t_float *float_data);
char					*calcul_final_data(t_vdprintf store, t_float *float_data);
char					*ft_addition(char *number1, char *number2);
char					*ft_multiple(char *number1, char *number2);
char					*ft_exponent(int base, unsigned int exponent);
char					*convert_binary(unsigned long mantissa_number,
		int length);
int						calcul_empty_space(char *number);
void					delete_empty_space(char **number);
char					*calcul_fd_specialcase(t_vdprintf store,
		t_float float_data);
char					*add_zeros(t_float float_data, char *data, int l_data,
		int l_final);
int						length_float(t_vdprintf *store, t_float *float_data,
		int length_data);

#endif
