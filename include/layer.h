#include <vector>
#include "neuron.h"

class Layer{
    public:
        Layer(int size, int position, int no_inputs);

        std::vector<Neuron> neurons;
        std::vector<float> inputs;
        std::vector<float> outputs;

        int position;

        std::vector<float> calculate_layer_outputs();

};