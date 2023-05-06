# names file project10_scheduler and compiles them with below dependencies
scheduler: job.o scheduler.o
	gcc -o scheduler job.o scheduler.o

# makes pre-compiled package with below dependencies

job.o: job.c job.h
	gcc -c job.c

# makes pre-compiled package with below dependencies
scheduler.o: scheduler.c job.h 
	gcc -c scheduler.c


