#include "neuron.h"

Neuron::Neuron(int no_inputs){
    // Initialisation
    for(int i = 0; i < no_inputs; i++){
        float random_weight = ((float) rand() / RAND_MAX) * 2.0f - 1.0f;
        weights.push_back(random_weight);
    }
    bias = ((float) rand() / RAND_MAX) * 2.0f - 1.0f;
};

float Neuron::calculate_neuron_output(){
    float sum = 0;
    for(int i = 0; i < inputs.size(); i++){
        sum += inputs[i] * weights[i];
    }
    sum += bias;

    // Leaky Relu Activation
    if(sum < 0.0){
        sum = sum * leaky_relu_alpha;
    }

    return sum;
}

void Neuron::calculate_signal_error(){

}