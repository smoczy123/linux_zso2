#ifndef _LINUX_BPF_COMPRESSOR_H
#define _LINUX_BPF_COMPRESSOR_H


#include <linux/types.h>
#include <linux/uidgid_types.h>

struct compress_ctx_kern {
    union {
        struct {
            loff_t offset;
            size_t size;
        };
        struct {
            kuid_t uid;
            kgid_t gid;
        };
    };
    char *buf;
};

int bpf_compressor_decide(struct compress_ctx_kern *);

int bpf_compressor_verify(struct compress_ctx_kern *);


#endif /* _LINUX_BPF_COMPRESSOR_H */