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

    for(int i = 0; i < network_structure.size() - 1; i++){
        for(int j = 0; j < network_structure[i]; j++){
            layers_[i].neurons_[j].next_layer_ptr_ = &layers_[i + 1];
        }
    }
}

void Network::set_input(std::vector<double> network_input){
    if(network_input.size() == no_inputs_){
        for(double& i : network_input){
            i = i / 10.0;
        }
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
            double max_val = out[0];
            for(double v : out){
                if(v > max_val) max_val = v;
            }
            
            double denom = 0.0;
            for(double v : out){
                denom += std::exp(v - max_val);
            }

            std::vector<double> softmax;
            for(double v : out){
                double probability = std::exp(v - max_val) / denom;
                softmax.push_back(probability);
            }
            
            network_output_ = softmax;
            return softmax;
        }
    }
}

double Network::calculate_loss(std::vector<double> target){

    int index;
    for(int i = 0; i < target.size(); i++){
        if(target[i] == 1.0){
            index = i;
            break;
        }
    }

    network_loss_ = -std::log(network_output_[index] + 1e-9);

    return network_loss_;
}

void Network::calculate_deltas(std::vector<double> target){
    for(int i = layers_.size() - 1; i >= 0; i--){
        layers_[i].calculate_deltas(target, network_output_);
    }
}

// Not used anymore
void Network::update_weights(){
    for(int i = 0; i < layers_.size(); i++){
        layers_[i].update_weights();
    }
    // std::cout << layers_[0].neurons_[0].weights_[0] << std::endl;

}

void Network::accumulate_gradients(){
    for(int i = 0; i < layers_.size(); i++){
        layers_[i].accumulate_gradients();
    }
    // std::cout << layers_[0].neurons_[0].weights_[0] << std::endl;
}

void Network::apply_batch_update(int batch_size){
    for(int i = 0; i < layers_.size(); i++){
        layers_[i].apply_batch_update(batch_size);
    }
    // std::cout << layers_[0].neurons_[0].weights_[0] << std::endl;
}