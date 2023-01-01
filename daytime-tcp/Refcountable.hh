#ifndef Refcountable_hh
#define Refcountable_hh

#if __cplusplus < 201103L
# error "Older versions of C++ not supported."
#endif

#include <atomic>

namespace util 
{
    using atomic_type = std::atomic_int64_t;
    static inline int64_t AtomicAdd(volatile atomic_type* counter, const int32_t toAdd)
    {
        const auto oldValue = counter->fetch_add(toAdd);

        // Returns new value (after adding value).
        return oldValue + toAdd;
    }
}

#include <boost/assert.hpp>

namespace util
{
    class Refcountable
    {
    protected:
        virtual ~Refcountable(){};

        // Optional delete notify, can be overridden by derived class to receive
        // notification of a pending delete.
        virtual void deleteNotify() {}

    public:
        // Public method called by intrusive_ptr<> template
        void _addRef_()
        {
            BOOST_ASSERT(theRefcount >= 0);
            (void)AtomicAdd(&theRefcount, 1);
        }

        // Public method to decrement reference count, called by intrusive_ptr<> template
        // class via macro intrusive_ptr_release() in this file.
        void _decRef_()
        {
            BOOST_ASSERT(theRefcount >= 0);
            if ( AtomicAdd(&theRefcount,  -1) == 0 )
            {
                deleteNotify();
                theRefcount = -1;
                delete this;
            }
        }

        // Returns current reference count for this object.
        int refcount() const { return theRefcount; }

    protected:
        // Protected constructor initializes theRefcount to 0.
        Refcountable() : theRefcount(0) {}

    private:
        atomic_type theRefcount;

        Refcountable& operator=(const Refcountable&rhs);
        Refcountable(Refcountable&);
    };
}

#ifdef _inc_intrusive_ptr_add_ref_macro

// Scaffolding required for boost/intrusive_ptr.hpp
// Should be a template in a namespace but these macros can be used in a pinch
//
# define intrusive_ptr_add_ref(_ptr) do { _ptr->_addRef_(); } while(false)
# define intrusive_ptr_release(_ptr) do { _ptr->_decRef_(); } while(false)
#endif /* _inc_intrusive_ptr_add_ref_macro */

#endif  // Refcountable_hh
