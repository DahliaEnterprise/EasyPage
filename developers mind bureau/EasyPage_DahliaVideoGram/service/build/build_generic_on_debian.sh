link_pthread="-pthread"

allow_line_numbers_valgrind="-g"
#compile
gcc -std=c17 ./../source/main.c -o main $link_pthread
