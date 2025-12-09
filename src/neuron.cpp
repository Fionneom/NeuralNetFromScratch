#include "neuron.h"

Neuron::Neuron(int no_inputs, bool last_layer){
    // Initialisation
    for(int i = 0; i < no_inputs; i++){
        float random_weight = ((float) rand() / RAND_MAX) * 2.0f - 1.0f;
        weights_.push_back(random_weight);
    }
    bias_ = ((float) rand() / RAND_MAX) * 2.0f - 1.0f;
};

float Neuron::calculate_neuron_output(){
    float sum = 0;
    for(int i = 0; i < inputs_.size(); i++){
        sum += inputs_[i] * weights_[i];
    }
    sum += bias_;

    // Leaky Relu Activation
    if(sum < 0.0){
        sum = sum * LEAKY_RELU_ALPHA;
    }

    return sum;
}

void Neuron::calculate_signal_error(){

}