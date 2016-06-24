# Base Makefile for project build.
#
# Author: Edson Alves (edsonalves@unb.br)
# Date: 22/03/2016

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
BIN_DIR = bin
BIN_DIR_TEST = test/bin
OBJ_DIR_TEST = test/obj
SRC_DIR_TEST = test/src

# C++ compiler
CC = g++

# Flags, includes and libs
CFLAGS = -W -Wall -pedantic -std=c++11 -MMD -g3
INCLUDES = -Iinclude `sdl-config --cflags`
LIBS = `sdl-config --libs` -lpthread -lSDL_image -lSDL_ttf

# Game info
NAME = jtj
GAME = $(BIN_DIR)/$(NAME)

# Project sources and objects
SRC = ${wildcard $(SRC_DIR)/*.cpp}
OBJ = ${addprefix $(OBJ_DIR)/, ${notdir ${SRC:.cpp=.o}}}

# Needs for tests
SRCM = src/box.cpp
SRCM = src/enemy.cpp
SRCM = src/game.cpp
SRCM = src/gameobject.cpp
SRCM = src/gameoverscreen.cpp
SRCM = src/initscreen.cpp
SRCM = src/jack.cpp
SRCM = src/label.cpp
SRCM = src/level.cpp
SRCM = src/optionsscreen.cpp
OBJM = $(SRCM:.cpp=.o)

.PHONY: all clean depend

all:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)
	$(MAKE) $(GAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Building $@
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(GAME): $(OBJ)
	@echo Building $(NAME) ...
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBS)
	@echo --- Done

lib: $(OBJ)
	@echo ar rcs $(LIB_DIR)/libjtj.a $(OBJ)
	@ar rcs $(LIB_DIR)/libjtj.a $(OBJ)

clean:
	@echo Cleaning...
	@rm -rf obj/ bin/ *~

testBox: $(SRC_DIR_TEST)/TestBox.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created


testEnemy: $(SRC_DIR_TEST)/TestEnemy.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testGame: $(SRC_DIR_TEST)/TestGame.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testGameObject: $(SRC_DIR_TEST)/TestGameObject.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testGameOverScreen: $(SRC_DIR_TEST)/TestGameOverScreen.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testInitScreen: $(SRC_DIR_TEST)/TestInitScreen.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testJack: $(SRC_DIR_TEST)/TestJack.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testLabel: $(SRC_DIR_TEST)/TestLabel.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testLevel: $(SRC_DIR_TEST)/TestLevel.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

testOptionsScreen: $(SRC_DIR_TEST)/TestOptionsScreen.cpp
	@echo Compiling $@
	@mkdir -p $(BIN_DIR_TEST)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(BIN_DIR_TEST)/$@ $< lib/libjtj.a -lcppunit $(LIBS)
	@echo --- Done, $(BIN_DIR_TEST)/$@ created

-include $(OBJ:.o=.d)
