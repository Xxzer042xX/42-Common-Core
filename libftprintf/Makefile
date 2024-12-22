NAME = libftprintf.a
CC = cc
INCLUDE = include
LIBFTDIR = libft
SRCDIR = src
BONUSDIR = srcb
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


BONUSFILES = $(BONUSDIR)/ft_parsing_bonus.c \
	     	 $(BONUSDIR)/ft_print_char_bonus.c \
	     	 $(BONUSDIR)/ft_print_hex_bonus.c \
	     	 $(BONUSDIR)/ft_print_int_bonus.c \
	    	 $(BONUSDIR)/ft_print_pointer_bonus.c \
	    	 $(BONUSDIR)/ft_print_str_bonus.c \
			 $(BONUSDIR)/ft_str_padding_bonus.c \
			 $(BONUSDIR)/ft_str_precision_bonus.c \
	    	 $(BONUSDIR)/ft_print_uint_bonus.c \
	    	 $(BONUSDIR)/ft_printf_bonus.c \
			 $(BONUSDIR)/ft_int_dot_bonus.c \
			 $(BONUSDIR)/ft_int_minus_bonus.c \
			 $(BONUSDIR)/ft_int_padding_bonus.c \
			 $(BONUSDIR)/ft_int_width_bonus.c \
			 $(BONUSDIR)/ft_print_sign_bonus.c \

OFILES = $(CFILES:.c=.o)
BONUS_OFILES = $(BONUSFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) bonus
	@cp $(LIBFTDIR)/libft.a $(NAME)
	@$(AR) $(ARFLAGS) $(NAME) $(OFILES)

bonus: $(BONUS_OFILES)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) bonus
	@cp $(LIBFTDIR)/libft.a $(NAME)
	@$(AR) $(ARFLAGS) $(NAME) $(BONUS_OFILES)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFTDIR) -c $< -o $@

clean:
	@$(RM) $(OFILES) $(BONUS_OFILES)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
