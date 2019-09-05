
## makefile for unc

project_dir   		:= $(shell pwd)
export_header_dir 	:= $(project_dir)/out/export_header

bin_dir     := $(project_dir)/bin
lib_dir     := $(bin_dir)/lib

program    := unc
libs       := libunc.a

#============================
# 定义过个模块
#============================
base_headers :=
base_sources :=
base_dir :=

mem_pool_headers :=
mem_pool_sources :=
mem_pool_dir     :=

test_sources :=
test_dir     :=

include ./src/base/*.mk
include ./src/mem_pool/*.mk
include ./src/test/*.mk

base_objects  	 := $(subst .c,.o,$(base_sources))
mem_pool_objects := $(subst .c,.o,$(mem_pool_sources))
test_objects  	 := $(subst .c,.o,$(test_sources))

INCLUDE_FLAGS   := $(addprefix -I, $(base_dir)) $(addprefix -I, $(mem_pool_dir)) 
PROGRAM_CFLAGS  := -lm -g -Wall -O3 $(INCLUDE_FLAGS) 
LIBS_CFLAGS     := -lm $(INCLUDE_FLAGS) 

.PHONY: debug
debug:
	@echo $(INCLUDE_FLAGS)
	@echo $(PROGRAM_CFLAGS)
	@echo $(LIBS_CFLAGS)
	@echo ---------------------
	@echo $(base_sources)
	@echo $(base_headers)
	@echo $(mem_pool_sources)
	@echo $(mem_pool_headers)
	@echo $(test_sources)
	@echo ----------------------
	@echo $(base_objects)
	@echo $(mem_pool_objects)
	@echo $(test_objects)
	@echo ----------------------
	@echo $(data_curr_dir)

MV  :=  mv -f
RM  :=  rm 

.PHONY: all
all: $(program)

$(program): $(test_sources) $(base_sources) $(mem_pool_sources) 
	mkdir -p $(bin_dir)
	$(CC) $(PROGRAM_CFLAGS) $^ -o $(bin_dir)/$@

.PHONY: libs
libs: $(libs)

$(libs): $(base_sources) $(mem_pool_sources)
	mkdir -p $(export_header_dir)
	mkdir -p $(lib_dir)
	$(AR) -r $(lib_dir)/$@ $^
	cp $(base_headers) $(mem_pool_headers) $(export_header_dir)

.PHONY: clean
clean:
	$(RM) -rf $(base_objects) $(mem_pool_objects) $(bin_dir) $(export_header_dir)/*.h 

 
