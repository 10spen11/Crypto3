input = test-encr
output = output-dec

ALL: HASH BRUTE RAINBOW
	
HASH: hash.c MD5
	gcc -o hash hash.c
	
BRUTE: brute_force.c MD5
	gcc -o brute_force brute_force.c
	
RAINBOW: rainbow.c MD5
	gcc -o rainbow rainbow.c
	

MD5: md5.h
	
CLEAN:
	rm -f hash
	rm -f brute-force
	rm -f rainbow
	make ALL