// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<syscall.h>>


#ifndef SYSCALL_H
# define SYSCALL_H
# include "ft_stdint.h"

// system call wrappers

/// system call with 0 arguments
void	*syscall0(uintptr_t n);

/// system call with 1 arguments
void	*syscall1(uintptr_t n, void *a1);

/// system call with 2 arguments
void	*syscall2(uintptr_t n, void *a1, void *a2);

/// system call with 3 arguments
void	*syscall3(uintptr_t n, void *a1, void *a2, void *a3);

/// system call with 4 arguments
void	*syscall4(uintptr_t n, void *a1, void *a2, void *a3, void *a4);

/// system call with 5 arguments
void	*syscall5(uintptr_t n, void *a1, void *a2, void *a3, void *a4, void *a5);

/// system call with 6 arguments
void	*syscall6(uintptr_t n, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6);

// convenience macros
# define _cast	(void *)(uintptr_t)

# define syscall1(n, a)					(syscall1(n, _cast a))
# define syscall2(n, a, b)				(syscall2(n, _cast a, _cast b))
# define syscall3(n, a, b, c)			(syscall3(n, _cast a, _cast b, _cast c))
# define syscall4(n, a, b, c, d)		(syscall4(n, _cast a, _cast b, _cast c, _cast d))
# define syscall5(n, a, b, c, d, e)		(syscall5(n, _cast a, _cast b, _cast c, _cast d, _cast e))
# define syscall6(n, a, b, c, d, e, f)	(syscall6(n, _cast a, _cast b, _cast c, _cast d, _cast e, _cast f))

// system call numbers

