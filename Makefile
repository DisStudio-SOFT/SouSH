coms_src := $(shell find src/commands -name *.c)
coms_obj := $(patsubst src/commands/%.c, soush-files/%, $(coms_src))

sh_src := $(shell find src/sh -name *.cc)

$(coms_obj): soush-files/% : src/commands/%.c
	@mkdir -p $(dir $@) && \
	gcc $(patsubst soush-files/%, src/commands/%.c, $@) -o $@
	@echo "CC        $@"

.PHONY: all build-commands build-sh install

all: build-commands build-sh

build-commands: $(coms_obj)
	@echo "-------------------------------"
	@echo "| Done!                       |"
	@echo "| Commands in soush-files     |"
	@echo "-------------------------------"

build-sh:
	@g++ $(sh_src) -o soush
	@echo "-------------------------------"
	@echo "| Done!                       |"
	@echo "| Shell in soush              |"
	@echo "-------------------------------"

install: build-commands build-sh
	@sudo cp soush /bin/soush
	@sudo rm -r /bin/soush-files/*
	@sudo cp -r soush-files /bin/
	@rm soush
	@rm -r soush-files
	@echo "---------------------------------------"
	@echo "| Done!                               |"
	@echo "| Shell and all commands is installed |"
	@echo "---------------------------------------"