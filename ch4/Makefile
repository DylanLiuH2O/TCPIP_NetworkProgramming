CFLAGS = -g -Wall
OBJDIR = obj

all: dir eserver eclient

eserver: $(OBJDIR)/echo_server.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_server.o: echo_server.c
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
	@-rm eserver eclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)