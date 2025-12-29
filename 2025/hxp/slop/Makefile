slop: slop.c
	$(CC) -O2 -static -Wall -Wextra -Wpedantic -Werror -D_FORTIFY_SOURCE=3 -fcf-protection -fno-stack-protector -fstack-clash-protection -Wl,-z,relro,-z,now $< -o $@

clean:
	$(RM) -- $(TARGETS)

.PHONY: clean
