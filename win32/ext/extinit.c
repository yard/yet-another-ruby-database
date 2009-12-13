#include "ruby.h"

#define init(func, name) {	\
    extern void func _((void));	\
    ruby_init_ext(name, func);	\
}

void ruby_init_ext _((const char *name, void (*init)(void)));

void Init_ext _((void))
{
    init(Init_digest, "digest.so");
    init(Init_md5, "digest/md5.so");
    init(Init_rmd160, "digest/rmd160.so");
    init(Init_sha1, "digest/sha1.so");
    init(Init_sha2, "digest/sha2.so");
    init(Init_dl, "dl.so");
    init(Init_socket, "socket.so");
    init(Init_win32ole, "win32ole.so");
}
