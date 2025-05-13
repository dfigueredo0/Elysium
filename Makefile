BUILD_DIR := build
GENERATOR := "Visual Studio 17 2022"
ARCH := x64
CONFIG := Debug

.PHONY: all clean

q ?= 0

ifeq ($(q), 1)
    SILENT := >nul 2>&1
    MSBUILD_FLAGS := /nologo /verbosity:quiet
else
    SILENT :=
    MSBUILD_FLAGS :=
endif

all:
	@echo "Building project..."
	@cmake -S . -B $(BUILD_DIR) -G $(GENERATOR) -A $(ARCH) -DCMAKE_BUILD_TYPE=$(CONFIG) $(SILENT)
	@cmake --build $(BUILD_DIR) --config $(CONFIG) -- $(MSBUILD_FLAGS) $(SILENT)
	@echo "Build complete."

clean:
	@echo "Removing build directory..."
	@cmake --build $(BUILD_DIR) --target clean $(SILENT) || echo "Nothing to clean with CMake."
	@if exist $(BUILD_DIR) rd /s /q $(BUILD_DIR) 
	@echo "Clean complete."