#include <iostream>
#include "network.h"
#include <ctime>

int main() {
    srand(time(NULL));

    std::vector<int> structure = {16, 24, 2};
    Network my_network(structure, 3);
    
    std::vector<double> input(3);
    std::vector<double> target(2);

    std::vector<int> input_count(10);

    int batch_size = 8;

    for(int i = 0; i < 2000000; i++){
        input[0] = rand() % 2;
        input[1] = rand() % 2;
        input[2] = rand() % 2;

        input_count[input[0]]++;

        std::fill(target.begin(), target.end(), 0.0);
        target[(input[0] || input[1]) && input[2]] = 1.0;

        my_network.set_input(input);
        my_network.calculate_network_output();
        my_network.calculate_deltas(target);
        my_network.accumulate_gradients();

        if((i + 1) % batch_size == 0){
            my_network.apply_batch_update(batch_size); 
        }

        if(i % 10000 == 0){
            // std::cout << "A: " << input[0] << " B: " << input[1] << std::endl;
            std::cout << my_network.calculate_loss(target) << std::endl;
        }
    }

    std::cout<< "-----------------Weights---------------------"<<std::endl;
    for(int i = 0; i < my_network.layers_.size(); i++){
        for(int j = 0; j < my_network.layers_[i].neurons_.size(); j++){
            std::cout << my_network.layers_[i].neurons_[j].weights_[0] << " ";
        }
        std::cout << std::endl;
    }

    while(true){
        int a, b, c;
        std::cout << "Digit 1: ";
        std::cin >> a;
        std::cout << "Digit 2: ";
        std::cin >> b;
        std::cout << "Digit 3: ";
        std::cin >> c;

        input = {(double)a, (double)b, (double)c};
        my_network.set_input(input);
        my_network.calculate_network_output();
        for(double o : my_network.network_output_){
            std::cout << o * 100<< " ";
        }
        std::cout << std::endl;
    }

    return 0;
}