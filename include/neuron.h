#pragma once

#include <vector>

class Layer;

class Neuron{
    public:
        Neuron(int no_inputs, bool last_layer);

        static constexpr double LEAKY_RELU_ALPHA = 0.1;
        static constexpr double LEARNING_RATE = 0.001;

        double signal_error_;

        bool last_layer_;
        double bias_;
        std::vector<double> weights_;
        std::vector<double> inputs_;
        double output_;

        Layer* next_layer_ptr_;

        double calculate_neuron_output();

        // For output layer
        void calculate_signal_error(double target, int no_network_outputs);
        // For hidden layers
        void calculate_signal_error(int neuron_position);
        double get_azi();
        
};