all:
	clang++ -o Bin/Main Source/*.cpp Source/*/*.cpp -std=c++17 -Wall -Wextra -pedantic -g -lsfml-graphics -lsfml-window -lsfml-system -lpugixml
