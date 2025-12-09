#include "neuron.h"

Neuron::Neuron(int no_inputs, bool last_layer){
    // Initialisation
    for(int i = 0; i < no_inputs; i++){
        double random_weight = ((double) rand() / RAND_MAX) * 2.0f - 1.0f;
        weights_.push_back(random_weight);
    }
    bias_ = ((double) rand() / RAND_MAX) * 2.0f - 1.0f;
};

double Neuron::calculate_neuron_output(){
    double sum = 0;
    for(int i = 0; i < inputs_.size(); i++){
        sum += inputs_[i] * weights_[i];
    }
    sum += bias_;

    // Leaky Relu Activation
    if(sum < 0.0){
        sum = sum * LEAKY_RELU_ALPHA;
    }

    output_ = sum;
    return sum;
}

void Neuron::calculate_signal_error(double target, int no_outputs){
    // Delta = DL/dyi * a'(zi)

    double azi = get_azi();
    double DLdyi = (2.0 / no_outputs) * (output_ - target);

    signal_error_ = DLdyi * azi;
}

double Neuron::get_azi(){
    double azi;
    if(output_ >= 0){
        azi = 1.0;
    }
    else{
        azi = LEAKY_RELU_ALPHA;
    }

    return azi;
}