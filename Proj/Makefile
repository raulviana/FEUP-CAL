.PHONY: all clean
all: smartDelivery

CFLAGS = -Wall -Wextra -Werror
OBJECTS = main.o menu.o

smartDelivery: $(OBJECTS)
	@g++ $(CFLAGS) -pedantic $(OBJECTS) -o smartDelivery

menu.o main.o: menu.h

clean:
	@rm -f smartDelivery $(OBJECTS)