# define SYS_READ						0
# define SYS_WRITE						1
# define SYS_OPEN						2
# define SYS_CLOSE						3
# define SYS_STAT						4
# define SYS_FSTAT						5
# define SYS_LSTAT						6
# define SYS_POLL						7
# define SYS_LSEEK						8
# define SYS_MMAP						9
# define SYS_MPROTECT					10
# define SYS_MUNMAP						11
# define SYS_BRK						12
# define SYS_RT_SIGACTION				13
# define SYS_RT_SIGPROCMASK				14
# define SYS_RT_SIGRETURN				15
# define SYS_IOCTL						16
# define SYS_PREAD64					17
# define SYS_PWRITE64					18
# define SYS_READV						19
# define SYS_WRITEV						20
# define SYS_ACCESS						21
# define SYS_PIPE						22
# define SYS_SELECT						23
# define SYS_SCHED_YIELD				24
# define SYS_MREMAP						25
# define SYS_MSYNC						26
# define SYS_MINCORE					27
# define SYS_MADVISE					28
# define SYS_SHMGET						29
# define SYS_SHMAT						30
# define SYS_SHMCTL						31
# define SYS_DUP						32
# define SYS_DUP2						33
# define SYS_PAUSE						34
# define SYS_NANOSLEEP					35
# define SYS_GETITIMER					36
# define SYS_ALARM						37
# define SYS_SETITIMES					38
# define SYS_GETPID						39
# define SYS_SENDFILE					40
# define SYS_SOCKET						41
# define SYS_CONNECT					42
# define SYS_ACCEPT						43
# define SYS_SENDTO						44
# define SYS_RECVFROM					45
# define SYS_SENDMSG					46
# define SYS_RECVMSG					47
# define SYS_SHUTDOWN					48
# define SYS_BIND						49
# define SYS_LISTEN						50
# define SYS_GETSOCKNAME				51
# define SYS_GETPEERNAME				52
# define SYS_SOCKETPAIR					53
# define SYS_SETSOCKOPT					54
# define SYS_GETSOCKOPT					55
# define SYS_CLONE						56
# define SYS_FORK						57
# define SYS_VFORK						58
# define SYS_EXECVE						59
# define SYS_EXIT						60
# define SYS_WAIT4						61
# define SYS_KILL						62
# define SYS_UNAME						63
# define SYS_SEMGET						64
# define SYS_SEMOP						65
# define SYS_SEMCTL						66
# define SYS_SHMDT						67
# define SYS_MSGGET						68
# define SYS_MSGSND						69
# define SYS_MSGRCV						70
# define SYS_MSGCTL						71
# define SYS_FCNTL						72
# define SYS_FLOCK						73
# define SYS_FSYNC						74
# define SYS_FDATASYNC					75
# define SYS_TRUNCATE					76
# define SYS_FTRUNCATE					77
# define SYS_GETDENTS					78
# define SYS_GETCWD						79
# define SYS_CHDIR						80
# define SYS_FCHDIR						81
# define SYS_RENAME						82
# define SYS_MKDIR						83
# define SYS_RMDIR						84
# define SYS_CREAT						85
# define SYS_LINK						86
# define SYS_UNLINK						87
# define SYS_SYMLINK					88
# define SYS_READLINK					89
# define SYS_CHMOD						90
# define SYS_FCHMOD						91
# define SYS_CHOWN						92
# define SYS_FCHOWN						93
# define SYS_LCHOWN						94
# define SYS_UMASK						95
# define SYS_GETTIMEOFDAY				96
# define SYS_GETRLIMIT					97
# define SYS_GETRUSAGE					98
# define SYS_SYSINFO					99
# define SYS_TIMES						100
# define SYS_PTRACE						101
# define SYS_GETUID						102
# define SYS_SYSLOG						103
# define SYS_GETGID						104
# define SYS_SETUID						105
# define SYS_SETGID						106
# define SYS_GETEUID					107
# define SYS_GETEGID					108
# define SYS_SETPGID					109
# define SYS_SETPPID					110
# define SYS_GETPGRP					111
# define SYS_SETSID						112
# define SYS_SETREUID					113
# define SYS_SETREGID					114
# define SYS_GETGROUPS					115
# define SYS_SETGROUPS					116
# define SYS_SETRESUID					117
# define SYS_GETRESUID					118
# define SYS_SETRESGID					119
# define SYS_GETRESGID					120
# define SYS_GETPGID					121
# define SYS_SETFSUID					122
# define SYS_SETFSGID					123
# define SYS_GETSID						124
# define SYS_CAPGET						125
# define SYS_CAPSET						126
# define SYS_RT_SIGPENDING				127
# define SYS_RT_SIGTIMEDWAIT			128
# define SYS_RT_SIGQUEUEINFO			129
# define SYS_RT_SIGSUSPEND				130
# define SYS_SIGALTSTACK				131
# define SYS_UTIME						132
# define SYS_MKNOD						133
# define SYS_USELIB						134
# define SYS_PERSONALITY				135
# define SYS_USTAT						136
# define SYS_STATFS						137
# define SYS_FSTATFS					138
# define SYS_SYSFS						139
# define SYS_GETPRIORITY				140
# define SYS_SETPRIORITY				141
# define SYS_SCHEC_SETPARAM				142
# define SYS_SCHED_GETPARAM				143
# define SYS_SCHED_SETSCHEDULER			144
# define SYS_SCHED_GETSCHEDULER			145
# define SYS_SCHED_GET_PRIORITY_MAX		146
# define SYS_SCHED_GET_PRIORITY_MIN		147
# define SYS_SCHED_RR_GET_INTERVAL		148
# define SYS_MLOCK						149
# define SYS_MUNLOCK					150
# define SYS_MLOCKALL					151
# define SYS_MUNLOCKALL					152
# define SYS_VHANGUP					153
# define SYS_MODIFY_LDT					154
# define SYS_PIVOT_ROOT					155
# define SYS__SYSCTL					156
# define SYS_PRCTL						157
# define SYS_ARCH_PRCTL					158
# define SYS_ADJTIMEX					159
# define SYS_SETRLIMIT					160
# define SYS_CHROOT						161
# define SYS_SYNC						162
# define SYS_ACCT						163
# define SYS_SETTIMEOFDAY				164
# define SYS_MOUNT						165
# define SYS_UMOUNT2					166
# define SYS_SWAPON						167
# define SYS_SAWPOFF					168
# define SYS_REBOOT						169
# define SYS_SETHOSTNAME				170
# define SYS_SETDOMAINNAME				171
# define SYS_IOPL						172
# define SYS_IOPERM						173
# define SYS_CREATE_MODULE				174
# define SYS_INIT_MODULE				175
# define SYS_DELETE_MODULE				176
# define SYS_GET_KERNEL_SYMS			177
# define SYS_QUERY_MODULE				178
# define SYS_QUOTACTL					179
# define SYS_NFSSERVCTL					180
# define SYS_GETPMSG					181
# define SYS_PUTPMSG					182
# define SYS_AFS_SYSCALL				183
# define SYS_TUXCALL					184
# define SYS_SECURITY					185
# define SYS_GETTID						186
# define SYS_READAHEAD					187
# define SYS_SETXATTR					188
# define SYS_LSETXATTR					189
# define SYS_FSETXATTR					190
# define SYS_GETXATTR					191
# define SYS_LGETXATTR					192
# define SYS_FGETXATTR					193
# define SYS_LISTXATTR					194
# define SYS_LLISTXATTR					195
# define SYS_FLISTXATTR					196
# define SYS_REMOVEXATTR				197
# define SYS_LREMOVEXATTR				198
# define SYS_FREMOVEXATTR				199
# define SYS_TKILL						200
# define SYS_TIME						201
# define SYS_FUTEX						202
# define SYS_SCHED_SETAFFINITY			203
# define SYS_SCHED_GETAFFINITY			204
# define SYS_SET_THREAD_AREA			205
# define SYS_IO_SETUP					206
# define SYS_IO_DESTROY					207
# define SYS_IO_GETEVENTS				208
# define SYS_IO_SUBMIT					209
# define SYS_IO_CANCEL					210
# define SYS_GET_THREAD_AREA			211
# define SYS_LOOKUP_DCOOKIE				212
# define SYS_EPOLL_CREATE				213
# define SYS_EPOLL_CTL_OLD				214
# define SYS_EPOLL_WAIT_OLD				215
# define SYS_REMAP_FILE_PAGES			216
# define SYS_GETDENTS64					217
# define SYS_SET_TID_ADDRESS			218
# define SYS_RESTART_SYSCALL			219
# define SYS_SEMTIMEDOP					220
# define SYS_FADVISE64					221
# define SYS_TIMER_CREATE				222
# define SYS_TIMER_SETTIME				223
# define SYS_TIMER_GETTIME				224
# define SYS_TIMER_GETOVERRUN			225
# define SYS_TIMER_DELETE				226
# define SYS_CLOCK_SETTIME				227
# define SYS_CLOCK_GETTIME				228
# define SYS_CLOCK_GETRES				229
# define SYS_CLOCK_NANOSLEEP			230
# define SYS_EXIT_GROUP					231
# define SYS_EPOLL_WAIT					232
# define SYS_EPOLL_CTL					233
# define SYS_TGKILL						234
# define SYS_UTIMES						235
# define SYS_VSERVER					236
# define SYS_MBIND						237
# define SYS_SET_MEMPOLICY				238
# define SYS_GET_MEMPOLICY				239
# define SYS_MQ_OPEN					240
# define SYS_MQ_UNLINK					241
# define SYS_MQ_TIMEDSEND				242
# define SYS_MQ_TIMEDRECEIVE			243
# define SYS_MQ_NOTIFY					244
# define SYS_MQ_GETSETATTR				245
# define SYS_KEXEC_LOAD					246
# define SYS_WAITID						247
# define SYS_ADD_KEY					248
# define SYS_REQUEST_KEY				249
# define SYS_KEYCTL						250
# define SYS_IOPRIO_SET					251
# define SYS_IOPRIO_GET					252
# define SYS_IONOTIFY_INIT				253
# define SYS_IONOTIFY_ADD_WATCH			254
# define SYS_IONOTIFY_RM_WATCH			255
# define SYS_MIGRATE_PAGES				256
# define SYS_OPENAT						257
# define SYS_MKDIRAT					258
# define SYS_MKNODAT					259
# define SYS_FCHOWNAT					260
# define SYS_FUTIMESAT					261
# define SYS_NEWFSTATAT					262
# define SYS_UNLINKAT					263
# define SYS_RENAMEAT					264
# define SYS_LINKAT						265
# define SYS_SYMLINKAT					266
# define SYS_READLINKAT					267
# define SYS_FCHMODAT					268
# define SYS_FACCESSAT					269
# define SYS_PSELECT6					270
# define SYS_PPOLL						271
# define SYS_UNSHARE					272
# define SYS_SET_ROBUST_LIST			273
# define SYS_GET_ROBUST_LIST			274
# define SYS_SPLICE						275
# define SYS_TEE						276
# define SYS_SYNC_FILE_RANGE			277
# define SYS_VMSPLICE					278
# define SYS_MOVE_PAGES					279
# define SYS_UTIMENSAT					280
# define SYS_EPOLL_PWAIT				281
# define SYS_SIGNALFD					282
# define SYS_TIMERFD_CREATE				283
# define SYS_EVENTFD					284
# define SYS_FALLOCATE					285
# define SYS_TIMERFD_SETTIME			286
# define SYS_TIMERFD_GETTIME			287
# define SYS_ACCEPT4					288
# define SYS_SIGNALFD4					289
# define SYS_EVENTFD2					290
# define SYS_EPOLL_CREATE1				291
# define SYS_DUP3						292
# define SYS_PIPE2						293
# define SYS_INOTIFY_INIT1				294
# define SYS_PREADV						295
# define SYS_PWRITEV					296
# define SYS_RT_TGSIGQUEUEINFO			297
# define SYS_PERF_EVENT_OPEN			298
# define SYS_RECVMMSG					299
# define SYS_FANOTIFY_INIT				300
# define SYS_FANOTIFY_MARK				301
# define SYS_PRLIMIT64					302
# define SYS_NAME_TO_HANDLE_AT			303
# define SYS_OPEN_BY_HANDLE_AT			304
# define SYS_CLOCK_ADJTIME				305
# define SYU_SYNCFS						306
# define SYS_SENDMMSG					307
# define SYS_SETNS						308
# define SYS_GETCPU						309
# define SYS_PROCESS_VM_READV			310
# define SYS_PROCESS_VM_WRITEV			311
# define SYS_KCMP						312
# define SYS_FINIT_MODULE				313
# define SYS_SCHED_SETATTR				314
# define SYS_SCHED_GETATTR				315
# define SYS_RENAMEAT2					316
# define SYS_SECCOMP					317
# define SYS_GETRANDOM					318
# define SYS_MEMFD_CREATE				319
# define SYS_KEXEC_FILE_LOAD			320
# define SYS_BPF						321
# define SYS_EXECVEAT					322
# define SYS_USERFAULTFD				323
# define SYS_MEMBARRIER					324
# define SYS_MLOCK2						325
# define SYS_COPY_FILE_RANGE			326
# define SYS_PREADV2					327
# define SYS_PWRITEV2					328
# define SYS_PKEY_MPROTECT				329
# define SYS_PKEY_ALLOC					330
# define SYS_PKEY_FREE					331
# define SYS_STATX						332
# define SYS_IO_PGETEVENTS				333
# define SYS_RSEQ						334
# define SYS_PIDFD_SEND_SIGNAL			424
# define SYS_IO_URING_SETUP				425
# define SYS_IO_URING_ENTER				426
# define SYS_IO_URING_REGISTER			427
# define SYU_OPEN_TREE					428
# define SYS_MOVE_MCOUNT				429
# define SYS_FSOPEN						430
# define SYS_FSCONFIG					431
# define SYS_FSMOUNT					432
# define SYS_FSPICK						433
# define SYS_PIDFD_OPEN					434
# define SYS_CLONE3						435
# define SYS_CLOSE_RANGE				436
# define SYS_OPENAT2					437
# define SYS_PIDFD_GETFD				438
# define SYS_FACCESSAT2					439
# define SYS_PROCESS_MADVISE			440
# define SYS_EPOLL_PWAIT2				441
# define SYS_MOUNT_SETATTR				442
# define SYS_QUOTACTL_FD				443
# define SYS_LANDLOCK_CREATE_RULESET	444
# define SYS_LANDLOCK_ADD_RULE			445
# define SYS_LANDLOCK_RESTRICT_SELF		446
# define SYS_MEMFD_SECRET				447
# define SYS_PROCESS_MRELEASE			448
# define SYS_FUTEX_WAITV				449
# define SYS_SET_MEMPOLICY_HOME_NODE	450
# define SYS_CACHESTAT					451
# define SYS_FCHMODAT2					452
# define SYS_MAP_SHADOW_STACK			453
# define SYS_FUTEX_WAKE					454
# define SYS_FUTEX_WAIT					455
# define SYS_FUTEX_REQUEUE				456

#endif
