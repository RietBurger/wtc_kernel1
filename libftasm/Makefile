NAME = libfts.a

SRC = ft_bzero.s ft_cat.s ft_isalnum.s ft_isalpha.s ft_isascii.s \
		ft_isdigit.s ft_isprint.s ft_memcpy.s ft_memset.s ft_puts.s\
	   	ft_strcat.s ft_strdup.s ft_strlen.s ft_tolower.s ft_toupper.s

OBJS = ft_bzero.o ft_cat.o ft_isalnum.o ft_isalpha.o ft_isascii.o \
		ft_isdigit.o ft_isprint.o ft_memcpy.o ft_memset.o ft_puts.o\
	   	ft_strcat.o ft_strdup.o ft_strlen.o ft_tolower.o ft_toupper.o 

ASM = nasm -f macho64

.PHONY: clean fclean run re

all: $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	gcc -W -Wall -Werror main.c libfts.a
	make clean

%.o : %.s
	$(ASM) -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
