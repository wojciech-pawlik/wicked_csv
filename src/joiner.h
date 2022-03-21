#ifndef WICKED_CSV_JOINER_H
#define WICKED_CSV_JOINER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 32768
<<<<<<< HEAD
int QUOTATION_COUNTER;
=======
>>>>>>> 50f151b1b924bb3ea0351047003e6f29d8ecc70e

int get_col_pos(char* header_line, const char* col_name);
int get_col_cnt(char* header_line);
void fill_row(char* line, char* join_type, int col_cnt);
<<<<<<< HEAD
char* get_line(int max_len, FILE *stream);
char* get_val(char* line, int pos);
=======
char* get_val(const char* line, int pos);
>>>>>>> 50f151b1b924bb3ea0351047003e6f29d8ecc70e
void remove_newline_char(char* line);
int join_line(char* left_line, char* right_path, int left_col_pos, int right_col_pos, char* join_type);
int join_header(char* left_header, char* right_header);
int join(char* left_path, char* right_path, char* col, char* join_type);

#endif //WICKED_CSV_JOINER_H
