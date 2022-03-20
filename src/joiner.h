#ifndef WICKED_CSV_JOINER_H
#define WICKED_CSV_JOINER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 32768

int get_col_pos(char* header_line, const char* col_name);
int get_col_cnt(char* header_line);
void fill_row(char* line, char* join_type, int col_cnt);
char* get_val(const char* line, int pos);
void remove_newline_char(char* line);
int join_line(char* left_line, char* right_path, int left_col_pos, int right_col_pos, char* join_type);
int join_header(char* left_header, char* right_header);
int join(char* left_path, char* right_path, char* col, char* join_type);

#endif //WICKED_CSV_JOINER_H
