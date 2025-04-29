
#include <linux/btf_ids.h>
#include <linux/types.h>
#include <linux/bpf_compressor.h>
#include <linux/errno.h>
#include <linux/bpf.h>
#include <linux/btf.h>
#include <linux/filter.h>


BTF_ID(func, bpf_compressor_decide);
BTF_ID(func, bpf_compressor_verify);

const struct bpf_func_proto *
bpf_compressor_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog);

const struct bpf_func_proto *
bpf_compressor_func_proto(enum bpf_func_id func_id, const struct bpf_prog *prog) {
    switch (func_id) {
    case BPF_FUNC_lzo_compress:
        return &bpf_lzo_compress_proto;
    case BPF_FUNC_copy_from_buffer:
        return &bpf_copy_from_buffer_proto;
    case BPF_FUNC_get_current_uid_gid:
        return &bpf_get_current_uid_gid_proto;
    case BPF_FUNC_get_current_pid_tgid:
        return &bpf_get_current_pid_tgid_proto;
    default:
        return bpf_base_func_proto(func_id, prog);
    }
}

const struct bpf_prog_ops bpf_compressor_prog_ops = {
};

const struct bpf_verifier_ops bpf_compressor_verifier_ops = {
    .get_func_proto = bpf_compressor_func_proto,
    .is_valid_access = btf_ctx_access,
};




int bpf_compressor_decide(struct compress_ctx_kern * ctx) {
    return 0;
}

int bpf_compressor_verify(struct compress_ctx_kern * ctx) {
    return -EINVAL;
}