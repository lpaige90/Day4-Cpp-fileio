#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

int main() {
	std::ifstream dataFile;//File containing our data
	std::ofstream writeFile;//File we'll write our results to

	std::string dataString;//String corresponding to a line of data
	std::size_t dataStringLength;

	std::size_t commaPosition;
	std::list<int> commaList;//List to contain comma positions
	std::size_t commaListSize;
	int comma;
	int prevComma;
	int lastComma;

	std::string dataChar;

	int firstNumber;
	int nextNumber;
	int lastNumber;
	int product;
	int tempProduct;

	dataFile.open ("multiplyme.txt");
	writeFile.open ("results.txt");

	if (dataFile.is_open()) {
		while ( getline (dataFile, dataString) ) {
			std::string numberString = "";
			std::vector<int> numbers;

			dataStringLength = dataString.length();

			for ( int i=0; i<dataStringLength; ++i ) {
				dataChar = dataString.at(i);
				if (dataChar==",") {
					commaList.push_back (i);
				}
			}

			commaListSize = commaList.size();

			if ( commaListSize > 0 ) {
				comma = commaList.front();

				for ( int i=0; i<comma; ++i ) {
					numberString += dataString.at(i);
				}

				commaList.pop_front();


				firstNumber = std::stoi(numberString);//Convert string to int

				while ( commaList.size() > 0 ) {
					numberString = "";
					prevComma = comma;
					comma = commaList.front();

					for ( int i=prevComma+1; i<comma; ++i ) {
						numberString += dataString.at(i);
					}

					nextNumber = std::stoi(numberString);
					numbers.push_back(nextNumber);

					commaList.pop_front();
				}

				numberString = "";
				lastComma = comma;

				for ( int i=lastComma+1; i<dataStringLength; ++i ) {
					numberString += dataString.at(i);
				}

				lastNumber = std::stoi(numberString);

				product = firstNumber;

				for ( int i=0; i<numbers.size(); ++i ) {
					tempProduct = product*numbers.at(i);
					product = tempProduct;
				}

				product = product*lastNumber;//Calculate final product

				//Write product to results.txt
				if (writeFile.is_open()) {
					writeFile << product << std::endl;
				} else {
					"Unable to open write file.";
				}
			} else {
				if ( dataStringLength==0 ) {
					writeFile << "" << std::endl;
				} else {
					writeFile << "No Product" << std::endl;
				}
			}
		}
	} else {
		std::cout << "Data file could not be opened.";
	}

	dataFile.close();

	writeFile.close();

	return 0;
}