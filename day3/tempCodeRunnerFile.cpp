#include <iostream>
#include <fstream>
#include <string>

bool is_symbol_above(std::string row_above, std::string current_row, int left_pos, int right_pos) {
    bool symbol_above = false;
    int i;
    if (left_pos > 0) {
        i = left_pos-1;
    }
    else {
        i = 0;
    }

    for (i; i < row_above.length() && i <= right_pos && !symbol_above; i++) {
        if (! (row_above[i] == '.' || ('0' <= row_above[i] && row_above[i] <= '9' ))) {
            symbol_above = true;
        }
    }
    return symbol_above;
}

bool is_symbol_beside(std::string current_row, int left_pos, int right_pos) {
    bool symbol_left = false, symbol_right = false;

    if (left_pos > 0) {
        if ( !(current_row[left_pos-1] == '.' || ('0' <= current_row[left_pos-1] && current_row[left_pos-1] <= '9'))) {
            symbol_left = true;
        }
    }

    if (right_pos < current_row.length()) {
        if ( !(current_row[right_pos] == '.' || ('0' <= current_row[right_pos] && current_row[right_pos] <= '9'))) {
            symbol_right = true;
        }
    }

    return (symbol_left || symbol_right);
}

bool is_symbol_below(std::string current_row, std::string row_below, int left_pos, int right_pos) {
    bool symbol_below = false;
    int i;
    if (left_pos > 0) {
        i = left_pos-1;
    }
    else {
        i = 0;
    }

    for (i; i < row_below.length() && i <= right_pos && !symbol_below; i++) {
        if (! (row_below[i] == '.' || ('0' <= row_below[i] && row_below[i] <= '9' ))) {
            symbol_below = true;
        }
    }
    return symbol_below;
}


int process_top_row(std::string top_row, std::string middle_row) {
    int total = 0;

    int pos = 0;

    int left_pos = 0; int right_pos = 0;
    while (pos < top_row.length()) {
        while (pos < top_row.length() && (top_row[pos] < '0' || top_row[pos] > '9')) {
            pos++;
        }
        if (pos < top_row.length()) {
            left_pos = pos;
            int val = 0;
            while (pos < top_row.length() && ('0' <= top_row[pos] && top_row[pos] <= '9')) {
                val = (val * 10) + (top_row[pos] - '0');
                pos++;
            }
            right_pos = pos;
            if (is_symbol_beside(top_row, left_pos, right_pos) || is_symbol_below(top_row, middle_row, left_pos, right_pos)) {
                total += val;
            }
        }
    }

    return total;
}

int process_middle_row(std::string top_row, std::string middle_row, std::string bottom_row) {
    int total = 0;

    int pos = 0;

    int left_pos = 0; int right_pos = 0;
    while (pos < middle_row.length()) {
        while (pos < middle_row.length() && (middle_row[pos] < '0' || middle_row[pos] > '9')) {
            pos++;
        }
        if (pos < middle_row.length()) {
            left_pos = pos;
            int val = 0;
            while (pos < middle_row.length() && ('0' <= middle_row[pos] && middle_row[pos] <= '9')){
                val = (val * 10) + (middle_row[pos] - '0');
                pos++;
            }
            right_pos = pos;
            if (is_symbol_beside(middle_row, left_pos, right_pos) || is_symbol_below(middle_row, bottom_row, left_pos, right_pos) || is_symbol_above(top_row, middle_row, left_pos, right_pos)) {
                total += val;
            }
        }
    }

    return total;
}

int process_bottom_row(std::string middle_row, std::string bottom_row) {
    int total = 0;

    int pos = 0;

    int left_pos = 0; int right_pos = 0;
    while (pos < bottom_row.length()) {
        while (pos < bottom_row.length() && (bottom_row[pos] < '0' || bottom_row[pos] > '9')) {
            pos++;
        }
        if (pos < bottom_row.length()) {
            left_pos = pos;
            int val = 0;
            while (pos < bottom_row.length() && ('0' <= bottom_row[pos] && bottom_row[pos] <= '9')){
                val = val * 10 + (bottom_row[pos] - '0');
                pos++;
            }
            right_pos = pos;
            if (is_symbol_beside(bottom_row, left_pos, right_pos) || is_symbol_above(middle_row, bottom_row, left_pos, right_pos)) {
                total += val;
            }
        }
    }

    return total;
}

bool is_num(std::string current_row, int pos) {
    return ('0' <= current_row[pos] && current_row[pos] <= '9');
}

