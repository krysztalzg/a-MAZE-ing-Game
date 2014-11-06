#include <cstdlib>
#include <ctime>

#include "Application.h"

int main() {
	srand((unsigned int)time(NULL));

	Application* app = new Application();

	return 0;
}