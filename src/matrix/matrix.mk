local_dir := $(project_dir)/src/matrix

matrix_sources += $(wildcard $(local_dir)/*.c)
matrix_headers += $(wildcard $(local_dir)/*.h)
matrix_dir 	 += $(local_dir)