CFLAGS = -g -Wall
OBJDIR = obj

all: dir econv

econv: $(OBJDIR)/endian_conv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/endian_conv.o: endian_conv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm econv
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)