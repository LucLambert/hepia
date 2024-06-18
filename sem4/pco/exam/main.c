#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define NB_TRAIN_NORTH 100
#define NB_TRAIN_SOUTH 100
#define DELAY 5000

pthread_mutex_t mutex_n, mutex_s;
sem_t sem_train_n, sem_train_s;
int nb_req_a=0;
int cpt_nb_train_n=0, cpt_nb_train_s=0, cpt_nb_trajet=0;
bool last_train_direction_north=true;

void* task_train_north(void* arg){
	int id_train = *(int*)arg;


	// attendre avant de lancer un train vers le nord
	sem_wait(&sem_train_n);

	// si 20 train sur la ligne attendre
	if (cpt_nb_train_n == 20) {
		usleep(DELAY*10);
	}
	// si dernier train était direction nord on peut lancer un autre train vers le nord.
	if (last_train_direction_north) {
		sem_post(&sem_train_n);
	}

	printf("train %d vers le nord avec %d autres trains\n", id_train, cpt_nb_train_n);

	// inc nbr trains
	pthread_mutex_lock(&mutex_n);
	cpt_nb_train_n++;
	pthread_mutex_unlock(&mutex_n);


	// simule trajet d'un train
	usleep(DELAY);


	//train arrive decompte
	pthread_mutex_lock(&mutex_n);
	cpt_nb_trajet++;
	cpt_nb_train_n--;
	pthread_mutex_unlock(&mutex_n);

	printf("train %d arrive depuis le nord\n", id_train);

	// si plus de train vers le nord on peut lancer train direction sud.
	if (cpt_nb_train_n==0) {
		pthread_mutex_lock(&mutex_n);
		sem_post(&sem_train_s);
		last_train_direction_north=false;
		pthread_mutex_unlock(&mutex_n);
	}
	return NULL;
}

void* task_train_south(void* arg){
	int id_train = *(int*)arg;

	// attendre avant de lancer un train vers le sud
	sem_wait(&sem_train_s);

	// si 20 train sur la ligne attendre
	if (cpt_nb_train_s == 20) {
		usleep(DELAY*10);
	}
	// si dernier train était direction sud on peut lancer un autre train vers le sud.
	if (!last_train_direction_north) {
		sem_post(&sem_train_s);
	}

	printf("train %d vers le sud avec %d autres trains\n", id_train, cpt_nb_train_s);

	// inc nbr trains
	pthread_mutex_lock(&mutex_s);
	cpt_nb_train_s++;
	pthread_mutex_unlock(&mutex_s);


	// simule trajet d'un train
	usleep(DELAY);

	//train arrive decompte
	pthread_mutex_lock(&mutex_s);
	cpt_nb_trajet++;
	cpt_nb_train_s--;
	pthread_mutex_unlock(&mutex_s);

	printf("train %d arrive depuis le sud\n", id_train);

	// si plus de train vers le sud on peut lancer train direction nord.
	if (cpt_nb_train_s==0) {
		pthread_mutex_lock(&mutex_s);
		sem_post(&sem_train_n);
		last_train_direction_north=true;
		pthread_mutex_unlock(&mutex_s);
	}
	return NULL;
}

int main() 
{
	int i;
	pthread_t task_train_n[NB_TRAIN_NORTH];
	pthread_t task_train_s[NB_TRAIN_SOUTH];

	int id_train_n[NB_TRAIN_NORTH];
	for (i=0; i<NB_TRAIN_NORTH; i++) {
		id_train_n[i]=i;
	}
	int id_train_s[NB_TRAIN_SOUTH];
	for (i=0; i<NB_TRAIN_SOUTH; i++) {
		id_train_s[i]=i;
	}
	
	assert(sem_init(&sem_train_n, 0, 0)==0);
	assert(sem_init(&sem_train_s, 0, 0)==0);
	assert(pthread_mutex_init(&mutex_n, NULL)==0);
	assert(pthread_mutex_init(&mutex_s, NULL)==0);

	for (i=0; i<NB_TRAIN_NORTH; i++)
		assert(pthread_create(&task_train_n[i], NULL, task_train_north, (void*)&id_train_n[i])==0);
	for (i=0; i<NB_TRAIN_SOUTH; i++)
		assert(pthread_create(&task_train_s[i], NULL, task_train_south, (void*)&id_train_s[i])==0);


	sem_post(&sem_train_n);

	for (i=0; i<NB_TRAIN_NORTH; i++)
		assert(pthread_join(task_train_n[i], NULL)==0);
	for (i=0; i<NB_TRAIN_SOUTH; i++)
		assert(pthread_join(task_train_s[i], NULL)==0);

	printf("Nombres de trajets : %d\n", cpt_nb_trajet);
}

