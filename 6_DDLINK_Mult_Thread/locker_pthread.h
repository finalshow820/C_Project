#include <pthread.h>
#include <stdlib.h>
struct _Locker;
typedef struct _Locker Locker;

/*typedef enum ret_val
{
	RET_OK;
	RET_FAIL
}Ret;*/


typedef void*  (*LockerLockFunc)(Locker* thiz);
typedef void*  (*LockerUnlockFunc)(Locker* thiz);
typedef void*  (*LockerDestroyFunc)(Locker* thiz);
typedef void*  (*LockerGet)(Locker* thiz);



struct _Locker
{
    LockerLockFunc    lock;
    LockerUnlockFunc  unlock;
    LockerDestroyFunc destroy;
	LockerGet         getlock;
    char priv[0];
};

Locker* locker_pthread_create(void);








