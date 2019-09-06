#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
typedef unsigned int uint;
typedef void *any_t;
typedef int (*PFany)(any_t, any_t);
typedef int (*printFunc)(any_t);

#endif /* COMMON_H */