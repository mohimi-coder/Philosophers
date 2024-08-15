CC = cc

FLAGS = -Wall -Wextra -Werror
FILE = parcing.c main.c fill_data.c utils.c helper.c

OBJECT_FILE = $(FILE:.c=.o)

NAME = philo

GREEN = \033[1;32m
YELLOW = \033[1;33m
all: $(NAME)

$(NAME): $(OBJECT_FILE)
	$(CC) $(FLAGS) $(OBJECT_FILE) -o $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"
%.o: %.c Philosopher.h
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
