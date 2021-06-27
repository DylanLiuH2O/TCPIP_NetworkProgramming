CFLAGS = -g -Wall
OBJDIR = obj

all: dir select eselserver eclient 

select: $(OBJDIR)/select.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/select.o: select.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

eselserver: $(OBJDIR)/echo_selectserv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_selectserv.o: echo_selectserv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

eclient: $(OBJDIR)/echo_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_client.o: echo_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm select eclient eselserver
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)