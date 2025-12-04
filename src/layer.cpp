#include "layer.h"
#include <iostream>

Layer::Layer(int size, int p, int no_inputs){
    for(int i = 0; i < size; i++){
        neurons.push_back(Neuron(p, no_inputs));
    }
    position = p;
}

std::vector<float> Layer::calculate_layer_outputs(){
    outputs.clear();
    
    int c = 0;
    for(auto n : neurons){
        n.inputs = inputs;
        float output = n.calculate_neuron_output();
        outputs.push_back(output);
        c++;
    }
    return outputs;
}