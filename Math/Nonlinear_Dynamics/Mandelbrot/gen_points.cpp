#include <iostream>
#include <fstream>
#include <complex>

#define D_R 0.0005
#define D_I 0.0005

#define MAX_ITER 1000

int main(void){
	std::ofstream outfile("data_out");
	if (!outfile.is_open()) {
		std::cerr << "Error: could not open output file." << std::endl;
		return 1;
	}

	for (double r = -2; r <= 1; r += D_R) {
		std::cout << "row: " << r << std::endl;

		for (double i = -1.5; i <= 1.5; i += D_I) {
			std::complex<double> c(r, i);
			std::complex<double> z = c;

			int in_set = 1;
			for (int i = 1; i <= MAX_ITER; i++) {
				if (std::abs(z) > 2){
					in_set = 0;
					break;
				}	
			 	z = z * z + c;	
			}

			outfile << r << " " << i << " " << in_set << std::endl;
		}
	}

	outfile.close();
	return 0;
}
