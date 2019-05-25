.PHONY: all clean
all: smartDelivery

CFLAGS = -Wall -Wextra -Werror
OBJECTS = van.o 2opt.o path.o delivery.o connection.o node.o graphviewer.o map.o menu.o main.o 

smartDelivery: $(OBJECTS)
	@g++ $(CFLAGS) -pedantic $(OBJECTS) -o smartDelivery

main.o: menu.h map.h
menu.o: menu.h map.h path.h delivery.h
connection.o: connection.h 
graphviewer.o: graphviewer.h connection.h  edgetype.h
map.o: map.h  graphviewer.h graph.h node.h delivery.h
node.o: node.h
delivery.o: delivery.h node.h
path.o: path.h map.h 2opt.h van.h
2opt.o: 2opt.h graph.h
van.o: van.h map.h delivery.h

clean:
	@rm -f smartDelivery $(OBJECTS)