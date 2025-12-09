#include <iostream>
#include "network.h"

int main() {
    std::vector<int> structure = {5,10};
    Network my_network(structure, 2);
    
    std::vector<double> input = {1.0, 2.0};
    std::vector<double> target = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    my_network.set_input(input);

    std::vector<double> output = my_network.calculate_network_output();

    for (double i : output){
        std::cout << i << std::endl;
    }

    std::cout << "Loss: " << my_network.calculate_loss(target) << std::endl;

    my_network.calculate_deltas(target);

    std::cout << "Delta: " << my_network.layers_[0].neurons_[0].signal_error_ << std::endl;

    return 0;
}