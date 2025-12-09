#include "network.h"
#include <iostream>
#include <cmath>

Network::Network(std::vector<int> network_structure, int no_inputs){
    no_inputs_ = no_inputs;

    for(int i = 0; i < network_structure.size(); i++){
        bool last_layer = false;
        if(i == network_structure.size() - 1){
            last_layer = true;
        }

        if(i == 0){
            layers_.push_back(Layer(network_structure[i], no_inputs, last_layer));
        }
        else{
            layers_.push_back(Layer(network_structure[i], network_structure[i - 1], last_layer));
        }
    }

}

void Network::set_input(std::vector<double> network_input){
    if(network_input.size() == no_inputs_){
        layers_[0].inputs_ = network_input;
    }
    else{
        std::cout << "Incorrect Number of Inputs";
        exit(1);
    }
}

std::vector<double> Network::calculate_network_output(){
    for(int i = 0; i < layers_.size(); i++){
        std::vector<double> out = layers_[i].calculate_layer_outputs();

        if(i < layers_.size() - 1){
            layers_[i + 1].inputs_ = out;
        }
        else{
            //softmax
            double denom = 0.0;
            for(double v : out){
                denom += std::exp(v);
            }

            std::vector<double> softmax;
            for(double v : out){
                double probability = std::exp(v) / denom;
                softmax.push_back(probability);
            }
            
            network_output_ = softmax;
            return softmax;
        }
    }
}

double Network::calculate_loss(std::vector<double> target){

    double sum = 0;
    for(int i = 0; i < network_output_.size(); i++){
        sum += std::pow(network_output_[i] - target[i], 2.0);
    }

    network_loss_ = sum / network_output_.size();

    return network_loss_;
}

void Network::calculate_deltas(std::vector<double> target){
    for(int i = layers_.size() - 1; i >= 0; i--){
        layers_[i].calculate_deltas(target);
    }
}