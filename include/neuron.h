#include <vector>

class Neuron{
    public:
        Neuron(int no_inputs, bool last_layer);

        static constexpr float LEAKY_RELU_ALPHA = 0.1;
        static constexpr float LEARNING_RATE = 0.001;

        float signal_error;

        bool last_layer_;
        float bias_;
        std::vector<float> weights_;
        std::vector<float> inputs_;

        float calculate_neuron_output();

        void calculate_signal_error();
};