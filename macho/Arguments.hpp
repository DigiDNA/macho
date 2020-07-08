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
 * @header      Arguments.hpp
 * @copyright   (c) 2020, Jean-David Gadina - www.xs-labs.com
 */

#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <XS.hpp>

class Arguments: public XS::Info::Object
{
    public:
        
        Arguments( int argc, char ** argv );
        Arguments( const Arguments & o );
        Arguments( Arguments && o ) noexcept;
        ~Arguments() override;
        
        Arguments & operator =( Arguments o );
        
        XS::Info getInfo() const override;
        
        bool                       showHelp()     const;
        bool                       showInfo()     const;
        bool                       showLibs()     const;
        bool                       showCStrings() const;
        std::string                exec()         const;
        std::vector< std::string > files()        const;
        
        friend void swap( Arguments & o1, Arguments & o2 );
        
    private:
        
        class IMPL;
        
        std::unique_ptr< IMPL > impl;
};

#endif /* ARGUMENTS_HPP */
