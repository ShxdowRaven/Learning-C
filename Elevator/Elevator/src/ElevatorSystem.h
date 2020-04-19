#pragma once
#include "Elevator.h"
#include <cstdlib>
#include <limits>
#include <ctime>

class ElevatorSystem {
public:
	Elevator *elevators[10];
	int totalElevators;
public:
	ElevatorSystem(int totalElevators) {
		if (totalElevators > 10) {
			std::cout << "Invalid number of elevators passed" << std::endl;
			return;
		}
;		for (int i = 0; i < totalElevators; i++) {
			elevators[i] = new Elevator(1);
		}
		this->totalElevators = totalElevators;
	}

	void sendRequest(int reqLevel) {
		struct ElevatorData {
		public:
			Elevator *elevator = NULL;
			int dist = std::numeric_limits<int>::max();
			int index = -1;
			int queueIndex = -1;
			int queueLen = -1;
			bool requiresShift = false;
		};

		ElevatorData leastDist;
		//int leastDistDist = std::numeric_limits<int>::max();
		
		for (int i = 0; i < totalElevators; i++) {
			ElevatorData current;
			current.elevator = elevators[i];
			current.dist = 0;
			current.queueLen = current.elevator->getQueueLen();
			current.requiresShift = false;
			current.queueIndex = -1;	

			/*if (leastDist == NULL)
				leastDist = &current;*/

			int *queue = current.elevator->getQueue();

			for (int j = 0; j < current.queueLen - 1; j++) {
				current.dist += abs(queue[j + 1] - queue[j]);
				if ((reqLevel >= queue[j] && reqLevel <= queue[j + 1]) || (reqLevel <= queue[j] && reqLevel >= queue[j + 1])) {
					//totalDist += abs(queue[j + 1] - reqLevel);
					current.queueIndex = j + 1;
					current.requiresShift = true;
					break;
				}
			}
			if (!current.requiresShift) {
				current.dist += abs(reqLevel - queue[current.queueLen - 1]);
				current.queueIndex = current.queueLen;
			}
			if (current.dist < leastDist.dist) {
				leastDist = current;
			}
		}
		if (leastDist.requiresShift)
			leastDist.elevator->shiftRightFrom(leastDist.queueIndex);
		leastDist.elevator->setQueueByVal(leastDist.queueIndex, reqLevel);
	}

	void updateAndPrint() {
		for (int i = 0; i < totalElevators; i++) {
			Elevator elevator = *elevators[i];
			//elevator.shiftQueue();
			std::cout << "Elevator #" << i << ": len(" << elevator.getQueueLen() << ") ";
			int *queue = elevator.getQueue();
			for (int i = 0; i < elevator.getQueueLen(); i++) {
				std::cout << queue[i] << " ";
			}
			std::cout << std::endl;
		}
	}
};