CC = g++ 
make: clean main.o Animation.o Player.o Platform.o
	$(CC) main.o Animation.o Player.o Platform.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system  
main.o: main.cpp Animation.h
	$(CC) -c main.cpp 
Animation.o: Animation.cpp Animation.h
	$(CC) -c Animation.cpp 
Player.o: Player.cpp Player.h
	$(CC) -c Player.cpp 
Platform.o: Platform.cpp Platform.h
	$(CC) -c Platform.cpp
clean: 
	rm -f *.o 
