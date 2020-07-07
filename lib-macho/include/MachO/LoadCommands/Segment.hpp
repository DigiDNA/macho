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
 * @header      Segment.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef MACHO_LOAD_COMMANDS_SEGMENT_HPP
#define MACHO_LOAD_COMMANDS_SEGMENT_HPP

#include <MachO/LoadCommand.hpp>
#include <MachO/BinaryStream.hpp>
#include <MachO/File.hpp>
#include <MachO/Section.hpp>
#include <string>
#include <vector>

namespace MachO
{
    namespace LoadCommands
    {
        class Segment: public LoadCommand
        {
            public:
                
                Segment( uint32_t command, uint32_t size, File::Kind kind, BinaryStream & stream  );
                Segment( const Segment & o );
                Segment( Segment && o ) noexcept;
                ~Segment() override;
                
                Segment & operator =( Segment o );
                
                Info getInfo() const override;
                
                uint32_t command() const override;
                uint32_t size()    const override;
                
                std::string name()             const;
                uint32_t    vmAddress()        const;
                uint32_t    vmSize()           const;
                uint32_t    fileOffset()       const;
                uint32_t    fileSize()         const;
                uint32_t    maxProtection()    const;
                uint32_t    initProtection()   const;
                uint32_t    flags()            const;
                
                std::vector< Section > sections() const;
                
                friend void swap( Segment & o1, Segment & o2 );
                
            private:
                
                class IMPL;
                
                std::unique_ptr< IMPL > impl;
        };
    }
}

#endif /* MACHO_LOAD_COMMANDS_SEGMENT_HPP */
