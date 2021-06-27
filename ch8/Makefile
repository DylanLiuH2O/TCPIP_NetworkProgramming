CFLAGS = -g -Wall
OBJDIR = obj

all: dir gethostbyname gethostbyaddr

gethostbyname: $(OBJDIR)/gethostbyname.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/gethostbyname.o: gethostbyname.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

gethostbyaddr: $(OBJDIR)/gethostbyaddr.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/gethostbyaddr.o: gethostbyaddr.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm gethostbyname gethostbyaddr
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)