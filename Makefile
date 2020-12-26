all: rho felma

rho: ./src/rho.c
	gcc -o rho ./src/rho.c -lgmp -O3 -march=native -std=c99

felma: ./src/felma.c
	gcc -o felma ./src/felma.c -lgmp -O3 -march=native -std=c99

clean: 
	rm -rf rho
