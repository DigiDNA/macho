/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2020 Jean-David Gadina - www.xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        LoadDylib.cpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#include <MachO/LoadCommands/LoadDylib.hpp>
#include <MachO/Casts.hpp>

namespace MachO
{
    namespace LoadCommands
    {
        class LoadDylib::IMPL
        {
            public:
                
                IMPL( uint32_t command, uint32_t size, BinaryStream & stream );
                IMPL( const IMPL & o );
                ~IMPL();
                
                uint32_t    _command;
                uint32_t    _size;
                std::string _name;
                uint32_t    _timestamp;
                uint32_t    _currentVersion;
                uint32_t    _compatibilityVersion;
        };

        LoadDylib::LoadDylib( uint32_t command, uint32_t size, BinaryStream & stream ):
            impl( std::make_unique< IMPL >( command, size, stream ) )
        {}
        
        LoadDylib::LoadDylib( const LoadDylib & o ):
            impl( std::make_unique< IMPL >( *( o.impl ) ) )
        {}

        LoadDylib::LoadDylib( LoadDylib && o ) noexcept:
            impl( std::move( o.impl ) )
        {}

        LoadDylib::~LoadDylib()
        {}

        LoadDylib & LoadDylib::operator =( LoadDylib o )
        {
            swap( *( this ), o );
            
            return *( this );
        }
        
        uint32_t LoadDylib::command() const
        {
            return this->impl->_command;
        }
        
        uint32_t LoadDylib::size() const
        {
            return this->impl->_size;
        }
        
        std::string LoadDylib::name() const
        {
            return this->impl->_name;
        }
        
        uint32_t LoadDylib::timestamp() const
        {
            return this->impl->_timestamp;
        }
        
        uint32_t LoadDylib::currentVersion() const
        {
            return this->impl->_currentVersion;
        }
        
        uint32_t LoadDylib::compatibilityVersion() const
        {
            return this->impl->_compatibilityVersion;
        }
        
        void swap( LoadDylib & o1, LoadDylib & o2 )
        {
            using std::swap;
            
            swap( o1.impl, o2.impl );
        }
        
        LoadDylib::IMPL::IMPL( uint32_t command, uint32_t size, BinaryStream & stream ):
            _command( command ),
            _size(    size )
        {
            uint32_t offset( stream.readUInt32() );
            
            this->_timestamp            = stream.readUInt32();
            this->_currentVersion       = stream.readUInt32();
            this->_compatibilityVersion = stream.readUInt32();
            
            stream.seek( offset, BinaryStream::SeekDirection::Begin );
            
            this->_name = stream.readNULLTerminatedString();
        }
        
        LoadDylib::IMPL::IMPL( const IMPL & o ):
            _command(              o._command ),
            _size(                 o._size ),
            _name(                 o._name ),
            _timestamp(            o._timestamp ),
            _currentVersion(       o._currentVersion ),
            _compatibilityVersion( o._compatibilityVersion )
        {}

        LoadDylib::IMPL::~IMPL()
        {}
    }
}