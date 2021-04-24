sfml-app: main.o Animation.o Player.o Platform.o Collider.o
	g++ main.o Collider.o Animation.o Player.o Platform.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Player.h Platform.h
	g++ -c main.cpp 

Collider.o: Collider.cpp Collider.h
	g++ -c Collider.cpp

Animation.o: Animation.cpp Animation.h
	g++ -c Animation.cpp 

Player.o: Player.cpp Player.h
	g++ -c Player.cpp 

Platform.o: Platform.cpp Platform.h
	g++ -c Platform.cpp

clean: 
	rm -f *.o 
