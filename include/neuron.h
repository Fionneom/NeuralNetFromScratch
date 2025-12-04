#include <vector>

class Neuron{
    public:
        Neuron(int layer_no, int no_inputs);

        float leaky_relu_alpha = 0.1;

        int layer;
        float bias;
        std::vector<float> weights;
        std::vector<float> inputs;

        float calculate_neuron_output();
};