local_dir := $(project_dir)/src/algor

algor_sources += $(wildcard $(local_dir)/*.c)
algor_headers += $(wildcard $(local_dir)/*.h)
algor_dir 	  += $(local_dir)