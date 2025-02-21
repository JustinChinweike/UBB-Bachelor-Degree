//testRepository.cpp
#include "TestAll.h"
#include "Repository.h"
#include "Domain.h"
#include <cassert>
#include <iostream>

void testRepository() {
    std::cout << "Testing Repository" << std::endl;
    Repository repository;
    repository.addTrenchCoat(1, 2, "red", 3, 4, "link");
    assert(repository.getSize() == 1);

    repository.addTrenchCoat(2, 4, "blue", 4, 5, "link2");
    repository.addTrenchCoat(3, 4, "green", 5, 6, "link3");
    repository.addTrenchCoat(4, 5, "yellow", 6, 7, "link4");
    repository.addTrenchCoat(5, 6, "black", 7, 8, "link5");
    assert(repository.getSize() == 5);

    assert(repository.validID(1));
    // Attempt to add a trench coat with an existin ID
    assert(repository.addTrenchCoat(2, 4, "blue", 4, 5, "link2") == false);
    // Check if the size remains the same after failing to add a duplicate trench coat
    assert(repository.getSize() == 5);


    //assert(repository.validID(1));
    //assert(repository.addTrenchCoat(2, 4, "blue", 4, 5, "link2") == false);

    repository.removeTrenchCoat(1);
    assert(repository.getSize() == 4);
    assert(!repository.validID(1));

    repository.updateTrenchCoat(2, 1, 2, "red", 3, 4, "link");
    assert(repository.getTrenchCoat(1).getTrenchID() == 1);
    assert(repository.getTrenchCoat(1).getTrenchSize() == 2);

    TrenchCoat trenchCoat = repository.getTrenchCoat(1);
    assert(trenchCoat.getTrenchID() == 1);

    std::vector<TrenchCoat> trenchCoats = repository.getAllTrenchCoats();
    assert(trenchCoats.size() == 4);

    repository.setFileName("test.txt");
    assert(repository.getFileName() == "test.txt");

    repository.writeToFile();
    repository.readFromFile();
    assert(repository.getSize() == 4);

    assert(repository.getTrenchCoat(1).getTrenchID() == 1);

    TrenchCoat trenchCoat1 = repository.getTrenchCoat(20);
    assert(trenchCoat1.getTrenchID() == -1);


    assert(repository.updateTrenchCoat(1, 20, 2, "red", 3, 4, "link"));
    assert(repository.removeTrenchCoat(20));
    std::cout << "Repository tests passed" << std::endl;




}
