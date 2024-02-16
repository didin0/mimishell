# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 16:00:48 by mabbadi           #+#    #+#              #
#    Updated: 2023/04/13 18:36:29 by mabbadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a


SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_calloc.c ft_strmapi.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_strdup.c ft_split.c ft_itoa.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_atoi.c \

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

BONUS_OBJ = ${BONUS:.c=.o}

FLAGS = -Wall -Wextra -Werror

OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
		@ar rc ${NAME} ${OBJ}

all: ${NAME}

%.o: %.c
		cc ${FLAGS} -I ./ -c $< -o ${<:.c=.o}

clean:
		@rm -rf ${OBJ} ${BONUS_OBJ}

fclean: clean
		@rm -rf ${NAME}

re: fclean all

bonus: ${OBJ} ${BONUS_OBJ}
		@ar rc ${NAME} ${OBJ} ${BONUS_OBJ}

.PHONY: all re clean fclean bonus