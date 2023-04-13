#include "../../include/core/datatable.hpp"
#include "../../include/core/threadpool.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

int main() {
    /*
     * for now specific columns must be in the order they appear in the file
     * being read in
     */
    std::chrono::steady_clock::time_point start_time =
        std::chrono::steady_clock::now();
    mtpk::DataTable dt;

    // std::pair<std::vector<std::string>,
    // std::vector<std::vector<std::string>>>
    mtpk::DataTableStr result = dt.csv_read("../../data/forestfires.csv",
                                            {"month", "day", "temp", "wind"});
    // print result
    dt.display(result);

    // mtpk::DataTable dt_b;

    /* of type std::pair<std::vector<std::string>,
     *         std::vector<std::vector<std::string>>>
     */
    // mtpk::DataTableStr result_b = dt_b.csv_read("../../data/1m.csv",
    // {"Num"});

    /* of type std::pair<std::vector<int64_t>,
     *         std::vector<std::vector<int64_t>>>
     * convert DataTableStr to DataTableInt
     */
    // mtpk::DataTableInt result_int = dt_b.str_to_int(result_b);

    // dt_b.display(result_int);

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    std::cout << "Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    return 0;
}
