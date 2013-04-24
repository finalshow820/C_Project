#include "locker_pthread.h"

typedef struct _PrivInfo
{
    pthread_mutex_t mutex;
}PrivInfo;


static void*  locker_pthread_lock(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    int ret = pthread_mutex_lock(&priv->mutex);

	printf("**********Lock Operation!!!!!!!!\n");
    //return ret == 0 ? RET_OK : RET_FAIL;
    return;
}

static void*  locker_pthread_unlock(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    int ret = pthread_mutex_unlock(&priv->mutex);
	printf("**********UnLock Operation!!!!!!!!\n");

    //return ret == 0 ? RET_OK : RET_FAIL;
    return;
}

static void*  locker_pthread_destroy(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    int ret = pthread_mutex_lock(&priv->mutex);

    return;
}

static void*  locker_pthread_get(Locker* thiz)
{
    PrivInfo* priv = (PrivInfo*)thiz->priv;

    return &priv->mutex;

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
