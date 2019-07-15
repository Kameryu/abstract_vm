NAME = abstract_vm

INCL	=	./includes

CLASSH	=	./class_hpp

CLS_DIR	=	class_cpp

CLASSC	=	Env.cpp \
			FOperand.cpp \
			MyExceptions.cpp \
			Operator.cpp

SRCS_PATH = ./srcs

SRCS =		functions.cpp \
			lexer.cpp \
			lexer_e.cpp \
			main.cpp \
			parser_e.cpp \
			parser.cpp

OBJ_DIR	=	obj

OBJ_SRC	=	$(SRCS:%.cpp=$(OBJ_DIR)/%.o)

OBJ_CLS	=	$(CLASSC:%.cpp=$(OBJ_DIR)/%.o)

OBJ		=	$(OBJ_CLS) $(OBJ_SRC)

CC		=	g++

CFLAGS	=	--std=c++1z -Werror -Wall -Wextra -O2

all : make_obj $(NAME)

make_obj :
	mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ_CLS) $(OBJ_SRC)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o : $(CLS_DIR)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCL) -I$(CLASSH)

$(OBJ_DIR)/%.o : $(SRCS_PATH)/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCL) -I$(CLASSH)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all make_obj clean fclean re
