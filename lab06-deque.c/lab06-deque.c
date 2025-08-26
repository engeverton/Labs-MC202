#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef *df_alloc(long capacity, double factor)
{
    dequef *deque = (dequef *) malloc(sizeof(dequef));
    if (deque) {
	deque->data = (float *) malloc(capacity * (sizeof(float)));
	if (!deque->data) {
	    free(deque);
	    return NULL;
	}
	deque->first = 0;
	deque->size = 0;
	deque->cap = capacity;
	deque->mincap = capacity;
	deque->factor = factor;
	return deque;
    } else {
	return NULL;
    }
}

/**
  Release a dequef and its data.
**/
void df_free(dequef * D)
{
    if (D) {
	free(D->data);
	free(D);
    }
}



/**
   The size of the deque.
**/
long df_size(dequef * D)
{
    return D->size;
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef * D, float x)
{
    int index;
    if (D->size == D->cap) {
	long new_cap = (long) (D->factor * D->cap);
	float *new_array = (float *) malloc(new_cap * sizeof(float));
	if (new_array) {
	    index = D->first;
	    for (int i = 0; i < D->size; i++) {
		new_array[i] = D->data[index];
		index = (index + 1) % D->cap;
	    }
	    D->cap = new_cap;
	    D->first = 0;
	    free(D->data);
	    D->data = new_array;
	} else {
	    return 0;
	}
    }

    index = (D->first + D->size) % D->cap;
    D->data[index] = x;
    D->size++;
    return 1;
}



/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, the returned float is meaningless.
**/
float df_pop(dequef * D)
{
    if (D->size == D->cap / (D->factor * D->factor)
	&& (D->cap / D->factor) >= D->mincap) {
	long new_cap = (long) (D->cap / D->factor);
	if (new_cap < D->mincap) {
	    new_cap = D->mincap;
	}
	float *new_array = (float *) malloc(new_cap * sizeof(float));
	if (new_array) {
	    int index = D->first;
	    for (int i = 0; i < D->size; i++) {
		new_array[i] = D->data[index];
		index = (index + 1) % D->cap;
	    }
	    D->cap = new_cap;
	    D->first = 0;
	    free(D->data);
	    D->data = new_array;
	}
    }

    D->size--;
    int index = (D->first + D->size) % D->cap;
    float result = D->data[index];
    if (D->size == 0) {
	D->first = 0;
    }
    return result;

}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef * D, float x)
{
    if (D->size == D->cap) {
	long new_cap = (long) (D->factor * D->cap);
	float *new_array = (float *) malloc(new_cap * sizeof(float));
	if (new_array) {
	    int index = D->first;
	    for (int i = 0; i < D->size; i++) {
		new_array[i] = D->data[index];
		index = (index + 1) % D->cap;
	    }
	    D->cap = new_cap;
	    D->first = 0;
	    free(D->data);
	    D->data = new_array;
	} else {
	    return 0;
	}
    }

    D->first = (D->first - 1 + D->cap) % D->cap;
    D->data[D->first] = x;
    D->size++;
    return 1;
}



/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, the returned float is meaningless.
**/
float df_eject(dequef * D)
{
    int index = D->first;
    if (D->size == D->cap / (D->factor * D->factor)
	&& (D->cap / D->factor) >= D->mincap) {
	long new_cap = (long) (D->cap / D->factor);
	if (new_cap < D->mincap) {
	    new_cap = D->mincap;
	}
	float *new_array = (float *) malloc(new_cap * sizeof(float));
	if (new_array) {
	    for (int i = 0; i < D->size; i++) {
		new_array[i] = D->data[index];
		index = (index + 1) % D->cap;
	    }
	    D->cap = new_cap;
	    D->first = 0;
	    free(D->data);
	    D->data = new_array;
	}
    }

    float result = D->data[index];
    D->first = (D->first + 1) % D->cap;
    D->size--;
    return result;
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef * D, long i, float x)
{
    if (i >= 0 && i < D->size) {	//mudei de D->cap
	D->data[(D->first + i) % D->cap] = x;
    }
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] the returned float is meaningless.
**/
float df_get(dequef * D, long i)
{
    if (i >= 0 && i < D->size) {	//mudei de //D->cap
	return D->data[(D->first + i) % D->cap];
    } else {
	return 0;
    }
}



/**
   Print the elements of D in a line.
**/
void df_print(dequef * D)
{
    int index = D->first;
    printf("deque (%ld):", D->size);
    for (int i = 0; i < D->size; i++) {
	if (index == D->cap) {
	    index = 0;
	}
	//if (i > 0){
	//printf(" ");
	//}
	printf(" %.1f", D->data[index]);
	index++;
    }
    printf("\n");
}