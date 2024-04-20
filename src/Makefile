all:	read1 debug1 read2 debug2 csqsum debug_csqsum

read1:
	clear
	gcc a1.c -o read_dataset1.bin -O3 -fPIC -Wall -pedantic -D DATASET1

debug1:
	clear
	gcc a1.c -o read_debug_dataset1.bin -O3 -fPIC -Wall -pedantic -D DATASET1 -D DEBUG

read2:
	clear
	gcc a1.c -o read_dataset2.bin -O3 -fPIC -Wall -pedantic -l m -D DATASET2

debug2:
	clear
	gcc a1.c -o read_debug_dataset2.bin -O3 -fPIC -Wall -pedantic -l m -D DATASET2 -D DEBUG


csqsum:
	clear
	gcc a1.c -o csqsum.bin -O3 -fPIC -Wall -pedantic -D DATASET1 -D CSQSUM

debug_csqsum:
	clear
	gcc a1.c -o csqsum_debug.bin -O3 -fPIC -Wall -pedantic -D DATASET1 -D CSQSUM -D DEBUG
