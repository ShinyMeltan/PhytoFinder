#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <string>

const int NUM_CHEMICALS = 8; // Adjust as needed

using ChemSet = std::bitset<NUM_CHEMICALS>;

// Mock chemical index
std::vector<std::string> chemicalList = {
    "Linalool", "Eugenol", "Camphor", "Thymol",
    "Menthol", "Citral", "Myrcene", "Geraniol"
};

// Mock plant → chemical map
std::unordered_map<std::string, ChemSet> plantMatrix = {
    { "Basil",    ChemSet("00000011") }, // Linalool, Eugenol
    { "Lavender", ChemSet("00000101") }, // Linalool, Camphor
    { "Thyme",    ChemSet("00001000") }  // Thymol
};

// Find intersection of chemicals across selected plants
std::vector<std::string> findSharedChemicals(const std::vector<std::string>& selectedPlants) {
    ChemSet common;
    if (selectedPlants.empty()) return {};

    common = plantMatrix[selectedPlants[0]];
    for (size_t i = 1; i < selectedPlants.size(); ++i) {
        common &= plantMatrix[selectedPlants[i]];
    }

    std::vector<std::string> result;
    for (int i = 0; i < NUM_CHEMICALS; ++i) {
        if (common.test(i)) {
            result.push_back(chemicalList[i]);
        }
    }
    return result;
}

int main() {
    std::vector<std::string> selection;

    std::cout << "Available plants:\n";
    for (const auto& [name, _] : plantMatrix) {
        std::cout << " - " << name << '\n';
    }

    std::cout << "\nEnter plant names (type 'done' to finish):\n";
    while (true) {
        std::string plant;
        std::cout << "> ";
        std::getline(std::cin, plant);
        if (plant == "done") break;
        if (plantMatrix.count(plant)) {
            selection.push_back(plant);
        } else {
            std::cout << "Plant not found.\n";
        }
    }

    auto shared = findSharedChemicals(selection);

    std::cout << "\nCommon chemicals:\n";
    for (const auto& chem : shared) {
        std::cout << " - " << chem << '\n';
    }

    return 0;
}