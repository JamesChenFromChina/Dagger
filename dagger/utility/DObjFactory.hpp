
#ifndef DOBJFACTORY_H
#define DOBJFACTORY_H

#include <memory>

namespace Dagger {

#define DAGGER_DISALLOW_ASSIGN_(type)           \
    void operator=(type const &)

#define DAGGER_DISALLOW_COPY_AND_ASSIGN_(type)  \
    type(type const &);                         \
    DAGGER_DISALLOW_ASSIGN_(type)

    template<typename T>
    class ObjFactoryBase {
    public:
        virtual ~ObjFactoryBase() { }
        virtual T *CreateObj() = 0;

    protected:
        ObjFactoryBase() { }

    private:
        DAGGER_DISALLOW_COPY_AND_ASSIGN_(ObjFactoryBase);
    };

    template <typename ParentClass,typename ObjClass>
    class ObjFactoryImpl : public ObjFactoryBase<ParentClass>
    {
    public:
        ObjFactoryImpl() { }
        virtual ParentClass *CreateObj() { return new ObjClass; }

    private:
        DAGGER_DISALLOW_COPY_AND_ASSIGN_(ObjFactoryImpl);
    };

}

#endif /* DOBJFACTORY_H */
