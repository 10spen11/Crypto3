input = test-encr
output = output-dec

ALL: HASH BRUTE DICT RAINBOW
	
HASH: hash.c MD5
	gcc -m32 -o hash hash.c
	
BRUTE: brute_force.c rainbowFuncs.h MD5
	gcc -m32 -o brute_force brute_force.c
	
DICT: dictionary.c rainbowFuncs.h MD5
	gcc -m32 -o dictionary dictionary.c
	
RAINBOW: rainbow.c rainbowGen.c rainbowFuncs.h MD5
	gcc -m32 -o rainbow rainbow.c
	gcc -m32 -o rainbowGen rainbowGen.c
	

MD5: md5.h
	
CLEAN:
	rm -f hash
	rm -f brute-force
	rm -f rainbow
	make ALL