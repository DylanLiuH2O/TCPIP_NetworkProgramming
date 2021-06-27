CFLAGS = -g -Wall
OBJDIR = obj

all: dir desto todes syscpy stdcpy esserver esclient

desto: $(OBJDIR)/desto.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/desto.o: desto.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

todes: $(OBJDIR)/todes.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/todes.o: todes.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

syscpy: $(OBJDIR)/syscpy.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/syscpy.o: syscpy.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

stdcpy: $(OBJDIR)/stdcpy.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/stdcpy.o: stdcpy.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

esserver: $(OBJDIR)/echo_stdserver.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_stdserver.o: echo_stdserver.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

esclient: $(OBJDIR)/echo_stdclient.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_stdclient.o: echo_stdclient.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm todes desto syscpy stdcpy esserver esclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)