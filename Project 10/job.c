//utilizes job.h header file to intialize prototypes and linked list structure

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "job.h"

//////////////////////////
// function definitions //
//////////////////////////

void help() {
	printf("List of operation codes:\n");
	printf("\t'h' for help;\n");
	printf("\t'a' for adding a job to the scheduler;\n");
	printf("\t'p' for removing a job from the scheduler;\n");
	printf("\t'u' for searching jobs per user;\n");
	printf("\t'j' for searching jobs per capacity;\n");
	printf("\t'l' for listing all jobs;\n");
	printf("\t'q' for quit.\n");
}

void read(char *job_name, char *user_name, int *num_cpus, int *num_gpus, int *memory, double *time, int *priority) {
	if(job_name != NULL) {
		printf("Enter the name of the job: ");
		scanf("%s", job_name);
	}
	if(user_name != NULL) {
		printf("Enter the name of the user: ");
		scanf("%s", user_name);
	}
	if(num_cpus != NULL) {
		printf("Enter the number of CPUs: ");
		scanf("%d", num_cpus);
	}
	if(num_gpus != NULL) {
		printf("Enter the number of GPUs: ");
		scanf("%d", num_gpus);
	}
	if(memory != NULL) {
		printf("Enter the amount of memory: ");
		scanf("%d", memory);
	}
	if(time != NULL) {
		printf("Enter the amount of time: ");
		scanf("%lf", time);
	}
	if(priority != NULL) {
		printf("Enter the priority: ");
		scanf("%d", priority);
	}
}

/////////////////////////////////////////////////////////
// WARNING - WARNING - WARNING - WARNING - WARNING     //
/////////////////////////////////////////////////////////
// Do not modify anything before this point, otherwise //
// your solution will be considered incorrect.         //
/////////////////////////////////////////////////////////

struct job * add_job(struct job *scheduler, char *job_name, char *user_name, int num_cpus, int num_gpus, int memory, double time, int priority) {
	struct job *cur, *prev, *new_node;

	new_node = malloc(sizeof(struct job));
	prev = malloc(sizeof(struct job));
	cur = malloc(sizeof(struct job));

	if(new_node == NULL) {
		printf("malloc failed in sorted_insert\n");
		return scheduler;
	}
	
	strcpy(new_node->job_name, job_name);
	strcpy(new_node->user_name, user_name);
	new_node->num_cpus = num_cpus;
	new_node->num_gpus = num_gpus;
	new_node->memory = memory;
	new_node->time = time;
	new_node->priority = priority;

	if (scheduler == NULL){
        return new_node;
    }
	
	// sets prev and cur position to insert node at location of priority
	for(cur=scheduler, prev=NULL; (cur != NULL) && (priority <= cur->priority) ;prev=cur, cur=cur->next) { 
	}

	
	//adds in the beginning
	if (prev == NULL) {
		new_node->next = scheduler;
		return new_node;
	} else if (cur == NULL){ //adds in the end
		new_node->next = NULL;
		prev->next = new_node;
		return scheduler;
	} else if (cur->priority == priority){ // adds if less than / equal to, and towards the end if multiple of same priority exists

		struct job *cur2, *prev2;
		cur2 = malloc(sizeof(struct job));
		prev2 = malloc(sizeof(struct job));

		// new prev and cur trackers to find end if there are multiple items of same priority
		for(cur2 = cur, prev2=NULL; (cur2 != NULL) && (priority == cur2->priority) ;prev2=cur2, cur2=cur2->next) {
		}

		new_node->next = cur2;
		prev2->next = new_node;
		return scheduler;
	} else { // other conditions for greater than priority values
		new_node->next = cur;
		prev->next = new_node;
		return scheduler;
	}
}



struct job * pop_job(struct job *scheduler) {
	if (scheduler == NULL){
    	    return NULL;
    	}
		//triggers if there's only one node
    	if (scheduler->next == NULL){
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", scheduler->job_name, scheduler->user_name, scheduler->num_cpus, scheduler->num_gpus, scheduler->memory, scheduler->time, scheduler->priority);
			free(scheduler);
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			return NULL;
    	}
		//deletes in FIFO manner using temp p structure
    	struct job *p = scheduler->next;
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", scheduler->job_name, scheduler->user_name, scheduler->num_cpus, scheduler->num_gpus, scheduler->memory, scheduler->time, scheduler->priority);
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		free(scheduler);
		return p; 
    	
	}


void list_user(struct job *scheduler, char *user_name) {
	//makes new nodes and allocates mem
	struct job *p;
	struct job *q;
	p = malloc(sizeof(struct job));
	q = malloc(sizeof(struct job));
	if (scheduler == NULL) {
		return;
	}
	//makes sure theres one node that matches username to print heading once
	for (p = scheduler; p != NULL; p = p->next) {
		if (strcmp(user_name, p->user_name) == 0) {
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			break;
		}
		
	}
	//used to print header once and not trigger for loop
	p = NULL;
	//checks through nodes for parts with matching username
	for (q = scheduler; q != NULL; q = q->next) {
		if (strcmp(user_name, q->user_name) == 0) {
			printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", q->job_name, q->user_name, q->num_cpus, q->num_gpus, q->memory, q->time, q->priority);
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		}
	}

	
}

void list_jobs(struct job *scheduler, int num_cpus, int num_gpus, int memory, double time) {
	//makes new nodes and allocates mem
	struct job *p;
	struct job *q;
	p = malloc(sizeof(struct job));
	q = malloc(sizeof(struct job));
	if (scheduler == NULL) {
		return;
	}
	
	//makes sure theres one node that matches quantities to print heading once
	for (p = scheduler; p != NULL; p = p->next) {
		if ((p->num_cpus <= num_cpus) && (p->num_gpus <= num_gpus) && (p->memory <= memory) && (p->time <= time)) {
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
			printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
			break;
		}
		
	}

	//used to print header once and not trigger for loop
	p = NULL;

	//checks through nodes for parts with matching parts quantities
	for (q = scheduler; q != NULL; q = q->next) {
		if((q->num_cpus <= num_cpus) && (q->num_gpus <= num_gpus) && (q->memory <= memory) && (q->time <= time)) {
		printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", q->job_name, q->user_name, q->num_cpus, q->num_gpus, q->memory, q->time, q->priority);
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
		}
	}

}

void list_all_jobs(struct job *scheduler) {
	//makes new nodes and allocates mem
	struct job *p;
	p = malloc(sizeof(struct job));
	if (scheduler == NULL) {
		return;
	}
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	printf("| Job name             | User name            | CPUs | GPUs | Mem. | Time   | Priority |\n");
	printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	//prints all items	
	for (p = scheduler; p != NULL; p = p->next) {
		printf("| %-20s | %-20s | %4d | %4d | %4d | %6.2f | %8d |\n", p->job_name, p->user_name, p->num_cpus, p->num_gpus, p->memory, p->time, p->priority);
		printf("|----------------------|----------------------|------|------|------|--------|----------|\n");
	}
}

struct job * clear_jobs(struct job *scheduler) {
	//assigns to temp p node to avoid dangling pointer and then releases from memory
	struct job *p;
	p = malloc(sizeof(struct job));
    while (scheduler != NULL){
        p = scheduler;
        scheduler = scheduler->next;
        free(p);
    }
    return NULL;
}