CFLAGS = -g -Wall
OBJDIR = obj

all: dir tserver tclient

tserver: $(OBJDIR)/tcp_server.o
	cc $(CFLAGS) tcp_server.c -o tserver
$(OBJDIR)/tcp_server.o: tcp_server.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

tclient: $(OBJDIR)/tcp_client.o
	cc $(CFLAGS) tcp_client.c -o tclient
$(OBJDIR)/tcp_client.o: tcp_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm tserver tclient
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)