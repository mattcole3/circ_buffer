/*
 * circ_buffer.h
 *
 *  Created on: Apr 11, 2013
 *      Author: mcole
 */

#ifndef CIRC_BUFFER_H_
#define CIRC_BUFFER_H_

#define CIRC_BUFFER_MAX_BUFFER_ENTRIES 4096
#define CIRC_BUFFER_TOP_OF_BUFFER  (CIRC_BUFFER_MAX_BUFFER_ENTRIES - 1)

typedef struct _sensorReading {
	char sensorName[32];
	float sensorValue;
} sensorReadingStr;

typedef union _dataSet {
	double bitMask;
	sensorReadingStr sensorReading;
} dataSetStr;

typedef struct _ringBuffer {
	int readIndex;
	int writeIndex;
	dataSetStr dataSet[CIRC_BUFFER_MAX_BUFFER_ENTRIES];
} ringBuffer;


//
// Init the ringbuffer by allocating memory and returning a pointer to the buffer
// Return: valid pointer on success
//         NULL on failure
//
ringBuffer*  initRingBuffer();

//
// Adds a number of data points (one-to-many) to the ringbuffer
// Return: 0 on success
//         -1 on failure
//
int writeIntoBuffer(ringBuffer *myRingBuffer, dataSetStr* myData, int numDataPoints);

//
// Reads next data set from ring buffer
// Return: pointer to next dataset on success
//         NULL on failure
//
dataSetStr* readFromBuffer(ringBuffer *myRingBuffer);

//
// Destroys ring buffer
// Return: 0 on success
//         -1 on failure
//
int destroyRingBuffer(ringBuffer* myRingBuffer);

#endif /* CIRC_BUFFER_H_ */
