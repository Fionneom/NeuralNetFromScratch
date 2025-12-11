#pragma once

#include <vector>
#include "neuron.h"

class Layer{
    public:
        Layer(int size, int no_inputs, bool last_layer);

        std::vector<Neuron> neurons_;
        std::vector<double> inputs_;
        std::vector<double> outputs_;

        bool last_layer_;

        std::vector<double> calculate_layer_outputs();
        void calculate_deltas(std::vector<double> target, std::vector<double> network_output);
        void update_weights();

        void accumulate_gradients();
        void apply_batch_update(int batch_size);
};