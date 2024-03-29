SRC_NAME =	Bullet.class.cpp \
				Enemy.class.cpp \
				EnemyA.class.cpp \
				EnemyB.class.cpp \
				EnemyEvents.cpp \
				GameEntity.class.cpp \
				Hero.class.cpp \
				Timer.class.cpp \
				display.cpp \
				main.cpp \
				GameMachine.class.cpp


INC_PATH = ./
OBJ_PATH = ./obj/

NAME = ft_retro

CC = clang++

CFLAGS = -Wall -Werror -Wextra -g

SRC_PATH = ./

OBJ_NAME = $(SRC_NAME:.cpp=.o)

LFLAGS = -lncurses

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(INC) $^ -o $@

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
