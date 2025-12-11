#include "layer.h"
#include <iostream>

Layer::Layer(int size, int no_inputs, bool last_layer){
    last_layer_ = last_layer;
    for(int i = 0; i < size; i++){
        neurons_.push_back(Neuron(no_inputs, last_layer));
    }
}

std::vector<double> Layer::calculate_layer_outputs(){
    outputs_.clear();
    
    int c = 0;
    for(auto& n : neurons_){
        n.inputs_ = inputs_;
        double output = n.calculate_neuron_output();
        outputs_.push_back(output);
        c++;
    }
    return outputs_;
}

void Layer::calculate_deltas(std::vector<double> target, std::vector<double> network_output){
    if(last_layer_){
        for(int i = 0; i < neurons_.size(); i++){
            neurons_[i].calculate_signal_error(target[i], network_output[i], static_cast<int>(target.size()));
        }
    }

    else{
        for(int i = 0; i < neurons_.size(); i++){
            neurons_[i].calculate_signal_error(i);
        }
    }
}

void Layer::update_weights(){
    for(Neuron& n : neurons_){
        n.update_weights();
    }
}

void Layer::accumulate_gradients(){
    for(int i = 0; i < neurons_.size(); i++){
        neurons_[i].accumulate_gradients();
    }
    // std::cout << layers_[0].neurons_[0].weights_[0] << std::endl;
}

void Layer::apply_batch_update(int batch_size){
    for(int i = 0; i < neurons_.size(); i++){
        neurons_[i].apply_batch_update(batch_size);
    }
    // std::cout << layers_[0].neurons_[0].weights_[0] << std::endl;
}