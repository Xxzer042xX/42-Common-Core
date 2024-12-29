NAME = libftprintf.a
CC = cc
INCLUDE = include
LIBFTDIR = libft
SRCDIR = src
CFLAGS = -Wall -Werror -Wextra -g
AR = ar
ARFLAGS = rcs
RM = rm -f


CFILES = $(SRCDIR)/ft_parsing.c \
	     $(SRCDIR)/ft_print_char.c \
	     $(SRCDIR)/ft_print_hex.c \
	     $(SRCDIR)/ft_print_int.c \
	     $(SRCDIR)/ft_print_pointer.c \
	     $(SRCDIR)/ft_print_str.c \
		 $(SRCDIR)/ft_str_padding.c \
		 $(SRCDIR)/ft_str_precision.c \
	     $(SRCDIR)/ft_print_uint.c \
	     $(SRCDIR)/ft_printf.c \
		 $(SRCDIR)/ft_int_dot.c \
		 $(SRCDIR)/ft_int_minus.c \
		 $(SRCDIR)/ft_int_padding.c \
		 $(SRCDIR)/ft_int_width.c \
		 $(SRCDIR)/ft_print_sign.c \

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) bonus
	@cp $(LIBFTDIR)/libft.a $(NAME)
	@$(AR) $(ARFLAGS) $(NAME) $(OFILES)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFTDIR) -c $< -o $@

clean:
	@$(RM) $(OFILES)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
