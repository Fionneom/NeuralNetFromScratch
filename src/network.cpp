#include "network.h"
#include <iostream>
#include <cmath>

Network::Network(std::vector<int> network_structure, int no_inputs){
    no_inputs_ = no_inputs;

    for(int i = 0; i < network_structure.size(); i++){
        if(i == 0){
            layers_.push_back(Layer(network_structure[i], i, no_inputs));
        }
        else{
            layers_.push_back(Layer(network_structure[i], i, network_structure[i - 1]));
        }
    }

}

void Network::set_input(std::vector<float> network_input){
    if(network_input.size() == no_inputs_){
        layers_[0].inputs_ = network_input;
    }
    else{
        std::cout << "Incorrect Number of Inputs";
        exit(1);
    }
}

std::vector<float> Network::calculate_network_output(){
    for(int i = 0; i < layers_.size(); i++){
        std::vector<float> out = layers_[i].calculate_layer_outputs();

        if(i < layers_.size() - 1){
            layers_[i + 1].inputs_ = out;
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
            
            network_output_ = softmax;
            return softmax;
        }
    }
}

float Network::calculate_loss(std::vector<float> target){

    float sum = 0;
    for(int i = 0; i < network_output_.size(); i++){
        sum += static_cast<float>(std::pow(network_output_[i] - target[i], 2.0));
    }

    network_loss_ = sum / network_output_.size();

    return network_loss_;
}