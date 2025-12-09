#include <vector>
#include "neuron.h"

class Layer{
    public:
        Layer(int size, int no_inputs);

        std::vector<Neuron> neurons;
        std::vector<float> inputs;
        std::vector<float> outputs;

        std::vector<float> calculate_layer_outputs();

};