#pragma once

#include <pthread.h>

template<class T>
class ThreadLocal {
public:
    ThreadLocal<T>() {
        pthread_key_create(&key, [](void *) {});
    }

    ~ThreadLocal<T>() {
        pthread_key_delete(key);
    }

    T *get() {
        return reinterpret_cast<T *>(pthread_getspecific(key));
    }

    void set(T *t) {
        pthread_setspecific(key, t);
    }

private:
    pthread_key_t key{0};
};