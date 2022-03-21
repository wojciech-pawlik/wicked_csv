#include "joiner.h"

int main(int argc, char** argv) {
    int status;

    if(argc < 5)
    {
<<<<<<< HEAD
        printf("Too few arguments.\n");
=======
        printf("Too less arguments.\n");
>>>>>>> 50f151b1b924bb3ea0351047003e6f29d8ecc70e
        return -1;
    }
    if(strcmp(argv[1], "join") != 0)
    {
        printf("Method %s not specified. You can use \"join\" method only in this demo version.\n", argv[1]);
        return -2;
    }
    char* left_path = argv[2];
    char* right_path = argv[3];
    char* column_name = argv[4];

    char* join_type;
    if(argc == 5)
    {
        printf("Join type not specified. Using default \"inner join\" method.\n");
        join_type = "inner";
    }
    else
    {
        join_type = argv[5];
        if(strcmp(join_type, "inner") != 0 && strcmp(join_type, "left") != 0 && strcmp(join_type, "right") != 0)
        {
            printf("Join type not specified correctly: \"%s\" instead of inner, left, or right. Using default \"inner join\" method.\n", join_type);
            join_type = "inner";
        }
    }

    status = join(left_path, right_path, column_name, join_type);
    return status;
}
