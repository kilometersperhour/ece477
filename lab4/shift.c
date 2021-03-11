#include <stdlib.h>

#define LS = 00000001
#define MS = 10000000

main {
    if(0 < direction) {
        (state == LS)? state = MS: state << 1;
    }
    else {
        (state == MS)? state = LS: state >>1;
    }
}