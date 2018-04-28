#pragma once


#define __attribute__(A) 

typedef void* pthread_mutex_t;
extern unsigned int __sync_fetch_and_sub(unsigned int* p, unsigned int a);
extern unsigned int __builtin_popcount(unsigned int a);
