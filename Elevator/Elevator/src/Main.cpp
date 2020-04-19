#include "ElevatorSystem.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
	srand((int)std::time(0));

	ElevatorSystem *es = new ElevatorSystem(2);

	es->elevators[0]->queue[0] = 9;

	int max = (int)std::rand() % 10;
	//max = 2;
	std::cout << "Max: " << max << std::endl;
	//int test[2] = { 10, 2};
	for (int i = 0; i < max; i++) {
		int request = (int)std::rand() % 10;
		//request = i;
		//request = test[i];
		std::cout << "Req: " << request << std::endl;
		es->sendRequest(request);
	}
	std::cout << std::endl;

	while (1) {
		es->updateAndPrint();
		Sleep(2000);
		break;
	}

	return 0;
}