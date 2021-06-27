CFLAGS = -g -Wall
OBJDIR = obj

all: dir nreceiver nsender nreceiver_b nsender_b

nreceiver: $(OBJDIR)/news_receiver.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/news_receiver.o: news_receiver.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

nsender: $(OBJDIR)/news_sender.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/news_sender.o: news_sender.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

nreceiver_b: $(OBJDIR)/news_sender_brd.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/news_sender_brd.o: news_sender_brd.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

nsender_b: $(OBJDIR)/news_receiver_brd.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/news_receiver_brd.o: news_receiver_brd.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm nreceiver nsender nreceiver_b nsender_b
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)