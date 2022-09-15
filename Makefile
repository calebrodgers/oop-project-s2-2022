mymake: main.cpp
	g++ main.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./game