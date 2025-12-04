#include <iostream>
#include "network.h"

int main() {
    std::vector<int> structure = {5,10};
    Network my_network(structure, 2);
    
    std::vector<float> input = {1.0, 2.0};
    std::vector<float> target = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    my_network.set_input(input);

    std::vector<float> output = my_network.calculate_network_output();

    for (float i : output){
        std::cout << i << std::endl;
    }

    std::cout << "Loss: " << my_network.calculate_loss(target) << std::endl;

    return 0;
}