#include "neuron.h"
#include "layer.h"
#include <iostream>
#include <algorithm>

Neuron::Neuron(int no_inputs, bool last_layer){

    // In neuron.cpp, inside Neuron constructor
    // The correct scale factor for Leaky ReLU / ReLU (He Initialization)
    double limit = std::sqrt(6.0 / no_inputs); 

    for(int i = 0; i < no_inputs; i++){
        // Scale the random number to the range [-limit, +limit]
        double random_weight = ((double)rand() / RAND_MAX) * 2.0 * limit - limit;
        weights_.push_back(random_weight);
    }
    // bias initialization should be scaled too (see #2)            

    bias_ = ((double) rand() / RAND_MAX) * 2.0 * limit - limit;

    weight_gradients_sum_.resize(no_inputs, 0.0);
};

double Neuron::calculate_neuron_output(){
    double sum = 0;
    for(int i = 0; i < inputs_.size(); i++){
        sum += inputs_[i] * weights_[i];
    }
    sum += bias_;

    // Leaky Relu Activation
    if(!last_layer_){
        if(sum < 0.0){
            sum = sum * LEAKY_RELU_ALPHA;
        }
    }

    output_ = sum;
    return sum;
}

void Neuron::calculate_signal_error(double target, double output_softmax, int no_outputs){
    // Using Cross-enthropy

    // double azi = get_azi();
    // double DLdyi = (output_softmax - target);

    // signal_error_ = DLdyi * azi;
    signal_error_ = (output_softmax - target);
}

void Neuron::calculate_signal_error(int neuron_position){
    double azi = get_azi();

    double sum = 0.0;
    for(int i = 0; i < next_layer_ptr_->neurons_.size(); i++){
        auto& n = next_layer_ptr_->neurons_[i];
        sum += n.signal_error_ * n.weights_[neuron_position];
    }

    signal_error_ = sum * azi;
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

// Old original function for sgd
void Neuron::update_weights(){
    for(int i = 0; i < weights_.size(); i++){
        double grad = signal_error_ * inputs_[i];
        // grad = std::clamp(grad, -1.0, 1.0);
        weights_[i] -= LEARNING_RATE * grad;

    }
    bias_ = bias_ - (LEARNING_RATE * signal_error_);
}

// Modified in neuron.cpp (RENAME THIS FUNCTION TO accumulate_gradients)
void Neuron::accumulate_gradients(){
    for(int i = 0; i < weights_.size(); i++){
        double grad = signal_error_ * inputs_[i];

        // Limit the gradient before accumulation
        grad = std::clamp(grad, -1.0, 1.0); 

        // SUM the change needed (instead of applying it)
        weight_gradients_sum_[i] += grad; 
    }
    bias_gradient_sum_ += std::clamp(signal_error_, -1.0, 1.0);
}

// New function in neuron.cpp
void Neuron::apply_batch_update(int batch_size){
    for(int i = 0; i < weights_.size(); i++){
        // Apply the average change
        weights_[i] -= LEARNING_RATE * (weight_gradients_sum_[i] / batch_size);

        // RESET the sum for the next batch
        weight_gradients_sum_[i] = 0.0; 
    }
    bias_ -= LEARNING_RATE * (bias_gradient_sum_ / batch_size);
    bias_gradient_sum_ = 0.0; // RESET
}