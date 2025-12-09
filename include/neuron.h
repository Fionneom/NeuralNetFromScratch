#include <vector>

class Neuron{
    public:
        Neuron(int no_inputs, bool last_layer);

        static constexpr double LEAKY_RELU_ALPHA = 0.1;
        static constexpr double LEARNING_RATE = 0.001;

        double signal_error;

        bool last_layer_;
        double bias_;
        std::vector<double> weights_;
        std::vector<double> inputs_;

        double calculate_neuron_output();

        void calculate_signal_error();
};