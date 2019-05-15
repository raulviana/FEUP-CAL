.PHONY: all clean
all: smartDelivery

CFLAGS = -Wall -Wextra -Werror
OBJECTS = connection.o node.o graphviewer.o map.o menu.o main.o 

smartDelivery: $(OBJECTS)
	@g++ $(CFLAGS) -pedantic $(OBJECTS) -o smartDelivery

main.o: menu.h map.h
menu.o: menu.h
connection.o: connection.h 
graphviewer.o: graphviewer.h connection.h  edgetype.h
map.o: map.h  graphviewer.h graph.h node.h
node.o: node.h

clean:
	@rm -f smartDelivery $(OBJECTS)