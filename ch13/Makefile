CFLAGS = -g -Wall
OBJDIR = obj

all: dir oobsend oobrecv

oobsend: $(OBJDIR)/oob_send.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/oob_send.o: oob_send.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

oobrecv: $(OBJDIR)/oob_recv.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/oob_recv.o: oob_recv.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm oobsend oobrecv
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)