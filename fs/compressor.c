#include <linux/syscalls.h>
#include <linux/fs.h>
#include <linux/file.h>




int get_compression_stats(int fd, size_t __user * bytes_written, size_t __user * bytes_after_compression) {
    struct file *file;
    int ret = -EBADF;

    if (unlikely(!access_ok(bytes_written, sizeof(size_t)) ||
        unlikely(!access_ok(bytes_after_compression, sizeof(size_t))))) {
        return -EFAULT;
    }

    struct fd f = fdget(fd);
    if (fd_file(f)) {
        file = fd_file(f);
        ret = 0;
        if (bytes_written) {
            if (copy_to_user(bytes_written, &file->f_bytes_written, sizeof(size_t)))
                ret = -EFAULT;
        }
        if (ret == 0 && bytes_after_compression) {
            if (copy_to_user(bytes_after_compression, &file->f_bytes_after_compression, sizeof(size_t)))
                ret = -EFAULT;
        }
        fdput(f);
    }

    return ret;
}

int reset_compression_stats(int fd) {
    struct file *file;
    int ret = -EBADF;

    struct fd f = fdget(fd);
    if (fd_file(f)) {
        file = fd_file(f);
        ret = 0;
        file->f_bytes_written = 0;
        file->f_bytes_after_compression = 0;
        fdput(f);
    }

    return ret;
}

SYSCALL_DEFINE3(get_compression_stats, int, fd, size_t __user *, bytes_written, size_t __user *, bytes_after_compression) {
    return get_compression_stats(fd, bytes_written, bytes_after_compression);
}

SYSCALL_DEFINE1(reset_compression_stats, int, fd) {
    return reset_compression_stats(fd);
}
