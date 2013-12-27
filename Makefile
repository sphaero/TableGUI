GCOMPILER = gcc
CFLAGS    = `pkg-config --cflags --libs gl libxml-2.0 x11`
LIBS       = `pkg-config --libs gl libxml-2.0 x11`

INC_            = /usr/local/include
LIB_            = /usr/local/lib
LOCAL_INC_      = /usr/local/include
LOCAL_LIB_      = /usr/local/lib
INC_freetype2   = /usr/include/freetype2
LIB_freetype2   = /usr/lib/freetype2

compile:
	@echo 'Compiting GUI.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI.o -c GUI.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_font.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_font.o -c GUI_font.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_draw.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_draw.o -c GUI_draw.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_widget.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_widget.o -c GUI_widget.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_box.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_box.o -c GUI_box.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_button.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_button.o -c GUI_button.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_entry.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_entry.o -c GUI_entry.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_splitter.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_splitter.o -c GUI_splitter.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_treeview.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_treeview.o -c GUI_treeview.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_tabset.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_tabset.o -c GUI_tabset.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_notebook.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_notebook.o -c GUI_notebook.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_checkbox.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_checkbox.o -c GUI_checkbox.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_scrollbar.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_scrollbar.o -c GUI_scrollbar.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting GUI_contentbox.'
	@$(GCOMPILER) -g $(CFLAGS) -o GUI_contentbox.o -c GUI_contentbox.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) -lbasicutils -lglfw -lfreetype -lcairo
	@echo 'Compiting main file.'
	$(GCOMPILER) -g -Wall -o ./Build/test main.c -I$(INC_) -I$(INC_freetype2) -I$(LOCAL_INC) -L$(LIB_) -L$(LIB_freetype2) -L$(LOCAL_LIB) main.o GUI.o GUI_widget.o GUI_font.o GUI_draw.o GUI_box.o GUI_contentbox.o GUI_entry.o GUI_button.o GUI_notebook.o GUI_splitter.o GUI_treeview.o GUI_checkbox.o GUI_tabset.o GUI_scrollbar.o -lbasicutils -lglfw -lfreetype -lcairo $(LIBS) $(CFLAGS)
	./Build/test