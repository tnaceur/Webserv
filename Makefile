NAME = Webserv
CPP = c++
F	= -fsanitize=address -fsanitize=undefined
CPPFLAGS = #-Wall -Wextra -Werror

SRCS = $(wildcard *.cpp)

RM = rm -rf
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
re : fclean all

.PHONY:all clean fclean re