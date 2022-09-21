game: main.cpp Game.h GameEntity.h Mirror.h
	g++ main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./game