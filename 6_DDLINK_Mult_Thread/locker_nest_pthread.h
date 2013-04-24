#include <locker_pthread.h>
struct _Locker;
typedef struct _Locker Locker_nest;

/*typedef enum ret_val
{
	RET_OK;
	RET_FAIL
}Ret;*/


typedef void*  (*LockerNestLockFunc)(Locker* thiz);
typedef void*  (*LockerNestUnlockFunc)(Locker* thiz);
typedef void*  (*LockerNestDestroyFunc)(Locker* thiz);
typedef void*  (*LockerNestGet)(Locker* thiz);
typedef unsigned long  (*TaskSelfFunc)(void *);




struct _Locker
{
    LockerNestLockFunc    lock;
    LockerNestUnlockFunc  unlock;
    LockerNestDestroyFunc destroy;
	LockerNestGet         getlock;
    char priv[0];
};

Locker* locker_nest_create(Locker *locker,(TaskSelfFunc)pthread_self);