int get_num_left(std::string current_row, int pos) {
    int val = 0;
    int i = pos;

    int left;

    while (i > 0 && is_num(current_row, i)) {
        i--;
    }

    if(!is_num(current_row, i)) {
        i++;
    }

    left = i;

    while (i <= pos) {
        val = (val * 10) + (current_row[i] - '0');
        i++;
    }

    // std::cout << current_row << ", in get_num_Left; left = " << left << ", right = " << pos << ", val = " << val << '\n';

    return val;
}

int get_num_right(std::string current_row, int pos) {
    int val = 0;
    int i = pos;

    while (i < current_row.length() && is_num(current_row, i)) {
        val = (val * 10) + (current_row[i] - '0');
        i++;
    }

    //std::cout << current_row << ", in get_num_right; left = " << pos << ", right = " << i << ", val = " << val << '\n';

    return val;
}

int get_num_middle(std::string current_row, int pos) {
    int val = 0;

    int i = pos;

    int left;
    while (i > 0 && is_num(current_row, i)) {
        i--;
    }

    if(!is_num(current_row, i)) {
        i++;
    }
    left = i;

    while (i <= current_row.length() && is_num(current_row, i)) {
        val = (val * 10) + (current_row[i] - '0');
        i++;
    }

    //std::cout << current_row << ", in get_num_middle; left = " << left << ", right = " << i << ", val = " << val << '\n';

    return val;
}

int gear_ratio_top_row(std::string top_row, std::string middle_row) {
    int gear_ratio=0;

    int first_val = 0;
    int second_val = 0;

    bool vals_found = false;

    for (int i=0; i < top_row.length(); i++) {
        /*/*   Case 17:
         *     ...
         *     1*2
         *     ...
         */

        if (!vals_found && i > 0) {
            if (is_num(top_row, i-1) && is_num(top_row, i+1)) {
                first_val = get_num_left(top_row, i-1);
                second_val = get_num_right(top_row, i+1);
                vals_found = true;
            }

        /*   Case 18:
         *     ...
         *     1*.
         *     2..
         */

            else if (is_num(top_row, i-1) && is_num(middle_row, i-1)) {
                first_val = get_num_left(top_row, i-1);
                second_val = get_num_middle(middle_row, i-1);
                vals_found = true;
            }

         /*
         *   Case 19:
         *     ...
         *     1*.
         *     .2.
         */

            else if (is_num(top_row, i-1) && is_num(middle_row, i)) {
                first_val = get_num_left(top_row, i-1);
                second_val = get_num_right(middle_row, i);
                vals_found = true;
            }
        }

        if (!vals_found && i > 0 && i < top_row.length()-1) {


        /*   Case 20:
         *     ...
         *     1*.
         *     ..2
         */
            if (is_num(top_row, i-1) && is_num(middle_row, i+1)) {
                first_val = get_num_left(top_row, i-1);
                second_val = get_num_right(middle_row, i+1);
                vals_found = true;
            }


         /*   Case 21:
         *     ...
         *     .*1
         *     2..
         */
            else if (is_num(top_row, i+1) && is_num(middle_row, i-1)) {
                first_val = get_num_right(top_row, i+1);
                second_val = get_num_middle(middle_row, i-1);
                vals_found = true;
            }
        }

         /*   Case 22:
         *     ...
         *     .*1
         *     .2.
         */
        if (!vals_found && i < top_row.length()-1) {
            if (is_num(top_row, i+1) && is_num(middle_row, i)) {
                first_val = get_num_right(top_row, i+1);
                second_val = get_num_right(top_row, i);
                vals_found = true;
            }

         /*   Case 23:
         *     ...
         *     .*1
         *     ..2
         */
            else if (is_num(top_row, i+1) && is_num(middle_row, i+1)) {
                first_val = get_num_right(top_row, i+1);
                second_val = get_num_right(top_row, i+1);
                vals_found = true;
            }
        }

         /*   Case 24:
         *     ...
         *     .*.
         *     1.2
         *
         */
        if (!vals_found && i > 0 && i < top_row.length()-1) {
            if (is_num(middle_row, i-1) && !is_num(middle_row, i) && is_num(middle_row, i+1)) {
                first_val = get_num_left(middle_row, i-1);
                second_val = get_num_right(middle_row, i+1);
                vals_found = true;
            }
        }
    }

    return first_val * second_val;
}

