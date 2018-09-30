C=g++
SRC_DIR=./src
OUT_DIR=./build
STD=c++17

COMPILE=$(C) $(SRC_DIR)/*.cpp --std=$(STD)

clean:
	@rm -rf ./build/*
build-debug:
	@if [ ! -d "./build" ]; then mkdir build; fi
	@$(COMPILE) -o $(OUT_DIR)/audiowire.debug -g -D DEBUG
build-release:
	@if [ ! -d "./build" ]; then mkdir build; fi
	@$(COMPILE) -o $(OUT_DIR)/audiowire