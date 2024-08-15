# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohimi <mohimi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/05 14:55:25 by mohimi            #+#    #+#              #
#    Updated: 2024/08/11 12:31:37 by mohimi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror

FILE = parcing_bonus.c main_bonus.c \
		utils_bonus.c helper_bonus.c

OBJECT_FILE = $(FILE:.c=.o)

NAME = philo_bonus

GREEN = \033[1;32m
YELLOW = \033[1;33m
all: $(NAME)

$(NAME): $(OBJECT_FILE)
	$(CC) $(FLAGS) $(OBJECT_FILE) -o $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"
%.o: %.c Philo_bonus.h
	@echo "\033[0;34mCompiling $<.\033[0;m"
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "\033[0;31mRemoving object files.\033[0;m"
	rm -f $(OBJECT_FILE)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

fclean: clean
	@echo "\033[0;31mRemoving executable file.\033[0;m"
	rm -f $(NAME)
	@echo "\033[1;32mFClean DONE ✅\033[0;m"

re: fclean all

.PHONY: clean