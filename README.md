# Wicked CSV
Join two CVS files.

# Assumptions
Input files follow the standard described on [rfc4180](https://datatracker.ietf.org/doc/html/rfc4180).

# Installation
- gcc:
```[shell]
gcc src/main.c src/joiner.c -o wicked_csv.exe
```

# Usage
```[shell]
./wicked_csv.exe join [path1] [path2] [by (col_name)] [join_type: inner/left/right]
```
Optional - save output to file:
```[shell]
./wicked_csv.exe join [path1] [path2] [by (col_name)] [join_type: inner/left/right] > [output_path]
```
