#include "fastareader.h"

// CONSTRUCTOR

fastareader::fastareader(std::string const &nom) : filename(nom)
{
	std::fstream fichier(filename);	
	std::string line, ligne_temp;
	// checks if file was opened properly : 
	if (fichier.fail())	throw std::string("The following file : " + filename +" was unsuccessfully opened");
	
	char c('a'); // with letters use ' , ' otherwise don't use characters for numbers.
	
	while (fichier.get(c)) // stops at end of file when getline returns false	
	{
	if (line[0] == '>') 
		{						
		sequence = line.erase(0, std::string::npos);	// erases ">"
		} 
							
		runMatrix
		 													
	}
}
//METHODS	
bool fastareader::printSequence(std::string const &chosen_sequence) const {	//Prints sequence
	
	for (auto& paire:sequences) 
	{	
		if (paire.first == chosen_sequence) {	
			std::cout << paire.second << std::endl;
			return true;
			}
	}	
	return false;
}
