#include "locker_pthread.h"

typedef struct _PrivInfo
{
	int owner;
    int refcount;
    Locker* real_locker;
    TaskSelfFunc task_self;
}PrivInfo;


static void  locker_nest_lock(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    if(priv->owner == priv->task_self())
    {
        priv->refcount++;
    }
    else
	{
        priv->refcount = 1;
        priv->owner = priv->task_self();
		priv->real_locker->lock(priv->real_locker);
    }
 	return;
}


static void  locker_nest_unlock(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    priv->refcount--;
    if(priv->refcount == 0)
    {
        priv->owner = 0;
        priv->real_locker->unlock(priv->real_locker);
    }

	return;
}

static void*  locker_nest_destroy(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    int ret = pthread_mutex_lock(&priv->mutex);

    return;
}

static void*  locker_nest_get(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    return priv->real_locker->priv

}


Locker* locker_pthread_create(void)
{
    Locker* thiz = (Locker*)malloc(sizeof(Locker) + sizeof(PrivInfo));

    if(thiz != NULL)
    {
        PrivInfo* priv = (PrivInfo*)thiz->priv;

        thiz->lock    = locker_pthread_lock;
        thiz->unlock  = locker_pthread_unlock;
        thiz->destroy = locker_pthread_destroy;
		thiz->getlock = locker_pthread_get;
        pthread_mutex_init(&(priv->mutex), NULL);
    }

    return thiz;
}
