#include "network.h"
#include <iostream>
#include <cmath>

Network::Network(std::vector<int> network_structure, int no_inputs){
    no_network_inputs = no_inputs;

    for(int i = 0; i < network_structure.size(); i++){
        if(i == 0){
            layers.push_back(Layer(network_structure[i], i, no_inputs));
        }
        else{
            layers.push_back(Layer(network_structure[i], i, network_structure[i - 1]));
        }
    }

}

void Network::set_input(std::vector<float> network_input){
    if(network_input.size() == no_network_inputs){
        layers[0].inputs = network_input;
    }
    else{
        std::cout << "Incorrect Number of Inputs";
        exit(1);
    }
}

std::vector<float> Network::calculate_network_output(){
    for(int i = 0; i < layers.size(); i++){
        std::vector<float> out = layers[i].calculate_layer_outputs();

        if(i < layers.size() - 1){
            layers[i + 1].inputs = out;
        }
        else{
            //softmax
            float denom = 0.0;
            for(float v : out){
                denom += std::exp(v);
            }

            std::vector<float> softmax;
            for(float v : out){
                float probability = std::exp(v) / denom;
                softmax.push_back(probability);
            }
            
            network_output = softmax;
            return softmax;
        }
    }
}

float Network::calculate_loss(std::vector<float> target){

    float sum = 0;
    for(int i = 0; i < network_output.size(); i++){
        sum += static_cast<float>(std::pow(network_output[i] - target[i], 2.0));
    }

    network_loss = sum / network_output.size();

    return network_loss;
}