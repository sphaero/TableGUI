GCOMPILER = gcc
CFLAGS    = `pkg-config --cflags --libs gl libxml-2.0`
LIBS       = `pkg-config --libs gl libxml-2.0`

INC_            = /usr/local/include
LIB_            = /usr/local/lib

compile:
	$(GCOMPILER) $(CFLAGS) -o GUI.o -c GUI.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o GUI_widget.o -c GUI_widget.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o GUI_button.o -c GUI_button.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o GUI_tabset.o -c GUI_tabset.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o GUI_checkbox.o -c GUI_checkbox.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o GUI_scrollbar.o -c GUI_scrollbar.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o GUI_contentbox.o -c GUI_contentbox.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) $(CFLAGS) -o main.o -c main.c -I$(INC_) -L$(LIB_) -lbasicutils -lglfw -lfreetype
	$(GCOMPILER) -Wall -o ./Build/test -I$(INC_) -L$(LIB_) main.o GUI.o GUI_widget.o GUI_contentbox.o GUI_button.o GUI_checkbox.o GUI_tabset.o GUI_scrollbar.o -lbasicutils -lglfw -lfreetype $(CFLAGS)
	./Build/test

