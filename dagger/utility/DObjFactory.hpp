
#ifndef DOBJFACTORY_H
#define DOBJFACTORY_H

#include <memory>

namespace Dagger
{
#define DAGGER_DISALLOW_ASSIGN_(type) void operator=(type const &)

#define DAGGER_DISALLOW_COPY_AND_ASSIGN_(type) \
    type(type const &);                        \
    DAGGER_DISALLOW_ASSIGN_(type)

template <typename T>
class DObjFactoryBase
{
   public:
    virtual ~DObjFactoryBase() {}
    virtual T *CreateObj() = 0;

   protected:
    DObjFactoryBase() {}
   private:
    DAGGER_DISALLOW_COPY_AND_ASSIGN_(DObjFactoryBase);
};

template <typename ParentClass, typename ObjClass>
class DObjFactoryImpl : public DObjFactoryBase<ParentClass>
{
   public:
    DObjFactoryImpl() {}
    virtual ParentClass *CreateObj() { return new ObjClass; }
   private:
    DAGGER_DISALLOW_COPY_AND_ASSIGN_(DObjFactoryImpl);
};
}

#endif /* DOBJFACTORY_H */
