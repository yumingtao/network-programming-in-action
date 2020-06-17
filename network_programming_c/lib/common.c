//
// Created by Yu, Mingtao on 2020/6/17.
//

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


void error(int status, int err, char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    if (err) {
        fprintf(stderr, ": %s (%d)\n", strerror(err), err);
    }
    if (status) {
        exit(status);
    }
}