int gear_ratio_middle_row(std::string top_row, std::string middle_row, std::string bottom_row) {
    int gear_ratio=0;

    for (int i=0; i < top_row.length(); i++) {
        if (middle_row[i] == '*') {
            int first_val = 0;
            int second_val = 0;

            bool vals_found = false;

            // hande cases where numbers are to the left and to the right of the gear symbol '*'
            if (i > 0 && i < top_row.length() - 1) {
                /*
                *   Case 1:
                *     1.2
                *     .*.
                *     ...
                */
                if (is_num(top_row, i-1) && !is_num(top_row, i) && is_num(top_row, i+1)) {
                    first_val = get_num_left(top_row, i-1);
                    second_val = get_num_right(top_row, i+1);
                    vals_found = true;
                }

                /*   Case 2:
                *     1..
                *     .*2
                *     ...
                */
                else if (is_num(top_row, i-1) && is_num(middle_row, i+1)) {
                    first_val = get_num_middle(top_row, i-1);
                    second_val = get_num_right(middle_row, i+1);
                    vals_found = true;
                }

                /*   Case 6:
                *     1..
                *     .*.
                *     ..2
                */
                else if (is_num(top_row, i-1) && is_num(bottom_row, i+1)) {
                    first_val = get_num_middle(top_row, i-1);
                    second_val = get_num_middle(bottom_row, i+1);
                    vals_found = true;
                }

                /*   Case 12:
                *     ..1
                *     2*.
                *     ...
                */
                else if (is_num(top_row, i+1) && is_num(middle_row, i-1)) {
                    first_val = get_num_middle(top_row, i+1);
                    second_val = get_num_left(middle_row, i-1);
                    vals_found = true;
                }

                /*   Case 14:
                *     ..1
                *     .*.
                *     2..
                */
                else if (is_num(top_row, i+1) && is_num(bottom_row, i-1)) {
                    first_val = get_num_middle(top_row, i+1);
                    second_val = get_num_middle(bottom_row, i-1);
                    vals_found = true;
                }

                /*   Case 17:
                *     ...
                *     1*2
                *     ...
                */
                else if (is_num(middle_row, i-1) && is_num(middle_row, i+1)) {
                    first_val = get_num_left(middle_row, i-1);
                    second_val = get_num_right(middle_row, i+1);
                    vals_found = true;
                }

                /*   Case 20:
                *     ...
                *     1*.
                *     ..2
                */
                else if (is_num(middle_row, i-1) && is_num(bottom_row, i+1)) {
                    first_val = get_num_left(middle_row, i-1);
                    second_val = get_num_right(bottom_row, i+1);
                    vals_found = true;
                }

                /*   Case 21:
                *     ...
                *     .*1
                *     2..
                */
                else if (is_num(middle_row, i+1) && is_num(bottom_row, i-1)) {
                    first_val = get_num_right(middle_row, i+1);
                    second_val = get_num_middle(bottom_row, i-1);
                    vals_found = true;
                }

                /*   Case 24:
                *     ...
                *     .*.
                *     1.2
                */
                else if (is_num(bottom_row, i-1) && !is_num(bottom_row, i) && is_num(bottom_row, i+1)) {
                    first_val = get_num_left(bottom_row, i-1);
                    second_val = get_num_right(bottom_row, i+1);
                    vals_found = true;
                }
            }

            // handle cases where there are numbers to the left, and possibly in the same column as, the gear symbol '*'
            if (!vals_found && i > 0) {
                /*   Case 3:
                *     1..
                *     2*.
                *     ...
                */
                if (is_num(top_row, i-1) && is_num(middle_row, i-1)) {
                    first_val = get_num_middle(top_row, i-1);
                    second_val = get_num_left(middle_row, i-1);
                    vals_found = true;
                }

                /*   Case 4:
                *     1..
                *     .*.
                *     2..
                */
                else if (is_num(top_row, i-1) && is_num(bottom_row, i-1)) {
                    first_val = get_num_middle(top_row, i-1);
                    second_val = get_num_middle(bottom_row, i-1);
                    vals_found = true;
                }

                /*   Case 5:
                *     1..
                *     .*.
                *     .2.
                */
                else if (is_num(top_row, i-1) && is_num(bottom_row, i)) {
                    first_val = get_num_middle(top_row, i-1);
                    second_val = get_num_middle(bottom_row, i);
                    vals_found = true;
                }


                /*   Case 7:
                *     .1.
                *     2*.
                *     ...
                */
                else if (is_num(top_row, i) && is_num(middle_row, i-1)) {
                    first_val = get_num_right(top_row, i);
                    second_val = get_num_left(middle_row, i-1);
                    vals_found = true;
                }

                /*   Case 9:
                *     .1.
                *     .*.
                *     2..
                */
                else if (is_num(top_row, i) && is_num(bottom_row, i-1)) {
                    first_val = get_num_right(top_row, i);
                    second_val = get_num_left(bottom_row, i-1);
                    vals_found = true;
                }

                /*   Case 18:
                *     ...
                *     1*.
                *     2..
                */
                else if (is_num(middle_row, i-1) && is_num(bottom_row, i-1)) {
                    first_val = get_num_left(middle_row, i-1);
                    second_val = get_num_middle(bottom_row, i-1);
                    vals_found = true;
                }

                /*
                *   Case 19:
                *     ...
                *     1*.
                *     .2.
                */
                else if (is_num(middle_row, i-1) && is_num(bottom_row, i)) {
                    first_val = get_num_left(middle_row, i-1);
                    second_val = get_num_right(bottom_row, i);
                    vals_found = true;
                }
            }

            // handle cases where there are numbers to the right of, and possibly in the same column as, the gear symbol '*'
            if (!vals_found && i < top_row.length() - 1) {

                /*   Case 8:
                *     .1.
                *     .*2
                *     ...
                */
                if (is_num(top_row, i) && is_num(middle_row, i+1)) {
                    first_val = get_num_middle(top_row, i);
                    second_val = get_num_right(middle_row, i+1);
                    vals_found = true;
                }

                /*   Case 11:
                *     .1.
                *     .*.
                *     ..2
                */
                else if (is_num(top_row, i) && is_num(bottom_row, i+1)) {
                    first_val = get_num_middle(top_row, i);
                    second_val = get_num_middle(bottom_row, i+1);
                    vals_found = true;
                }

                /*   Case 13:
                *     ..1
                *     .*2
                *     ...
                */
                else if (is_num(top_row, i+1) && is_num(middle_row, i+1)) {
                    first_val = get_num_right(top_row, i+1);
                    second_val = get_num_right(middle_row, i+1);
                    vals_found = true;
                }

                /*   Case 15:
                *     ..1
                *     .*.
                *     .2.
                */
                else if (is_num(top_row, i+1) && is_num(bottom_row, i)) {
                    first_val = get_num_middle(top_row, i+1);
                    second_val = get_num_middle(bottom_row, i);
                    vals_found = true;
                }

                /*   Case 16:
                *     ..1
                *     .*.
                *     ..2
                */
                else if (is_num(top_row, i+1) && is_num(bottom_row, i+1)) {
                    first_val = get_num_middle(top_row, i+1);
                    second_val = get_num_right(bottom_row, i+1);
                    vals_found = true;
                }

                /*   Case 22:
                *     ...
                *     .*1
                *     .2.
                */
                else if (is_num(middle_row, i+1) && is_num(bottom_row, i)) {
                    first_val = get_num_right(middle_row, i+1);
                    second_val = get_num_middle(bottom_row, i);
                    vals_found = true;
                }

                /*   Case 23:
                *     ...
                *     .*1
                *     ..2
                */
                else if (is_num(middle_row, i+1) && is_num(bottom_row, i+1)) {
                    first_val = get_num_right(middle_row, i+1);
                    second_val = get_num_right(bottom_row, i+1);
                    vals_found = true;
                }

            }

            //handle edge case of single values above and below the gear symbol '*'
            if (!vals_found) {

                /*   Case 10:
                *     .1.
                *     .*.
                *     .2.
                */
                if (is_num(top_row, i) && is_num(bottom_row, i)) {
                    first_val = get_num_middle(top_row, i);
                    second_val = get_num_middle(bottom_row, i);
                    vals_found = true;
                }

            }

            if (vals_found) {
                gear_ratio += first_val * second_val;
            }
        }
    }
    return gear_ratio;
}


int main(int argc, char **argv) {
    int total = 0;
    int total_gear_ratio = 0;

    std::fstream input_file;
    //input_file.open("input.txt");
    input_file.open("day3.txt");


    std::string top_row, middle_row, bottom_row;

    std::getline(input_file, top_row);
    std::getline(input_file, middle_row);

    total += process_top_row(top_row, middle_row);

    while (std::getline(input_file, bottom_row)) {
        total += process_middle_row(top_row, middle_row, bottom_row);
        int row_gear_ratio = gear_ratio_middle_row(top_row, middle_row, bottom_row);
        total_gear_ratio += row_gear_ratio;
        top_row = middle_row;
        middle_row = bottom_row;
    }

    total += process_bottom_row(top_row, middle_row);

    std::cout << "Total = " << total << '\n';

    std::cout << "Total gear ratio = " << total_gear_ratio << '\n';
    return 0;
}