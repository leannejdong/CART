#include <iostream>
#include "train_test.h"
#include "DecisionTree.h"
int main() {
    int ret = test_decision_tree_train();

    if (ret == 0) fprintf(stdout, "========== test success ==========\n");
    else
        fprintf(stderr, "########## test fail ##########\n");

    //    int ret1 = test_decision_tree_predict();
    //
    //    if (ret1 == 0) fprintf(stdout, "========== test success ==========\n");
    //    else
    //        fprintf(stderr, "########## test fail ##########\n");

    return 0;
}
