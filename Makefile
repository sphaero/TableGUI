GCOMPILER = gcc
CFLAGS    = `pkg-config --cflags gl libxml-2.0 glfw3 cairo freetype2`
LIBS      = -lm -lpthread `pkg-config --libs x11 xxf86vm xi xrandr gl libxml-2.0 glfw3 cairo freetype2` -lbasicutils

compile:
	@echo 'Compiling GUI.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI.o -c GUI.c
	@echo 'Compiling GUI_draw.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_draw.o -c GUI_draw.c
	@echo 'Compiling GUI_widget.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_font.o -c GUI_font.c
	@echo 'Compiling GUI_widget.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_entry.o -c GUI_entry.c
	@echo 'Compiling GUI_widget.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_widget.o -c GUI_widget.c
	@echo 'Compiling GUI_box.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_box.o -c GUI_box.c
	@echo 'Compiling GUI_button.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_button.o -c GUI_button.c
	@echo 'Compiling GUI_splitter.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_splitter.o -c GUI_splitter.c
	@echo 'Compiling GUI_treeview.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_treeview.o -c GUI_treeview.c
	@echo 'Compiling GUI_tabset.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_tabset.o -c GUI_tabset.c
	@echo 'Compiling GUI_notebook.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_notebook.o -c GUI_notebook.c
	@echo 'Compiling GUI_checkbox.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_checkbox.o -c GUI_checkbox.c
	@echo 'Compiling GUI_scrollbar.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_scrollbar.o -c GUI_scrollbar.c
	@echo 'Compiling GUI_contentbox.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_contentbox.o -c GUI_contentbox.c
	@echo 'Compiling main file.'
	@$(GCOMPILER) -g $(CFLAGS) -o main.o -c main.c
	@echo 'Linking files.'
	$(GCOMPILER) -o ./Build/test *.o /usr/local/lib/libbasicutils.a $(LIBS) -lbasicutils
	./Build/test

clean:
	@echo 'Cleaning up.'
	rm *.o ./Build/test
