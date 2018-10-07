C=g++
SRC_DIR=./src
OUT_DIR=./build
STD=c++17

COMPILE=$(C) $(SRC_DIR)/*.cpp --std=$(STD)

clean:
	@rm -rf $(OUT_DIR)/*
build-debug:
	@mkdir -p $(OUT_DIR)
	@$(COMPILE) -o $(OUT_DIR)/audiowire.debug -g -D DEBUG
build-release:
	@mkdir -p $(OUT_DIR)
	@$(COMPILE) -o $(OUT_DIR)/audiowire