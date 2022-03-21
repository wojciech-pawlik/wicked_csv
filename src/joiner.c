#include "joiner.h"

int get_col_pos(char* header_line, const char* col_name)
{
    int col_num = 0;
    char line[strlen(header_line)];
    strcpy(line, header_line);
    remove_newline_char(line);
    while(strcmp(get_val(line, col_num),"\0") != 0)
    {
        if(strcmp(get_val(line, col_num),col_name) == 0)
            return col_num;
        col_num++;
    }
    return -1;
}

int get_col_cnt(char* header_line)
{
    if(strlen(header_line) == 0)
        return 0;
    char line[strlen(header_line)];
    strcpy(line, header_line);
    int len = 0;
    while (strcmp(get_val(line, len), "\0") != 0)
        len++;
    return len;
}

void fill_row(char* line, char* join_type, int col_cnt)
{
    int i;
    int cmp = strcmp(join_type, "right");
    if(cmp != 0)
        printf("%s", line);
    for(i = 0; i < col_cnt; i++)
        printf(",");
    if(cmp == 0)
        printf("%s", line);
    printf("\n");
}

char* get_line(int max_len, FILE *stream)
{
    QUOTATION_COUNTER = 0;
    char next = '\0';
    size_t n = 0;
    char* line;
    line = (char*)malloc(MAX_LINE_LEN*sizeof(char));
    while((next = (char)fgetc(stream)) != EOF && n < max_len)
    {
        if(next == '\n' && QUOTATION_COUNTER == 0)
            return line;
        if(next == '\"')
            QUOTATION_COUNTER = (QUOTATION_COUNTER + 1) % 2;
        line[n++] = next;
    }
    line[n] = '\0';
    return line;
}

char* get_val(char* line, int pos)
{
    QUOTATION_COUNTER = 0;
    size_t n = 0;
    int cnt = 0;
    size_t start, end;
    char* val = (char*)malloc(MAX_LINE_LEN*sizeof(char));
    while(cnt < pos)
    {
        if(line[n] == '\0')
            return "\0";
        if(line[n] == ',' && QUOTATION_COUNTER == 0)
            cnt++;
        if(line[n] == '\"')
            QUOTATION_COUNTER = (QUOTATION_COUNTER + 1) % 2;
        n++;
    }
    start = n;
    while(!((line[n] == ',' || line[n] == '\n') && QUOTATION_COUNTER == 0) && line[n] != '\0')
    {
        if(line[n] == '\"')
            QUOTATION_COUNTER = (QUOTATION_COUNTER + 1) % 2;
        n++;
    }
    end = line[n] == '\n' ? n-1 : n;
    strncpy(val, line + start, (end-start));
    return val;
}

void remove_newline_char(char* line)
{
    size_t len = strlen(line)-1;
    if(len > 0 && line[len] == '\n')
        line[len] = '\0';
}

int join_line(char* left_line, char* right_path, int left_col_pos, int right_col_pos, char* join_type)
{
    int rows = 0;
    char* lval;
    char* right_line;
    remove_newline_char(left_line);
    lval = get_val(left_line, left_col_pos);

    FILE *file = fopen(right_path, "r");

    right_line = get_line(MAX_LINE_LEN, file);
    while(strcmp(right_line,"\0") != 0)
    {
        remove_newline_char(right_line);
        char* rval = get_val(right_line, right_col_pos);
        if (strcmp(lval, rval) == 0)
        {
            remove_newline_char(right_line);
            if(strcmp(join_type, "right") == 0)
                printf("%s,%s\n", right_line, left_line);
            else
                printf("%s,%s\n", left_line, right_line);
            rows++;
        }
        free(rval);
        right_line = get_line(MAX_LINE_LEN, file);
    }
    fclose(file);
    free(lval);
    return rows;
}

int join_header(char* left_header, char* right_header)
{
    remove_newline_char(left_header);
    remove_newline_char(right_header);
    printf("%s,%s\n", left_header, right_header);
    return 0;
}

int join(char* left_path, char* right_path, char* col, char* join_type)
{
    int left_len, right_len;
    int left_col_pos, right_col_pos;
    char* hl;
    char* hr;
    int rows;
    char* left_line;
    char* right_line;

    FILE *fl = fopen(left_path, "r");
    FILE *fr = fopen(right_path, "r");
    if(fl == NULL)
    {
        printf("No such file: %s\nPlease give the correct path for file 1.\n", left_path);
        return 1;
    }
    if(fr == NULL)
    {
        printf("No such file: %s\nPlease give the correct path for file 2.\n", right_path);
        return 1;
    }

    hl = get_line(MAX_LINE_LEN, fl);
    left_col_pos = get_col_pos(hl, col);
    if(left_col_pos < 0)
    {
        printf("Column %s does not exist in %s.\n", col, left_path);
        return 2;
    }

    hr = get_line(MAX_LINE_LEN, fr);
    right_col_pos = get_col_pos(hr, col);
    if(right_col_pos < 0)
    {
        printf("Column %s does not exist in %s\n.", col, right_path);
        return 2;
    }

    join_header(hl, hr);

    if(strcmp(join_type, "inner") == 0 || strcmp(join_type, "left") == 0)
        fclose(fr);
    else fclose(fl);

    if(strcmp(join_type, "inner") == 0)
    {
        left_line = get_line(MAX_LINE_LEN, fl);
        while(strcmp(left_line,"\0") != 0)
        {
            join_line(left_line, right_path, left_col_pos, right_col_pos, join_type);
            left_line = get_line(MAX_LINE_LEN, fl);
        }
    }
    else if(strcmp(join_type, "left") == 0)
    {
        right_len = get_col_cnt(hr);
        left_line = get_line(MAX_LINE_LEN, fl);
        while(strcmp(left_line,"\0") != 0)
        {
            rows = join_line(left_line, right_path, left_col_pos, right_col_pos, join_type);
            if(rows == 0)
                fill_row(left_line, join_type, right_len);
            left_line = get_line(MAX_LINE_LEN, fl);
        }
    }
    else
    {
        left_len = get_col_cnt(hl);
        right_line = get_line(MAX_LINE_LEN, fr);
        while(strcmp(right_line,"\0") != 0)
        {
            rows = join_line(right_line, left_path, right_col_pos, left_col_pos, join_type);
            if(rows == 0)
                fill_row(right_line, join_type, left_len);
            right_line = get_line(MAX_LINE_LEN, fr);
        }
    }
    free(hl);
    free(hr);
    return 0;
}