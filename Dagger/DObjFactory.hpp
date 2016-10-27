
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
    class ObjFactoryBase : public ::std::enable_shared_from_this<ObjFactoryBase<T> >
    {
    public:
        virtual ~ObjFactoryBase() { }
        virtual ::std::shared_ptr<T> CreateObj() = 0;

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
        virtual ::std::shared_ptr<ParentClass> CreateObj() { return ::std::shared_ptr<ObjClass>(new ObjClass); }

    private:
        DAGGER_DISALLOW_COPY_AND_ASSIGN_(ObjFactoryImpl);

    };

    template <typename ParentClass,typename ObjClass>
    class CloneObjFactoryImpl : public ObjFactoryBase<ParentClass>
    {
        ::std::shared_ptr<ObjClass> m_templateObj;
    public:
        CloneObjFactoryImpl(::std::shared_ptr<ObjClass> templateObj) : m_templateObj(templateObj) { }
        ::std::shared_ptr<ObjClass> GetTemplateObj() { return m_templateObj; }

        virtual ::std::shared_ptr<ParentClass> CreateObj()
            {
                if (m_templateObj.get() == NULL) return ::std::shared_ptr<ParentClass>();
                return ::std::shared_ptr<ObjClass>(new ObjClass(*m_templateObj));
            }

    private:
        DAGGER_DISALLOW_COPY_AND_ASSIGN_(CloneObjFactoryImpl);

    };template<typename T>
    class ObjFactoryBase : public ::std::enable_shared_from_this<ObjFactoryBase<T> >
      {
      public:
          virtual ~ObjFactoryBase() { }
          virtual ::std::shared_ptr<T> CreateObj() = 0;

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
        virtual ::std::shared_ptr<ParentClass> CreateObj() { return ::std::shared_ptr<ObjClass>(new ObjClass); }
    private:
        DAGGER_DISALLOW_COPY_AND_ASSIGN_(ObjFactoryImpl);

    };

    template <typename ParentClass,typename ObjClass>
    class CloneObjFactoryImpl : public ObjFactoryBase<ParentClass>
    {
        ::std::shared_ptr<ObjClass> m_templateObj;
    public:
        CloneObjFactoryImpl(::std::shared_ptr<ObjClass> templateObj) : m_templateObj(templateObj) { }
        ::std::shared_ptr<ObjClass> GetTemplateObj() { return m_templateObj; }

        virtual ::std::shared_ptr<ParentClass> CreateObj()
            {
                if (m_templateObj.get() == NULL) return ::std::shared_ptr<ParentClass>();
                return ::std::shared_ptr<ObjClass>(new ObjClass(*m_templateObj));
            }
    private:
        DAGGER_DISALLOW_COPY_AND_ASSIGN_(CloneObjFactoryImpl);

    };
}
#endif /* DOBJFACTORY_H */