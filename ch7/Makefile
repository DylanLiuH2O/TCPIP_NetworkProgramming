CFLAGS = -g -Wall
OBJDIR = obj

all: dir fserver fclient

fserver: $(OBJDIR)/file_server.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/file_server.o: file_server.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

fclient: $(OBJDIR)/file_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/file_client.o: file_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm fserver fclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)