#include <vector>
#include "layer.h"

class Network{
    public:
        Network(std::vector<int> network_structure, int no_inputs);

        std::vector<Layer> layers_;
        int no_inputs_;

        std::vector<double> network_output_;

        double network_loss_;

        void set_input(std::vector<double> network_input);
        std::vector<double> calculate_network_output();
        double calculate_loss(std::vector<double> target);
        void calculate_deltas(std::vector<double> target);
};