# names file project10_scheduler and compiles them with below dependencies
project10_scheduler: job.o project10_scheduler.o
	gcc -o project10_scheduler job.o project10_scheduler.o

# makes pre-compiled package with below dependencies

job.o: job.c job.h
	gcc -c job.c

# makes pre-compiled package with below dependencies
project10_scheduler.o: project10_scheduler.c job.h 
	gcc -c project10_scheduler.c


