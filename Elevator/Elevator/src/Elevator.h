#pragma once
#include <iostream>

class Elevator {
public:
	int queue[50];
	int queueLen;

public:
	Elevator() = default;
	Elevator(int startingLevel) {
		for (int i = 0; i < 50; i++) {
			queue[i] = -1;
		}
		queue[0] = startingLevel;
		queueLen = 1;
	}

	void shiftQueue() {
		for (int i = 1; i < queueLen; i++) {
			queue[i - 1] = queue[i];
		}
		queueLen--;
	}

	void shiftRightFrom(int n) {
		for (int i = queueLen - 1; i >= n; i--) {
			queue[i + 1] = queue[i];
		}
	}

	int getQueueLen() {
		return queueLen;
	}

	int *getQueue() {
		return queue;
	}

	/*void setQueueByIndex(int startI, int endI) {
		queue[startI] = queue[endI];
	}*/

	void setQueueByVal(int i, int val) {
		queue[i] = val;
		queueLen++;
	}
};