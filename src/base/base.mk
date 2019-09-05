local_dir := $(project_dir)/src/base

base_sources += $(wildcard $(local_dir)/*.c)
base_headers += $(wildcard $(local_dir)/*.h)
base_dir 	+= $(local_dir)
