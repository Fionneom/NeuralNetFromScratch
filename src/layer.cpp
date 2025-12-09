#include "layer.h"
#include <iostream>

Layer::Layer(int size, int no_inputs, bool last_layer){

    for(int i = 0; i < size; i++){
        neurons_.push_back(Neuron(no_inputs, last_layer));
    }
}

std::vector<float> Layer::calculate_layer_outputs(){
    outputs_.clear();
    
    int c = 0;
    for(auto n : neurons_){
        n.inputs_ = inputs_;
        float output = n.calculate_neuron_output();
        outputs_.push_back(output);
        c++;
    }
    return outputs_;
}