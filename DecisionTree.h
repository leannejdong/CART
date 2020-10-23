#ifndef CART_DECISIONTREE_H
#define CART_DECISIONTREE_H

#include <algorithm>
#include <cassert>
#include <fstream>
#include <memory>
#include <set>
#include <sstream>
#include <tuple>
#include <typeinfo>
#include <vector>

namespace ANN {
    template<typename T>
    requires std::copy_constructible<T>//use a require cause
            class DecisionTree {       // CART (Classfification and Regression Trees
    public:
        DecisionTree() = default;
        int init(const std::vector<std::vector<T>> &data, const std::vector<T> &classes);
        void set_max_depth(int max_depth) { this->max_depth = max_depth; }
        int get_max_depth() const { return max_depth; }
        void set_min_size(int min_size) { this->min_size = min_size; }
        int get_min_size() const { return min_size; }
        void train();
        int save_model(std::string_view name) const;
        int load_model(std::string_view name);
        T predict(const std::vector<T>& data) const;
    protected:
        using dictionary = std::tuple<int, T, std::vector<std::vector<std::vector<T>>>>; // index of attribute, value of attribute, groups of data
        using row_element = std::tuple<int, int, T, T, T>; // flag, index, value, class_value_left, class_value_right
        struct binary_tree {
            dictionary dict;
            T class_value_left = (T) -1.f;
            T class_value_right = (T) -1.f;
            //            binary_tree* left = nullptr;
            //            binary_tree* right = nullptr;
            std::unique_ptr<binary_tree> left;
            std::unique_ptr<binary_tree> right;
        };

        // Calculate the Gini index for a split dataset
        T gini_index(const std::vector<std::vector<std::vector<T>>> &groups, const std::vector<T> &classes) const;
        // Split a dataset based on an attribute and an attribute value
        std::vector<std::vector<std::vector<T>>> test_split(int index, T value, const std::vector<std::vector<T>> &dataset) const;
        // Select the best split point for a dataset
        dictionary get_split(const std::vector<std::vector<T>> &dataset) const;
        // Create a terminal node value
        T to_terminal(const std::vector<std::vector<T>> &group) const;
        void split(binary_tree *node, int depth);// Build a decision tree
        void build_tree(const std::vector<std::vector<T>> &train);
        // Print a decision tree
        void print_tree(const binary_tree *node, int depth = 0) const;
        // Make a prediction with a decision tree
        T predict(binary_tree *node, const std::vector<T> &data) const;
        // calculate accuracy percentage
        double accuracy_metric() const;
        // void delete_tree();
        void delete_node(std::unique_ptr<binary_tree> node);
        void write_node(const binary_tree *node, std::ofstream &file) const;
        void node_to_row_element(binary_tree* node, std::vector<row_element>& rows, int pos) const;
        int height_of_tree(const binary_tree *node) const;
        void row_element_to_node(binary_tree *node, const std::vector<row_element> &rows, int n, int pos);

    private:
        std::vector<std::vector<T>> src_data;
        std::unique_ptr<binary_tree> tree;
        int samples_num = 0;
        int feature_length = 0;
        int classes_num = 0;
        int max_depth = 10;  // maximum tree depth
        size_t min_size = 10;// minimum node records
        int max_nodes = -1;
    };
}



#endif //CART_DECISIONTREE_H
