#include <vector>
#include "neuron.h"

class Layer{
    public:
        Layer(int size, int no_inputs, bool last_layer);

        std::vector<Neuron> neurons_;
        std::vector<float> inputs_;
        std::vector<float> outputs_;

        std::vector<float> calculate_layer_outputs();

};