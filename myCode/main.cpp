/**
 * @file main.cpp
 * @brief Entry point for performing multiple StudentDatabase operations
 *
 * @date 22-Jan-2024
 * @author Sree Samanvitha Manoor Vadhoolas
 */
#include <iostream>
#include <cstdlib>

using namespace std;

// Add your project's header files here
#include "SimpleUI.h"
#include "StudentDb.h"

/**
 * @brief Main function of the application.
 *
 * Creates instances of StudentDb and SimpleUI classes and runs the UI to start the application.
 *
 * @return int Returns 0 upon successful execution.
 */
int main()
{
	cout << "lab3 started." << endl;
	StudentDb sd;
	SimpleUI su(sd);
	su.run();

	return 0;
}
