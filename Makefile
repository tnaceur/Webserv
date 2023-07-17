NAME = Webserv
CPPFLAGS = #-Wall -Wextra -Werror

SRCS = clients.cpp\
		main.cpp\

RM = rm -rf
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	c++ $(CPPFLAGS) $(OBJS) -o $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
re : fclean all