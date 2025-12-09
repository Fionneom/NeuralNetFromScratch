#include <vector>
#include "layer.h"

class Network{
    public:
        Network(std::vector<int> network_structure, int no_inputs);

        std::vector<Layer> layers_;
        int no_inputs_;

        std::vector<float> network_output_;

        float network_loss_;

        void set_input(std::vector<float> network_input);
        std::vector<float> calculate_network_output();
        float calculate_loss(std::vector<float> target);
};