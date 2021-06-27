CFLAGS = -g -Wall
OBJDIR = obj

all: dir eserver eclient2 opserver opclient

eserver: $(OBJDIR)/echo_server.o
	gcc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_server.o: echo_server.c
	@mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -c $^ -o $@

eclient2: $(OBJDIR)/echo_client2.o
	gcc $(CFLAGS) $^ -o $@
$(OBJDIR)/echo_client2.o: echo_client2.c
	@mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -c $^ -o $@

opserver: $(OBJDIR)/op_server.o
	gcc $(CFLAGS) $^ -o $@
$(OBJDIR)/op_server.o: op_server.c
	@mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -c $^ -o $@

opclient: $(OBJDIR)/op_client.o
	gcc $(CFLAGS) $^ -o $@
$(OBJDIR)/op_client.o: op_client.c
	@mkdir -p $(OBJDIR)
	gcc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm eserver eclient2 opserver opclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)