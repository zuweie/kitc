
## makefile for unc

project_dir   		= $(shell pwd)
build_dir           = $(project_dir)/build

build_obj_dir       = $(build_dir)/objects

export_header_dir 	= $(build_dir)/export_header
bin_dir     = $(build_dir)/bin
lib_dir     = $(build_dir)/lib

test           = test
container_lib  = libcontainer.a

#============================
# 定义过个模块
#============================
base_headers :=
base_sources :=
base_dir :=

container_headers :=
container_sources :=
container_dir :=

mem_pool_headers :=
mem_pool_sources :=
mem_pool_dir     :=

algor_headers :=
algor_sources :=
algor_dir     :=

test_sources :=
test_dir     :=

include ./src/base/*.mk
include ./src/mem_pool/*.mk
include ./src/container/*.mk
include ./src/algor/*.mk
include ./src/test/*.mk

# := 意思是清空原来的变量的内容，放入新的内容

base_objects  	  := $(subst .c,.o,$(base_sources))
container_objects := $(subst .c,.o,$(container_sources))
mem_pool_objects  := $(subst .c,.o,$(mem_pool_sources))
algor_objects     := $(subst .c,.o,$(algor_sources))
test_objects  	  := $(subst .c,.o,$(test_sources))

build_base_objs      := $(addprefix $(build_obj_dir)/, $(notdir $(base_objects)))
build_container_objs := $(addprefix $(build_obj_dir)/, $(notdir $(container_objects)))
build_mem_pool_objs  := $(addprefix $(build_obj_dir)/, $(notdir $(mem_pool_objects)))
build_algor_objs     := $(addprefix $(build_obj_dir)/, $(notdir $(algor_objects)))
build_test_objs      := $(addprefix $(build_obj_dir)/, $(notdir $(test_objects)))

INCLUDE_FLAGS   = $(addprefix -I, $(base_dir)) $(addprefix -I, $(container_dir)) $(addprefix -I, $(mem_pool_dir)) $(addprefix -I, $(algor_dir))
TEST_LINK_FLAGS = -lcunit
LIB_LINK_FLAGS  = 

DEBUG_CFLAGS    =  -Wall -g
CFLAGS          =  -Wall

# .PHONY: debug
# debug:
# 	@echo $(INCLUDE_FLAGS)
# 	@echo $(CFLAGS)
# 	@echo $(DEBUG_CFLAGS)
# 	@echo $(TEST_LINK_FLAGS)
# 	@echo $(LIB_LINK_FLAGS)
# 	@echo ---------------------
# 	@echo $(base_sources)
# 	@echo $(base_headers)
# 	@echo $(mem_pool_sources)
# 	@echo $(mem_pool_headers)
# 	@echo $(test_sources)
# 	@echo ----------------------
# 	@echo $(base_objects)
# 	@echo $(container_objects)
# 	@echo $(mem_pool_objects)
# 	@echo $(algor_objects)
# 	@echo $(test_objects)
# 	@echo ----------------------
# 	@echo $(data_curr_dir)

#记录一下
# $< => 冒号右边第一个对象，例如
# xx.o : xx.c ($< == xx.c)
# $@ : 冒号左边第一个对象，例如
# xx.o : xx.c ($@ == xx.o)
# $^ : 依赖列表，例如
# xx : xx.o yy.o zz.o ($^ == xx.o, yy.o zz.o)

.PHONY: test
test: $(test)

$(test): $(test_sources) $(base_sources) $(container_sources) $(mem_pool_sources) $(algor_sources)
	mkdir -p $(bin_dir)
	$(CC) $(INCLUDE_FLAGS) $(TEST_LINK_FLAGS) $(DEBUG_CFLAGS) $^ -o $(bin_dir)/$@

.PHONY: container_lib
container_lib: $(container_lib)

$(container_lib): $(base_objects) $(mem_pool_objects) $(container_objects)
	mkdir -p $(export_header_dir)
	mkdir -p $(lib_dir)
	$(AR) -r $(lib_dir)/$@ $(build_base_objs) $(build_mem_pool_objs) $(build_container_objs)
	cp $(base_headers) $(mem_pool_headers) $(container_headers) $(export_header_dir)

%.o : %.c
	mkdir -p $(build_obj_dir)
	$(CC) $(INCLUDE_FLAGS) $(LIB_LINK_FLAGS) $(CFLAGS) -c $< -o $(build_obj_dir)/$(notdir $@)

.PHONY: clean
clean:
	rm -rf $(test_objects) $(base_objects) $(mem_pool_objects) $(container_objects) $(build_dir)
 
