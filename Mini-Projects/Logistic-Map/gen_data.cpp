#include <iostream>
#include <fstream>

#define D_R 0.0001
#define NUM_VALUES 1000

int main(void){
	std::ofstream outfile("logistic_out");
	if (!outfile.is_open()) {
		std::cerr << "Error: could not open output file." << std::endl;
		return 1;
	}

	for (double r = 3.5; r<= 4.0; r += D_R) {
		outfile << r << " ";
		
		double x = 0.5;

		// Get first one hundred out of the way
		for (int i = 0; i < 100; i++) {
			x = r * x * (1 - x);
		}

		for (int i = 0; i < NUM_VALUES; i++) {
			x = r * x * (1 - x);
			outfile << x << " ";
		}

		outfile << std::endl;
	}
	outfile.close();
}
