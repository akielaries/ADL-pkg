/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <openGPMP/core/datatable.hpp>
#include <openGPMP/core/utils.hpp>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
// for memory mapping files
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/** Logger class object*/
static gpmp::core::Logger _log_;

// create method to create datatable from scratch? insert, drop, etc?

// TODO : optimize these methods, CSV reader using threads? loop unrolling?,
// etc? conversion functions to be quicker,
gpmp::core::DataTableStr
gpmp::core::DataTable::csv_read(std::string filename,
                                std::vector<std::string> columns) {

    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == -1) {
        // Handle file open error
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    char *file_data =
        static_cast<char *>(mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0));

    if (file_data == MAP_FAILED) {
        // Handle memory mapping error
        perror("Error mapping file to memory");
        close(fd);
        exit(EXIT_FAILURE);
    }

    std::stringstream file_stream(file_data);
    std::vector<std::vector<std::string>> data;
    std::string line;

    // Get the header line and parse the column names
    getline(file_stream, line);
    std::stringstream header(line);
    std::vector<std::string> header_cols;
    std::string columnName;

    while (getline(header, columnName, ',')) {
        header_cols.push_back(columnName);
    }

    // If no columns are specified, read in all columns
    if (columns.empty()) {
        columns = header_cols;
    }

    // Check if specified columns exist in the header
    for (const auto &column : columns) {
        if (std::find(header_cols.begin(), header_cols.end(), column) ==
            header_cols.end()) {
            // Handle column not found error
            perror(("Column: " + column + " not found").c_str());
            munmap(file_data, size);
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    // Read in the data rows
    while (getline(file_stream, line)) {
        std::vector<std::string> row;
        std::stringstream rowStream(line);
        std::string value;
        int columnIndex = 0;

        while (getline(rowStream, value, ',')) {
            // If column is specified, only read in specified columns
            if (std::find(columns.begin(),
                          columns.end(),
                          header_cols[columnIndex]) != columns.end()) {
                row.push_back(value);
            }

            columnIndex++;
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    // populate headers_ class variable
    headers_ = columns;
    // populate data_ class variable
    data_ = data;

    munmap(file_data, size);
    close(fd);

    return std::make_pair(headers_, data_);
}

// Extracts date/time information from given column
// TODO: add additional options for detecting/converting date/time columns
// to numeric formats
gpmp::core::DataTableStr
gpmp::core::DataTable::datetime(std::string column_name,
                                bool extract_year,
                                bool extract_month,
                                bool extract_time) {
    // Find the index of the specified column
    auto column_iter = std::find(headers_.begin(), headers_.end(), column_name);
    if (column_iter == headers_.end()) {
        _log_.log(ERROR, "Column: " + column_name + " node found");
        exit(EXIT_FAILURE);
    }
    int column_index = std::distance(headers_.begin(), column_iter);

    // Extract components from each row
    std::vector<std::string> new_headers = headers_;
    std::vector<std::vector<std::string>> new_data;

    // Iterate and populate the additional columns
    for (size_t row_index = 0; row_index < data_.size(); ++row_index) {
        std::vector<std::string> row = data_[row_index];
        // If column row is not found
        if (row.size() <= static_cast<size_t>(column_index)) {
            _log_.log(ERROR, "Column: " + column_name + " not found");

            exit(EXIT_FAILURE);
        }

        std::string timestamp = row[column_index];
        std::string year, month, time;

        // Create a new row with extracted components
        std::vector<std::string> new_row;

        // Extract year, month, and time components
        if (extract_year) {
            year = timestamp.substr(timestamp.find_last_of('/') + 1, 4);
            new_row.push_back(year);
        }
        if (extract_month) {
            month = timestamp.substr(0, timestamp.find_first_of('/'));
            new_row.push_back(month);
        }
        if (extract_time) {
            time = timestamp.substr(timestamp.find(' ') + 1);
            new_row.push_back(time);
        }

        // append original row data
        new_row.insert(new_row.end(), row.begin(), row.end());
        // add new rows
        new_data.push_back(new_row);
    }

    // Create new headers based on the extracted components
    if (extract_month)
        new_headers.insert(new_headers.begin(), "Month");
    if (extract_year)
        new_headers.insert(new_headers.begin(), "Year");
    if (extract_time)
        new_headers.insert(new_headers.begin(), "Time");

    // set class car data_ to hold rows/lines
    data_ = new_data;
    // set class var modified headers to new headers
    // new_headers_ = new_headers;
    headers_ = new_headers;

    return std::make_pair(new_headers, new_data);
}

// Sort specified columns, by default in asending order
void gpmp::core::DataTable::sort(const std::vector<std::string> &sort_columns,
                                 bool ascending) {
    // Extract the column indices to be sorted by from the original data
    std::vector<size_t> column_indices;
    for (const std::string &column : sort_columns) {
        auto iter = std::find(headers_.begin(), headers_.end(), column);
        if (iter != headers_.end()) {
            size_t index = std::distance(headers_.begin(), iter);
            column_indices.push_back(index);
        }
    }

    // Sort the data based on the specified columns
    std::stable_sort(data_.begin(),
                     data_.end(),
                     [&](const std::vector<std::string> &row1,
                         const std::vector<std::string> &row2) {
                         for (size_t index : column_indices) {
                             if (row1[index] != row2[index]) {
                                 if (ascending) {
                                     return row1[index] < row2[index];
                                 } else {
                                     return row1[index] > row2[index];
                                 }
                             }
                         }
                         // Rows are equal, nothing to sort
                         return false;
                     });
}

// Group rows by specific columns
std::vector<gpmp::core::DataTableStr>
gpmp::core::DataTable::group_by(std::vector<std::string> group_by_columns) {
    // Find the indices of the specified group by columns
    std::vector<int> group_by_indices;

    // Traverse group column names
    for (const std::string &column_name : group_by_columns) {
        std::cout << "Searching for column: " << column_name << std::endl;

        // Find start/end and match column name
        auto column_iter =
            std::find(headers_.begin(), headers_.end(), column_name);

        // If no columns
        if (column_iter == headers_.end()) {
            _log_.log(ERROR, "Column: " + column_name + " not found");
            exit(EXIT_FAILURE);
        }
        // column index set to distance from start of first col to nexter iter
        int column_index = std::distance(headers_.begin(), column_iter);
        // add column index to group
        group_by_indices.push_back(column_index);
    }

    // Group the data based on the specified columns using a vector
    std::vector<std::pair<std::vector<std::string>, gpmp::core::DataTableStr>>
        groups;

    // Traverse row/line data
    for (const std::vector<std::string> &row : data_) {
        // store group key for each row
        std::vector<std::string> group_key;
        // Fill group key from specified group column names
        for (int index : group_by_indices) {
            group_key.push_back(row[index]);
        }

        // Check if the group already exists
        auto group_iter = std::find_if(
            groups.begin(),
            groups.end(),
            [&group_key](const std::pair<std::vector<std::string>,
                                         gpmp::core::DataTableStr> &group) {
                return group.first == group_key;
            });
        // If the group DNE create a new one to add to groups vector
        if (group_iter == groups.end()) {
            // Create a new group
            groups.push_back(
                {group_key, gpmp::core::DataTableStr(headers_, {})});
            group_iter = groups.end() - 1;
        }
        // Add current row to group
        group_iter->second.second.push_back(row);
    }

    // Extract the grouped data into a vector
    std::vector<gpmp::core::DataTableStr> grouped_data;
    // Iterate over sorted groups to push onto result vector
    for (const auto &group : groups) {
        grouped_data.push_back(group.second);
    }

    // Return final DataTableStr type
    return grouped_data;
}

// Get first element of each created group
gpmp::core::DataTableStr gpmp::core::DataTable::first(
    const std::vector<gpmp::core::DataTableStr> &groups) const {
    if (groups.empty()) {
        // Handle the case when there are no groups
        return std::make_pair(std::vector<std::string>(),
                              std::vector<std::vector<std::string>>());
    }

    std::vector<std::vector<std::string>> first_rows;

    for (const gpmp::core::DataTableStr &group : groups) {
        if (!group.second.empty()) {
            first_rows.push_back(
                group.second[0]); // Get the first row of each group
        }
    }

    if (!first_rows.empty()) {
        // Assuming all groups have the same headers as the first group
        return std::make_pair(groups[0].first, first_rows);
    } else {
        // Handle the case when there are no first rows found.
        return std::make_pair(groups[0].first,
                              std::vector<std::vector<std::string>>());
    }
}

// Prints some basic information about a DataTable object

gpmp::core::DataTableInt
gpmp::core::DataTable::str_to_int(gpmp::core::DataTableStr src) {
    gpmp::core::DataTableInt dest;

    for (const auto &v : src.first) {
        // check if v contains only digits
        if (std::regex_match(v, std::regex("\\d+"))) {
            dest.first.push_back(std::stoi(v));
        }
    }
    for (const auto &vv : src.second) {
        std::vector<int64_t> new_vec;
        for (const auto &v : vv) {
            // check if v contains only digits
            if (std::regex_match(v, std::regex("\\d+"))) {
                new_vec.push_back(std::stoi(v));
            }
        }
        dest.second.push_back(new_vec);
    }
    return dest;
}

gpmp::core::DataTableDouble
gpmp::core::DataTable::str_to_double(gpmp::core::DataTableStr src) {
    gpmp::core::DataTableDouble dest;

    for (const auto &v : src.first) {
        if (std::regex_match(v, std::regex("[-+]?\\d*\\.?\\d+"))) {
            dest.first.push_back(std::stold(v));
        }
    }

    for (const auto &vv : src.second) {
        std::vector<long double> new_vec;
        for (const auto &v : vv) {
            if (std::regex_match(v, std::regex("[-+]?\\d*\\.?\\d+"))) {
                new_vec.push_back(std::stold(v));
            }
        }
        dest.second.push_back(new_vec);
    }

    return dest;
}
