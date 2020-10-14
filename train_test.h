#ifndef CART_TRAIN_TEST_H
#define CART_TRAIN_TEST_H

#include <iostream>
#include "DecisionTree.h"
#include "utility.h"

template int read_txt_file<float>(std::string_view, std::vector<std::vector<float>>&, const char, const int, const int);

int test_decision_tree_train() {
    // small dataset test
    const std::vector<std::vector<float>> data{{2.771244718f, 1.784783929f, 0.f},
                                               {1.728571309f, 1.169761413f, 0.f},
                                               {3.678319846f, 2.81281357f, 0.f},
                                               {3.961043357f, 2.61995032f, 0.f},
                                               {2.999208922f, 2.209014212f, 0.f},
                                               {7.497545867f, 3.162953546f, 1.f},
                                               {9.00220326f, 3.339047188f, 1.f},
                                               {7.444542326f, 0.476683375f, 1.f},
                                               {10.12493903f, 3.234550982f, 1.f},
                                               {6.642287351f, 3.319983761f, 1.f}};
    const std::vector<float> classes{0.f, 1.f};
    ANN::DecisionTree<float> dt;
    dt.init(data, classes);
    dt.set_max_depth(3);
    dt.set_min_size(1);
    dt.train();

    std::string_view model_name = "/home/leanne/CLionProjects/CART/saved_model/decision_tree0.model";
    dt.save_model(model_name);
    ANN::DecisionTree<float> dt2;
    dt2.load_model(model_name);
    // fix it!
    const std::vector<std::vector<float>> test{{0.6f, 1.9f, 0.f}, {9.7f, 4.3f, 1.f}};
    for (const auto &row : test) {
        float ret = dt2.predict(row);
        fprintf(stdout, "predict result: %.1f, actural value: %.1f\n", ret, row[2]);
    }

    //    // banknote authentication dataset
    //    std::string_view file_name = "/home/leanne/CLionProjects/CART/banknote_authentication.txt";
    //
    //    std::vector<std::vector<float>> data1;
    //    int ret = read_txt_file<float>(file_name, data1, ',', 1372, 5);
    //    if (ret != 0) {
    //        fprintf(stderr, "parse txt file fail: %s\n", std::string(file_name).c_str());
    //        return -1;
    //    }
    //
    //    //fprintf(stdout, "data size: rows: %d\n", data.size());
    //
    //    const std::vector<float> classes1{ 0.f, 1.f };
    //    ANN::DecisionTree<float> dt;
    //    dt.init(data1, classes1);
    //    dt.set_max_depth(6);
    //    dt.set_min_size(10);
    //    dt.train();
    //
    //    std::string_view model_name1 = "/home/leanne/CLionProjects/CART/saved_model/decision_tree.model";
    //    dt.save_model(model_name1);

    return 0;
}

int test_decision_tree_predict()
{
    std::string_view model_name = "/home/leanne/CLionProjects/CART/saved_model/decision_tree.model";
    ANN::DecisionTree<float> dt;
    dt.load_model(model_name);
    int max_depth = dt.get_max_depth();
    int min_size = dt.get_min_size();

    fprintf(stdout, "max_depth: %d, min_size: %d\n", max_depth, min_size);

    std::vector<std::vector<float>> test {{-2.5526,-7.3625,6.9255,-0.66811,1},
                                          {-4.5531,-12.5854,15.4417,-1.4983,1},
                                          {4.0948,-2.9674,2.3689,0.75429,0},
                                          {-1.0401,9.3987,0.85998,-5.3336,0},
                                          {1.0637,3.6957,-4.1594,-1.9379,1}};
    for (const auto& row : test) {
        float ret_predict = dt.predict(row);
        std::cout << "predicted result: " << ret_predict << ", actual value " << row[4] << "\n";
    }


    return 0;
}

#endif //CART_TRAIN_TEST_H
