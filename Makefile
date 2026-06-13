# Makefile for TermiFlow - Modular Terminal Productivity Tool

# Compiler configuration
CXX = g++
CXX_MINGW = x86_64-w64-mingw32-g++

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
CORE_DIR = $(SRC_DIR)/core
FEATURES_DIR = $(SRC_DIR)/features

# Output files
LINUX_OUTPUT = $(BUILD_DIR)/termiflow
WINDOWS_OUTPUT = $(BUILD_DIR)/termiflow.exe

# Source files
MAIN_SRC = $(SRC_DIR)/main.cpp
CORE_SRCS = $(wildcard $(CORE_DIR)/*.cpp)
FEATURES_SRCS = $(wildcard $(FEATURES_DIR)/*.cpp)
ALL_SRCS = $(MAIN_SRC) $(CORE_SRCS) $(FEATURES_SRCS)

# Compiler flags
CXXFLAGS = -fdiagnostics-color=always -g -fexceptions -I./$(INCLUDE_DIR)
LINUX_CXXFLAGS = $(CXXFLAGS)
WINDOWS_CXXFLAGS = $(CXXFLAGS) -static -static-libgcc -static-libstdc++

# Test configuration
TEST_DIR = tests
TEST_MAIN = $(TEST_DIR)/main_test.cpp
TEST_SRCS = $(filter-out $(TEST_MAIN),$(wildcard $(TEST_DIR)/*_test.cpp))
TEST_OUTPUT = $(BUILD_DIR)/test_runner

# Phony targets
.PHONY: all help build linux windows clean rebuild run test

# Default target
all: linux

# Help target
help:
	@echo "TermiFlow Makefile - Available targets:"
	@echo ""
	@echo "  make build             - Build for current platform (Linux/Windows)"
	@echo "  make linux             - Build Linux executable (default)"
	@echo "  make windows           - Build Windows executable (requires MinGW)"
	@echo "  make test              - Build and run unit tests (native framework)"
	@echo "  make run               - Build and run Linux executable"
	@echo "  make rebuild           - Clean and rebuild for current platform"
	@echo "  make clean             - Remove build artifacts"
	@echo "  make help              - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make                   - Build Linux version"
	@echo "  make test              - Build and run tests"
	@echo "  make windows           - Build Windows .exe"
	@echo "  make clean rebuild     - Clean and rebuild"

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Linux build target
linux: $(BUILD_DIR)
	@echo "Building TermiFlow for Linux..."
	$(CXX) $(LINUX_CXXFLAGS) $(ALL_SRCS) -o $(LINUX_OUTPUT)
	@echo "✓ Build complete: $(LINUX_OUTPUT)"

# Windows build target
windows: $(BUILD_DIR)
	@echo "Building TermiFlow for Windows..."
	$(CXX_MINGW) $(WINDOWS_CXXFLAGS) $(ALL_SRCS) -o $(WINDOWS_OUTPUT)
	@echo "✓ Build complete: $(WINDOWS_OUTPUT)"

# Build target (alias for linux)
build: linux

# Run target
run: linux
	@echo "Running TermiFlow..."
	./$(LINUX_OUTPUT)

# Rebuild target
rebuild: clean build
	@echo "✓ Rebuild complete"

# Test target - uses native C++ test framework (no external dependencies)
test: $(BUILD_DIR)
	@echo "Building unit tests..."
	$(CXX) $(LINUX_CXXFLAGS) $(CORE_SRCS) $(FEATURES_SRCS) $(TEST_SRCS) $(TEST_MAIN) -o $(TEST_OUTPUT)
	@echo "✓ Test build complete"
	@echo ""
	@echo "Running tests..."
	./$(TEST_OUTPUT)

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete"

# Information target
info:
	@echo "TermiFlow Build Information:"
	@echo "  Compiler: $(CXX)"
	@echo "  Flags: $(LINUX_CXXFLAGS)"
	@echo "  Sources: $(ALL_SRCS)"
	@echo "  Build directory: $(BUILD_DIR)"
	@echo "  Include directory: $(INCLUDE_DIR)"
