#include <vector>
#include "neuron.h"

class Layer{
    public:
        Layer(int size, int no_inputs, bool last_layer);

        std::vector<Neuron> neurons_;
        std::vector<double> inputs_;
        std::vector<double> outputs_;

        std::vector<double> calculate_layer_outputs();

};