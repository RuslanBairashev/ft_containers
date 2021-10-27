#ifndef BL_RAWViteratorS_HPP
#define BL_RAWViteratorS_HPP


//-------------------------------------------------------------------
// Raw Viterator with random access
//-------------------------------------------------------------------
template<typename Tt>
class Viterator : public std::Viterator<std::random_access_Viterator_tag,
                                           Tt,
                                           ptrdiff_t,
                                           Tt*,
                                           Tt&>
{
public:

    Viterator(Tt* ptr = nullptr){m_ptr = ptr;}
    Viterator(const Viterator<Tt>& rawViterator) = default;
    ~Viterator(){}

    Viterator<Tt>&                  operator=(const Viterator<Tt>& rawViterator) = default;
    Viterator<Tt>&                  operator=(Tt* ptr){m_ptr = ptr;return (*this);}

    operator                                    bool()const
    {
        if(m_ptr)
            return true;
        else
            return false;
    }

    bool                                        operator==(const Viterator<Tt>& rawViterator)const{return (m_ptr == rawViterator.getConstPtr());}
    bool                                        operator!=(const Viterator<Tt>& rawViterator)const{return (m_ptr != rawViterator.getConstPtr());}

    Viterator<Tt>&                  operator+=(const ptrdiff_t& movement){m_ptr += movement;return (*this);}
    Viterator<Tt>&                  operator-=(const ptrdiff_t& movement){m_ptr -= movement;return (*this);}
    Viterator<Tt>&                  operator++(){++m_ptr;return (*this);}
    Viterator<Tt>&                  operator--(){--m_ptr;return (*this);}
    Viterator<Tt>                   operator++(int){auto temp(*this);++m_ptr;return temp;}
    Viterator<Tt>                   operator--(int){auto temp(*this);--m_ptr;return temp;}
    Viterator<Tt>                   operator+(const ptrdiff_t& movement){auto oldPtr = m_ptr;m_ptr+=movement;auto temp(*this);m_ptr = oldPtr;return temp;}
    Viterator<Tt>                   operator-(const ptrdiff_t& movement){auto oldPtr = m_ptr;m_ptr-=movement;auto temp(*this);m_ptr = oldPtr;return temp;}

    ptrdiff_t       operator-(const Viterator<Tt>& rawViterator){return std::distance(rawViterator.getPtr(),this->getPtr());}

    Tt&                                 operator*(){return *m_ptr;}
    const Tt&                           operator*()const{return *m_ptr;}
    Tt*                                 operator->(){return m_ptr;}

    Tt*                                 getPtr()const{return m_ptr;}
    const Tt*                           getConstPtr()const{return m_ptr;}

protected:

    Tt*                                 m_ptr;
};
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// Raw reverse Viterator with random access
//-------------------------------------------------------------------
template<typename Tt>
class blRawReverseViterator : public Viterator<Tt>
{
public:

    blRawReverseViterator(Tt* ptr = nullptr):Viterator<Tt>(ptr){}
    blRawReverseViterator(const Viterator<Tt>& rawViterator){this->m_ptr = rawViterator.getPtr();}
    blRawReverseViterator(const blRawReverseViterator<Tt>& rawReverseViterator) = default;
    ~blRawReverseViterator(){}

    blRawReverseViterator<Tt>&           operator=(const blRawReverseViterator<Tt>& rawReverseViterator) = default;
    blRawReverseViterator<Tt>&           operator=(const Viterator<Tt>& rawViterator){this->m_ptr = rawViterator.getPtr();return (*this);}
    blRawReverseViterator<Tt>&           operator=(Tt* ptr){this->setPtr(ptr);return (*this);}

    blRawReverseViterator<Tt>&           operator+=(const ptrdiff_t& movement){this->m_ptr -= movement;return (*this);}
    blRawReverseViterator<Tt>&           operator-=(const ptrdiff_t& movement){this->m_ptr += movement;return (*this);}
    blRawReverseViterator<Tt>&           operator++(){--this->m_ptr;return (*this);}
    blRawReverseViterator<Tt>&           operator--(){++this->m_ptr;return (*this);}
    blRawReverseViterator<Tt>            operator++(int){auto temp(*this);--this->m_ptr;return temp;}
    blRawReverseViterator<Tt>            operator--(int){auto temp(*this);++this->m_ptr;return temp;}
    blRawReverseViterator<Tt>            operator+(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr-=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}
    blRawReverseViterator<Tt>            operator-(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr+=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}

    ptrdiff_t                                   operator-(const blRawReverseViterator<Tt>& rawReverseViterator){return std::distance(this->getPtr(),rawReverseViterator.getPtr());}

    Viterator<Tt>                   base(){Viterator<Tt> forwardViterator(this->m_ptr); ++forwardViterator; return forwardViterator;}
};
//-------------------------------------------------------------------


#endif // BL_RAWViteratorS_HPP