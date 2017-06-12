CC = gcc
FLAGS = -std=c99

OBJXOR= xorerFunct.o cut_main.o misc.o
OBJJOIN= joinerFunct.o join_main.o xorerFunct.o misc.o

OBJDIR = build/obj
VPATH = src:build/obj

# Creacion del codigo objeto
ALL: main.o xorer joiner
	$(CC) $< -o build/raid5

$(OBJDIR)/misc.o: misc.c misc.h  | $(OBJDIR)
	$(CC) -c $(FLAGS) $< -o $@

$(OBJDIR)/xorerFunct.o: xorerFunct.c xorerFunct.h misc.h | $(OBJDIR)
	$(CC) -c $(FLAGS) $< -o $@

$(OBJDIR)/joinerFunct.o: joinerFunct.c joinerFunct.h misc.h xorerFunct.h | $(OBJDIR)
	$(CC) -c $(FLAGS) $< -o $@

$(OBJDIR)/join_main.o: join_main.c joinerFunct.h xorerFunct.h misc.h | $(OBJDIR)
	$(CC) -c $(FLAGS) $< -o $@

$(OBJDIR)/cut_main.o: cut_main.c xorerFunct.h misc.h | $(OBJXOR)
	$(CC) -c $(FLAGS) $< -o $@

$(OBJDIR)/main.o: main.c | $(OBJDIR)
	$(CC) -c $(FLAGS) $< -o $@

# Creacion del directorio de salida en caso que no existiera

$(OBJDIR):
	mkdir -p build/obj

# Creacion del XORer

xorer: $(OBJXOR)
	$(CC) $^ -o build/CUT

# Creacion del JOINer

joiner: $(OBJJOIN)
	$(CC) $^ -o build/JOIN

# Limpiar los objetos antiguos para empezar denuevo
clean:
	rm -f build/obj/*.o
	rm -f build/CUT build/JOIN


