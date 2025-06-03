CC = g++
CFLAGS = -g -Wall -Iinclude -std=c++17 -MMD -MP
LDFLAGS = -pthread
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3 -lstdc++fs

SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = app
TARGET = $(TARGET_DIR)/fnaf

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(SRC_FILES))

# Добавлена переменная для папки с изображениями
IMG_DIR = $(SRC_DIR)/img
TARGET_IMG_DIR = $(TARGET_DIR)/img

$(shell mkdir -p $(BUILD_DIR) $(TARGET_DIR))

# Добавлена цель img_copy в зависимости all
all: $(TARGET) db_copy img_copy

$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

db_copy:
	@cp -f $(SRC_DIR)/Nights.db $(TARGET_DIR)/Nights.db 2>/dev/null || true

# Новая цель для копирования изображений
img_copy:
	@if [ -d "$(IMG_DIR)" ]; then \
    	echo "Copying images directory..."; \
    	mkdir -p $(TARGET_IMG_DIR); \
    	cp -r $(IMG_DIR)/* $(TARGET_IMG_DIR)/; \
  	else \
    	echo "Image directory $(IMG_DIR) not found!"; \
    	exit 1; \
  	fi

# Обновленная цель clean для удаления изображений
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET) \
	$(TARGET_DIR)/Nights.db \
	$(TARGET_IMG_DIR)  # Добавлено удаление папки с изображениями

-include $(DEP_FILES)

.PHONY: all clean db_copy img_copy  # Добавлена img_copy в PHONY
