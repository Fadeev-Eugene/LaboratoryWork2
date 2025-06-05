CC = g++
CFLAGS = -g -Wall -Iinclude -std=c++17 -MMD -MP -I/usr/include
LDFLAGS = -pthread
LDLIBS = -lsqlite3 -lstdc++fs

SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = app
TARGET = $(TARGET_DIR)/fnaf

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(SRC_FILES))

$(shell mkdir -p $(BUILD_DIR) $(TARGET_DIR))

all: $(TARGET) db_copy install-deps

$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

db_copy:
	@cp -f $(SRC_DIR)/Nights.db $(TARGET_DIR)/Nights.db 2>/dev/null || true

install-deps:
	@echo "Installing dependencies..."
	@sudo apt-get update >/dev/null 2>&1 && sudo apt-get install -y build-essential cmake libsqlite3-dev >/dev/null 2>&1 || \
	(echo "Automatic dependency installation failed. Please install manually: build-essential cmake libsqlite3-dev" && exit 1)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET) $(TARGET_DIR)/Nights.db

-include $(DEP_FILES)

.PHONY: all clean db_copy install-deps
