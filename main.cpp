#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <string>

const int NUM_CHEMICALS = 8; 

using ChemSet = std::bitset<NUM_CHEMICALS>;

std::vector<std::string> chemicalList = {
    "Linalool", "Eugenol", "Camphor", "Thymol",
    "Menthol", "Citral", "Myrcene", "Geraniol"
};

std::unordered_map<std::string, ChemSet> plantMatrix = {
    { "Basil",    ChemSet("00000011") },
    { "Lavender", ChemSet("00000101") },
    { "Thyme",    ChemSet("00001000") }
};

std::vector<std::string> findSharedChemicals(const std::vector<std::string>& selectedPlants) {
    if (selectedPlants.empty()) return {};
    ChemSet common = plantMatrix[selectedPlants[0]];
    for (size_t i = 1; i < selectedPlants.size(); ++i) {
        common &= plantMatrix[selectedPlants[i]];
    }
    std::vector<std::string> result;
    for (int index = 0; index < NUM_CHEMICALS; ++index) {
        if (common.test(index)) {
            result.push_back(chemicalList[index]);
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