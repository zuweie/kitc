local_dir      := $(project_dir)/src/test
test_sources   := $(wildcard $(local_dir)/*.c)
test_dir       += $(local_dir)