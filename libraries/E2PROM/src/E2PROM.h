/*
  EEPROM.h - EEPROM library
  Original Copyright (c) 2006 David A. Mellis.  All right reserved.
  New version by Christopher Andrews 2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef E2PROM_h
#define E2PROM_h

#include <inttypes.h>
#include <BR24T512.h>


#define E2END 65535


/***
    E2Ref class.
    
    This object references an EEPROM cell.
    Its purpose is to mimic a typical byte of RAM, however its storage is the EEPROM.
    This class has an overhead of two bytes, similar to storing a pointer to an EEPROM cell.
***/

struct E2Ref{

    E2Ref( const int index )
        : index( index )                 {}
    
    //Access/read members.
    uint8_t operator*() const            { return br24t512.read(index); }
    operator uint8_t() const             { return **this; }
    
    //Assignment/write members.
    E2Ref &operator=( const E2Ref &ref ) { return *this = *ref; }
    E2Ref &operator=( uint8_t in )       { return br24t512.write(index, in), *this;  }
    E2Ref &operator +=( uint8_t in )     { return *this = **this + in; }
    E2Ref &operator -=( uint8_t in )     { return *this = **this - in; }
    E2Ref &operator *=( uint8_t in )     { return *this = **this * in; }
    E2Ref &operator /=( uint8_t in )     { return *this = **this / in; }
    E2Ref &operator ^=( uint8_t in )     { return *this = **this ^ in; }
    E2Ref &operator %=( uint8_t in )     { return *this = **this % in; }
    E2Ref &operator &=( uint8_t in )     { return *this = **this & in; }
    E2Ref &operator |=( uint8_t in )     { return *this = **this | in; }
    E2Ref &operator <<=( uint8_t in )    { return *this = **this << in; }
    E2Ref &operator >>=( uint8_t in )    { return *this = **this >> in; }
    
    E2Ref &update( uint8_t in )          { return  in != *this ? *this = in : *this; }
    
    /** Prefix increment/decrement **/
    E2Ref& operator++()                  { return *this += 1; }
    E2Ref& operator--()                  { return *this -= 1; }
    
    /** Postfix increment/decrement **/
    uint8_t operator++ (int){ 
        uint8_t ret = **this;
        return ++(*this), ret;
    }

    uint8_t operator-- (int){ 
        uint8_t ret = **this;
        return --(*this), ret;
    }
    
    int index; //Index of current EEPROM cell.
};

/***
    EEPtr class.
    
    This object is a bidirectional pointer to EEPROM cells represented by E2Ref objects.
    Just like a normal pointer type, this can be dereferenced and repositioned using 
    increment/decrement operators.
***/

struct EEPtr{

    EEPtr( const int index )
        : index( index )                {}
        
    operator int() const                { return index; }
    EEPtr &operator=( int in )          { return index = in, *this; }
    
    //Iterator functionality.
    bool operator!=( const EEPtr &ptr ) { return index != ptr.index; }
    E2Ref operator*()                   { return index; }
    
    /** Prefix & Postfix increment/decrement **/
    EEPtr& operator++()                 { return ++index, *this; }
    EEPtr& operator--()                 { return --index, *this; }
    EEPtr operator++ (int)              { return index++; }
    EEPtr operator-- (int)              { return index--; }

    int index; //Index of current EEPROM cell.
};

/***
    EEPROMClass class.
    
    This object represents the entire EEPROM space.
    It wraps the functionality of EEPtr and E2Ref into a basic interface.
    This class is also 100% backwards compatible with earlier Arduino core releases.
***/

struct E2PROMClass{

    //Basic user access methods.
    E2Ref operator[]( const int idx )    { return idx; }
    uint8_t read( int idx )              { return E2Ref( idx ); }
    void write( int idx, uint8_t val )   { (E2Ref( idx )) = val; }
    void update( int idx, uint8_t val )  { E2Ref( idx ).update( val ); }
    
    //STL and C++11 iteration capability.
    EEPtr begin()                        { br24t512.begin(); return  0x00; }
    EEPtr end()                          { return length(); } //Standards requires this to be the item after the last valid entry. The returned pointer is invalid.
    uint16_t length()                    { return E2END; }
    
    //Functionality to 'get' and 'put' objects to and from EEPROM.
    template< typename T > T &get( int idx, T &t ){
        EEPtr e = idx;
        uint8_t *ptr = (uint8_t*) &t;
        for( int count = sizeof(T) ; count ; --count, ++e )  *ptr++ = *e;
        return t;
    }
    
    template< typename T > const T &put( int idx, const T &t ){
        EEPtr e = idx;
        const uint8_t *ptr = (const uint8_t*) &t;
        for( int count = sizeof(T) ; count ; --count, ++e )  (*e).update( *ptr++ );
        return t;
    }
};

static E2PROMClass E2PROM;
#endif
