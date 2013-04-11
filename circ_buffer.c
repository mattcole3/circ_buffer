/*
 ============================================================================
 Name        : circ_buffer.c
 Author      : Matt Cole
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circ_buffer.h"

ringBuffer * myRingBuffer;

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	myRingBuffer = initRingBuffer();
	if (!myRingBuffer)
	{
		puts("Init failed\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


//
// Init the ringbuffer by allocating memory and returning a pointer to the buffer
// Return: valid pointer on success
//         NULL on failure
//
ringBuffer*  initRingBuffer()
{
	myRingBuffer = (ringBuffer *)calloc(1, sizeof(ringBuffer));
	if (myRingBuffer == NULL)
	{
		return NULL;
	} else {
		return myRingBuffer;
	}

}

//
// Adds a number of data points (one-to-many) to the ringbuffer
// Return: 0 on success
//         -1 on failure
//
int writeIntoBuffer(ringBuffer *myRingBuffer, dataSetStr* myData, int numDataPoints)
{
	if (myRingBuffer != NULL && myData != NULL && numDataPoints > 0)
	{
		for (int i=0; i<numDataPoints; i++)
		{
			if (!(memcpy(&(myRingBuffer->dataSet[myRingBuffer->writeIndex]), &(myData[i]), sizeof(dataSetStr))))
			{
				return -1;
			}
			myRingBuffer->writeIndex += numDataPoints;
			myRingBuffer->writeIndex &= CIRC_BUFFER_TOP_OF_BUFFER;
			if (myRingBuffer->writeIndex == myRingBuffer->readIndex)
			{
				myRingBuffer->readIndex = ((myRingBuffer->writeIndex+1) & CIRC_BUFFER_TOP_OF_BUFFER);
			}
		}
	}
	else
	{
		return -1;
	}

	return 0;
}

//
// Reads next data set from ring buffer
// Return: pointer to next dataset on success
//         NULL on failure
//
dataSetStr* readFromBuffer(ringBuffer *myRingBuffer)
{
	dataSetStr* dataPtr = (dataSetStr*)&(myRingBuffer->dataSet[myRingBuffer->readIndex]);
	myRingBuffer->readIndex++;
	myRingBuffer->readIndex &= CIRC_BUFFER_TOP_OF_BUFFER;
	return dataPtr;
}

//
// Destroys ring buffer
// Return: 0 on success
//         -1 on failure
//
int destroyRingBuffer(ringBuffer* myRingBuffer)
{
	free(myRingBuffer);
	return 0;
}
