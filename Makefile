CC := g++
CXXFLAGS := -g -Wall -Iinclude -std=c++17 -MMD -MP
LDFLAGS := -pthread
LDLIBS := -lsqlite3 -lstdc++fs

SRC_DIR := src
BUILD_DIR := build
TARGET_DIR := app
TARGET := $(TARGET_DIR)/fnaf

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

$(shell mkdir -p $(BUILD_DIR) $(TARGET_DIR))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
	@cp -f $(SRC_DIR)/Nights.db $(TARGET_DIR)/Nights.db 2>/dev/null || true

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET_DIR)

-include $(DEPS)
