game: main.cpp Game.h GameEntity.h Mirror.h Player.h BorderWall.h Level.h Light.h Wall.h Antitarget.h
	g++ main.cpp -o game.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./game.out