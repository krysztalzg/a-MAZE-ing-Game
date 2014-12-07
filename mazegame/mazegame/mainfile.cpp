#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Application.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));

	Application* app = new Application();

	app->ApplicationMainLoop();

	cout << "Press enter to continue ...";
	cin.get();
	return 0;
}