// FileStorage.h
#pragma once
#include <vector> 
#include <string>
#include "Domain.h"
class FileStorage
{
public:
	static void saveToCSV(const std::vector<TrenchCoat>& shoppingBasket, const std::string& filename);
	static void saveToHTML(const std::vector<TrenchCoat>& shoppingBasket, const std::string& filename);

};

