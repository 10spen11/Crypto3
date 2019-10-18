input = test-encr
output = output-dec

ALL: HASH
	
HASH: hash.c MD5
	gcc -o hash hash.c
	
#BRUTE: brute-force.c MD5
#	gcc -m32 -o brute-force brute-force.c

MD5: md5.h
	
CLEAN:
	rm -f decrypt
	rm -f encrypt
	rm -f brute-force
	make ALL