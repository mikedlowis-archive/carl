#include <carl.h>

typedef struct obj_t {
    uintptr_t refcount;
    void (*destruct)(void*);
    uint8_t data[];
} obj_t;

void* refallocate(size_t sz)
{
    return refobject(sz, nil);
}

void* refobject(size_t sz, void (*destruct)(void*))
{
    obj_t* object = (obj_t*)malloc(sizeof(obj_t) + sz);
    object->refcount = 1;
    object->destruct = destruct;
    return &(object->data[0]);
}

void* refretain(void* obj)
{
    obj_t* object = container_of(obj, obj_t, data);
    object->refcount++;
    return obj;
}

void refrelease(void* obj)
{
    obj_t* object = container_of(obj, obj_t, data);
    object->refcount--;
    if (object->refcount == 0) {
        if (nil != object->destruct)
            object->destruct(obj);
        free(object);
    }
}

size_t refcount(void* obj)
{
    obj_t* object = container_of(obj, obj_t, data);
    return object->refcount;
}

void refreplace(void** var, void* val)
{
    void* deadite = *var;
    *var = val;
    refrelease(deadite);
}

