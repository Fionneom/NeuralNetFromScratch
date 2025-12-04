#include <vector>
#include "layer.h"

class Network{
    public:
        Network(std::vector<int> network_structure, int no_inputs);

        std::vector<Layer> layers;
        int no_network_inputs;

        std::vector<float> network_output;

        float network_loss;

        void set_input(std::vector<float> network_input);
        std::vector<float> calculate_network_output();
        float calculate_loss(std::vector<float> target);
};