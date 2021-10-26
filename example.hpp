#ifndef BL_RAWITERATORS_HPP
#define BL_RAWITERATORS_HPP


//-------------------------------------------------------------------
// Raw iterator with random access
//-------------------------------------------------------------------
template<typename Tt>
class Iterator : public std::iterator<std::random_access_iterator_tag,
                                           Tt,
                                           ptrdiff_t,
                                           Tt*,
                                           Tt&>
{
public:

    Iterator(Tt* ptr = nullptr){m_ptr = ptr;}
    Iterator(const Iterator<Tt>& rawIterator) = default;
    ~Iterator(){}

    Iterator<Tt>&                  operator=(const Iterator<Tt>& rawIterator) = default;
    Iterator<Tt>&                  operator=(Tt* ptr){m_ptr = ptr;return (*this);}

    operator                                    bool()const
    {
        if(m_ptr)
            return true;
        else
            return false;
    }

    bool                                        operator==(const Iterator<Tt>& rawIterator)const{return (m_ptr == rawIterator.getConstPtr());}
    bool                                        operator!=(const Iterator<Tt>& rawIterator)const{return (m_ptr != rawIterator.getConstPtr());}

    Iterator<Tt>&                  operator+=(const ptrdiff_t& movement){m_ptr += movement;return (*this);}
    Iterator<Tt>&                  operator-=(const ptrdiff_t& movement){m_ptr -= movement;return (*this);}
    Iterator<Tt>&                  operator++(){++m_ptr;return (*this);}
    Iterator<Tt>&                  operator--(){--m_ptr;return (*this);}
    Iterator<Tt>                   operator++(int){auto temp(*this);++m_ptr;return temp;}
    Iterator<Tt>                   operator--(int){auto temp(*this);--m_ptr;return temp;}
    Iterator<Tt>                   operator+(const ptrdiff_t& movement){auto oldPtr = m_ptr;m_ptr+=movement;auto temp(*this);m_ptr = oldPtr;return temp;}
    Iterator<Tt>                   operator-(const ptrdiff_t& movement){auto oldPtr = m_ptr;m_ptr-=movement;auto temp(*this);m_ptr = oldPtr;return temp;}

    ptrdiff_t       operator-(const Iterator<Tt>& rawIterator){return std::distance(rawIterator.getPtr(),this->getPtr());}

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
// Raw reverse iterator with random access
//-------------------------------------------------------------------
template<typename Tt>
class blRawReverseIterator : public Iterator<Tt>
{
public:

    blRawReverseIterator(Tt* ptr = nullptr):Iterator<Tt>(ptr){}
    blRawReverseIterator(const Iterator<Tt>& rawIterator){this->m_ptr = rawIterator.getPtr();}
    blRawReverseIterator(const blRawReverseIterator<Tt>& rawReverseIterator) = default;
    ~blRawReverseIterator(){}

    blRawReverseIterator<Tt>&           operator=(const blRawReverseIterator<Tt>& rawReverseIterator) = default;
    blRawReverseIterator<Tt>&           operator=(const Iterator<Tt>& rawIterator){this->m_ptr = rawIterator.getPtr();return (*this);}
    blRawReverseIterator<Tt>&           operator=(Tt* ptr){this->setPtr(ptr);return (*this);}

    blRawReverseIterator<Tt>&           operator+=(const ptrdiff_t& movement){this->m_ptr -= movement;return (*this);}
    blRawReverseIterator<Tt>&           operator-=(const ptrdiff_t& movement){this->m_ptr += movement;return (*this);}
    blRawReverseIterator<Tt>&           operator++(){--this->m_ptr;return (*this);}
    blRawReverseIterator<Tt>&           operator--(){++this->m_ptr;return (*this);}
    blRawReverseIterator<Tt>            operator++(int){auto temp(*this);--this->m_ptr;return temp;}
    blRawReverseIterator<Tt>            operator--(int){auto temp(*this);++this->m_ptr;return temp;}
    blRawReverseIterator<Tt>            operator+(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr-=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}
    blRawReverseIterator<Tt>            operator-(const int& movement){auto oldPtr = this->m_ptr;this->m_ptr+=movement;auto temp(*this);this->m_ptr = oldPtr;return temp;}

    ptrdiff_t                                   operator-(const blRawReverseIterator<Tt>& rawReverseIterator){return std::distance(this->getPtr(),rawReverseIterator.getPtr());}

    Iterator<Tt>                   base(){Iterator<Tt> forwardIterator(this->m_ptr); ++forwardIterator; return forwardIterator;}
};
//-------------------------------------------------------------------


#endif // BL_RAWITERATORS_HPP