/*
 * Saitek X52 IO driver
 *
 * Copyright (C) 2012-2020 Nirenjan Krishnan (nirenjan@nirenjan.org)
 *
 * SPDX-License-Identifier: GPL-2.0-only WITH Classpath-exception-2.0
 */

#include <stdlib.h>
#include <string.h>
#include "io_common.h"

int libx52io_init(libx52io_context **ctx)
{
    libx52io_context *tmp;

    if (ctx == NULL) {
        return LIBX52IO_ERROR_INVALID;
    }

    if (hid_init()) {
        return LIBX52IO_ERROR_INIT_FAILURE;
    }

    // Allocate a context
    tmp = calloc(1, sizeof(*tmp));
    if (tmp == NULL) {
        return LIBX52IO_ERROR_INIT_FAILURE;
    }

    *ctx = tmp;
    return LIBX52IO_SUCCESS;
}

void libx52io_exit(libx52io_context *ctx)
{
    // Close any open handles, free context
    if (ctx == NULL) {
        return;
    }

    libx52io_close(ctx);
    hid_exit();
}

int libx52io_close(libx52io_context *ctx)
{
    if (ctx == NULL) {
        return LIBX52IO_ERROR_INVALID;
    }

    if (ctx->handle != NULL) {
        hid_close(ctx->handle);
        memset(ctx, 0, sizeof(*ctx));
    }

    return LIBX52IO_SUCCESS;
}

int libx52io_open(libx52io_context *ctx)
{
    struct hid_device_info *devs, *cur_dev;
    int rc = LIBX52IO_SUCCESS;

    if (ctx == NULL) {
        return LIBX52IO_ERROR_INVALID;
    }

    /* Close any already open handles */
    libx52io_close(ctx);

    /* Enumerate all Saitek HID devices */
    devs = hid_enumerate(0x06a3, 0);
    cur_dev = devs;
    while (cur_dev) {
        switch (cur_dev->product_id) {
        case 0x0255:
        case 0x075c:
        case 0x0762:
            ctx->handle = hid_open_path(cur_dev->path);
            if (ctx->handle == NULL) {
                rc = LIBX52IO_ERROR_CONN;
                goto finally;
            }

            ctx->pid = cur_dev->product_id;
            /* _x52io_set_axis_range(ctx); */
            /* _x52io_set_report_parser(ctx); */

            break;

        default:
            break;
        }

        cur_dev = cur_dev->next;
    }

finally:
    hid_free_enumeration(devs);
    return rc;
}
