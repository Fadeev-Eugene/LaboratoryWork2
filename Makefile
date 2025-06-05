CC := g++
CXXFLAGS := -g -Wall -Iinclude -std=c++17 -MMD -MP
LDFLAGS := -pthread
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3 -lstdc++fs

SRC_DIR := src
BUILD_DIR := build
TARGET_DIR := app
TARGET := $(TARGET_DIR)/fnaf
IMG_DIR := $(SRC_DIR)/img
TARGET_IMG_DIR := $(TARGET_DIR)/img

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Создаем директории при необходимости
$(shell mkdir -p $(BUILD_DIR) $(TARGET_DIR) $(TARGET_IMG_DIR))

.PHONY: all install-deps clean

all: install-deps $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@cp -f $(SRC_DIR)/Nights.db $(TARGET_DIR)/Nights.db 2>/dev/null || true
	@if [ -d "$(IMG_DIR)" ]; then \
		cp -r $(IMG_DIR)/* $(TARGET_IMG_DIR)/ 2>/dev/null || true; \
		echo "Images copied to $(TARGET_IMG_DIR)"; \
	fi

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

install-deps:
	@if [ ! -d "/usr/include/SFML" ]; then \
		echo "Installing SFML and SQLite dependencies..."; \
		sudo apt-get update >/dev/null 2>&1; \
		sudo apt-get install -y libsfml-dev libsqlite3-dev >/dev/null 2>&1; \
	fi

clean:
	rm -rf $(BUILD_DIR) $(TARGET_DIR)

-include $(DEPS)
