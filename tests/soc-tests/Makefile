.PHONY: all run gdb clean

RESULT = .result
$(shell > $(RESULT))

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

SOC_TESTS_ROOT := $(shell pwd)

# 导出 INC_PATH，包含公共头文件目录
# 注意：不能 export CFLAGS，否则 RISC-V 编译标志会传递给 NPC 模拟器的编译过程
export INC_PATH += $(SOC_TESTS_ROOT)/include

ifdef ALL
  TEST_DIRS := tests/$(ALL)
else
  TEST_DIRS := $(dir $(wildcard tests/*/Makefile))
endif

# TESTS_DIR = tests/char/ tests/flash/
# TESTS = char flash
TESTS := $(notdir $(patsubst %/,%,$(TEST_DIRS)))

all: $(TESTS)
	@echo "test list [$(words $(TESTS)) item(s)]:" $(TESTS)

$(TESTS):
	@if $(MAKE) -C tests/$@ ARCH=$(ARCH) $(MAKECMDGOALS); then \
		printf "[%14s] $(COLOR_GREEN)PASS$(COLOR_NONE)\n" $@ >> $(RESULT); \
	else \
		printf "[%14s] $(COLOR_RED)***FAIL***$(COLOR_NONE)\n" $@ >> $(RESULT); \
	fi

run: all
	@cat $(RESULT)
	@grep -q "FAIL" $(RESULT); FAIL=$$?; rm -f $(RESULT); test $$FAIL -ne 0

gdb: all

clean:
	@for dir in $(TEST_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -rf build/ .result
