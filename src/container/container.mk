local_dir := $(project_dir)/src/container

container_sources += $(wildcard $(local_dir)/*.c)
container_headers += $(wildcard $(local_dir)/*.h)
container_dir 	+= $(local_dir)