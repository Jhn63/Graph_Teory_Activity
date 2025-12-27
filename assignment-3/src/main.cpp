#include <iostream>
#include <iomanip>

#include "../include/Karger.h"
#include "../include/IO.h"
#include "../include/Naive.h"

#define N_EXEC 1000

int main() {
    IO io;
    auto m = io.load_data("test.txt");
    SuperGraph *s = new SuperGraph(m);

    Karger karger(s);
    Naive naive(m);

    int minimal_cut = 1;
    double prob_k = 0, prob_n;
    for (int niter = 10; prob_k < 0.98; niter+= 10) {

        int count_k = 0, count_n = 0;
        for (int i = 0; i < niter; i++) {

            auto k_cut = karger.min_cut();
            if (k_cut.size() == minimal_cut) {
                count_k++;
            }
            auto n_cut = naive.min_cut();
            if (n_cut.size() == minimal_cut) {
                count_n++;
            }
        }
        prob_k = static_cast<double>(count_k)/N_EXEC;
        prob_n = static_cast<double>(count_n)/N_EXEC;

        std::cout << "Karger: minimal cut founded " << count_k << " times ";
        std::cout << "of " << niter << " iterations, probability: " << prob_k;
        std::cout << std::endl << std::endl;

        std::cout << "Naive: minimal cut founded " << count_n << " times ";
        std::cout << "of " << niter << " iterations, probability: " << prob_n;
        std::cout << std::endl << std::endl;
    }

}
