#include <vector>
#include <random>

#define THRESHOLD_VALUE 0

class Hopfield {
    public:
        Hopfield(int size);

        void update_nodes_sequential();
        void update_node(int node_idx);
        void update_random_node();

        void set_state(std::vector<int> new_states);
    
    private:
        std::vector<int> m_nodes;
        std::vector<std::vector<double>> m_weights; 
        int m_size;   
};

Hopfield::Hopfield(int size) 
    : m_nodes(size, 1), m_weights(size, std::vector<double>(size, 0.0)), m_size(size) 
{
}

void Hopfield::update_nodes_sequential() {
    for (int node_idx = 0; node_idx < m_size; node_idx++) {
        update_node(node_idx);
    }
}

inline void Hopfield::update_node(int node_idx) {
    double weight_sum = 0;

    for (int neighbor_idx = 0; neighbor_idx < m_size; neighbor_idx++) {
        weight_sum += m_weights[node_idx][neighbor_idx] * m_nodes[neighbor_idx];
    }

    m_nodes[node_idx] = (weight_sum >= THRESHOLD_VALUE) ? 1 : -1;
}

void Hopfield::update_random_node() {
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution<> distribution(0, m_size-1);

    int node_idx = distribution(generator);
    update_node(node_idx);
}