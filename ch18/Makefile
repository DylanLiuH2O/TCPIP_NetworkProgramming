CFLAGS = -g -Wall -pthread
OBJDIR = obj

all: dir thread1 thread2 thread3 thread4 \
	 mutex semaphore chatserv chatclnt

thread1: $(OBJDIR)/thread1.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/thread1.o: thread1.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

thread2: $(OBJDIR)/thread2.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/thread2.o: thread2.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

thread3: $(OBJDIR)/thread3.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/thread3.o: thread3.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

thread4: $(OBJDIR)/thread4.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/thread4.o: thread4.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

mutex: $(OBJDIR)/mutex.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/mutex.o: mutex.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

semaphore: $(OBJDIR)/semaphore.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/semaphore.o: semaphore.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

chatserv: $(OBJDIR)/chat_server.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/chat_server.o: chat_server.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

chatclnt: $(OBJDIR)/chat_client.o
	cc $(CFLAGS) $^ -o $@
$(OBJDIR)/chat_client.o: chat_client.c
	@mkdir -p $(OBJDIR)
	cc $(CFLAGS) -c $^ -o $@

dir:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@-rm thread1 thread2 thread3 thread4 \
		 mutex semaphore chatserv chatclnt
	@-rm $(OBJDIR)/*.o
	@-rm -r $(OBJDIR)