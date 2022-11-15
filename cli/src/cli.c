#include <sha256.h>
#include <stdio.h>

int main() {
    char str[] = "Hello world!";
    printf("%s\n", sha256(str));
    return 0;
}
