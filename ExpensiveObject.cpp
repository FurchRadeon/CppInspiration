#include "ObjectPool.h"

class ExpensiveObject
{
public:
    ExpensiveObject() { mID = ++msCount; cout << "ctor " << mID << endl; }
    virtual ~ExpensiveObject() { cout << "dtor " << mID << endl; }

private:
    int mID;
    static int msCount;
    // Other data members (not shown)
};
int ExpensiveObject::msCount = 0;

ObjectPool<ExpensiveObject>::Object getExpensiveObject(ObjectPool<ExpensiveObject>& pool)
{
    auto object = pool.acquireObject();
    return object;
}

void processExpensiveObject(ObjectPool<ExpensiveObject>::Object& /*object*/)
{
}


int main()
{
    ObjectPool<ExpensiveObject> requestPool;

    {
        vector<ObjectPool<ExpensiveObject>::Object> objects;
        for (size_t i = 0; i < 10; ++i) {
            objects.push_back(getExpensiveObject(requestPool));
        }
    }

    cout << "Loop starting." << endl;
    for (size_t i = 0; i < 100; ++i) {
        auto req = getExpensiveObject(requestPool);
        processExpensiveObject(req);
    }
    cout << "Loop finished." << endl;

    return EXIT_SUCCESS;
}
