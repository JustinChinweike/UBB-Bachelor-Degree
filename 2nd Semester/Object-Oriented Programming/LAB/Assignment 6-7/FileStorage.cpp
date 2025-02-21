#include "FileStorage.h"
#include <fstream>
#include "RepositoryException.h"


void FileStorage::saveToCSV(const std::vector<TrenchCoat>& shoppingBasket,
	const std::string& filename)
{
	std::ofstream file(filename); 
	if (!file.is_open()) {
		throw RepositoryException("Sorry, I can't open the file for writing"); 
	}

	for (const auto& trenchCoat : shoppingBasket) {
		file << trenchCoat.getTrenchID() << ","
			<< trenchCoat.getTrenchSize() << ","
			<< trenchCoat.getTrenchColour() << ","
			<< trenchCoat.getTrenchPrice() << ","
			<< trenchCoat.getTrenchQuantity() << ","
			<< trenchCoat.getTrenchPhotographyLink()
			<< "\n";
	}
	file.close(); 
}

void FileStorage::saveToHTML(const std::vector<TrenchCoat>& shoppingBasket, 
	const std::string& filename) {

	std::ofstream file(filename);
	if (!file.is_open()) {
		throw RepositoryException("Sorry, I can't open the file for writing.");
	}
	file << "<html><head><title>Shopping Basket</title><head><body><table Border=\"1\">\n";
	file << "<tr><th>ID</th><th>Size</th><th>Colour</th><th>Price</th><th>Quantity</th><th>Link</th></tr>\n";
	
	for (const auto& trenchCoat : shoppingBasket){
		file << "<tr><td>" << trenchCoat.getTrenchID() << "</td><td>" << trenchCoat.getTrenchSize() << "</td><td>"
			<< trenchCoat.getTrenchColour() << "</td><td>" << trenchCoat.getTrenchPrice() << "</td><td>"
			<< trenchCoat.getTrenchQuantity() << "</td><td>" << trenchCoat.getTrenchPhotographyLink() << "</td></tr>\n";
	}

	file << "</table></body></html>";
	file.close();
}