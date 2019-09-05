local_dir := $(project_dir)/src/mem_pool

mem_pool_sources += $(wildcard $(local_dir)/*.c)
mem_pool_headers += $(wildcard $(local_dir)/*.h)

mem_pool_dir 	 += $(local_dir)