all:
	clang++ -o Bin/Main Source/*.cpp Source/*/*.cpp -std=c++17 -Wall -Wextra -Wpedantic -g -lsfml-graphics -lsfml-window -lsfml-system -lpugixml
