#include <vector>

class Neuron{
    public:
        Neuron(int no_inputs, bool _last_layer);

        float leaky_relu_alpha = 0.1;
        float learning_rate = 0.001;
        float signal_error;

        bool last_layer;
        float bias;
        std::vector<float> weights;
        std::vector<float> inputs;

        float calculate_neuron_output();

        void calculate_signal_error();
};