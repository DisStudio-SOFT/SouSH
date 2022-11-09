coms_src := $(shell find src/commands -name *.c)
coms_obj := $(patsubst src/commands/%.c, output/commands/%.o, $(coms_src))

sh_src := $(shell find src/sh -name *.c)

$(coms_obj): output/commands/%.o : src/commands/%.c
	@mkdir -p $(dir $@) && \
	gcc $(patsubst output/commands/%.o, src/commands/%.c, $@) -o $@
	@echo "CC        $@"

coms_out_1 := $(shell find output/commands/ -name *.o)
coms_out_2 := $(patsubst output/commands/%.o, soush-files/%, $(coms_out_1))

$(coms_out_2): soush-files/% : output/commands/%.o
	@mkdir -p $(dir $@) && \
	cp $(patsubst soush-files/%, output/commands/%.o, $@) $@
	@echo "INSTALL   $@"

.PHONY: all build-commands build-sh install

all: build-commands build-sh

build-commands: $(coms_obj)
	@echo "-------------------------------"
	@echo "| Done!                       |"
	@echo "| Commands in output/commands |"
	@echo "-------------------------------"

build-sh:
	@gcc $(sh_src) -o soush
	@echo "-------------------------------"
	@echo "| Done!                       |"
	@echo "| Shell in soush              |"
	@echo "-------------------------------"

install: $(coms_out_2)
	@sudo cp soush /bin/soush
	@sudo mkdir -p /bin/soush-files
	@sudo rm -r /bin/soush-files
	@sudo cp -r soush-files /bin/soush-files
	@echo "---------------------------------------"
	@echo "| Done!                               |"
	@echo "| Shell and all commands is installed |"
	@echo "---------------------------------------"