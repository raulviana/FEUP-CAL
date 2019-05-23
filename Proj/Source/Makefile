.PHONY: all clean
all: smartDelivery

CFLAGS = -Wall -Wextra -Werror
OBJECTS = 2opt.o path.o delivery.o connection.o node.o graphviewer.o map.o menu.o main.o 

smartDelivery: $(OBJECTS)
	@g++ $(CFLAGS) -pedantic $(OBJECTS) -o smartDelivery

main.o: menu.h map.h
menu.o: menu.h
connection.o: connection.h 
graphviewer.o: graphviewer.h connection.h  edgetype.h
map.o: map.h  graphviewer.h graph.h node.h delivery.h
node.o: node.h
delivery.o: delivery.h
path.o: path.h map.h 2opt.h
2opt.o: 2opt.h graph.h

clean:
	@rm -f smartDelivery $(OBJECTS)