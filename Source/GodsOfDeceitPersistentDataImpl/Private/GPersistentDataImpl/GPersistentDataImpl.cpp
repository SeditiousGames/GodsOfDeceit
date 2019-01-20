/**
 * @file
 * @author  Mamadou Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mamadou Babaei
 * Copyright (c) 2018 - 2019 Seditious Games Studio
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Provides the low-level implementation for the persistent data module
 */


#include "GPersistentDataImpl/GPersistentDataImpl.h"

#include <sstream>
#include <utility>

#include <GHacks/GUndef_check.h>
THIRD_PARTY_INCLUDES_START
#include <boost/exception/diagnostic_information.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/regex.hpp>
THIRD_PARTY_INCLUDES_END
#include <GHacks/GRestore_check.h>

THIRD_PARTY_INCLUDES_START
#include <cereal/archives/json.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
THIRD_PARTY_INCLUDES_END

#include <GCompressionImpl/GCompressionImpl.h>
#include <GCryptoImpl/GCryptoImpl.h>
#include <GHacks/GInclude_Windows.h>
//#include <GPlatformImpl/GFilesSstemImpl.h>
#include <GPlatformImpl/GSystemImpl.h>
#include <GVersionImpl/GBuildInfoImpl.h>

//#include "GDatabase.h"

struct GPersistentDataImpl::Impl
{

};

GPersistentDataImpl::GPersistentDataImpl()
    : Pimpl(std::make_unique<GPersistentDataImpl::Impl>())
{

}

//GCryptoImpl& GPersistentDataImpl::GetCryptoInstance()
//{
//    static GCryptoImpl Instance(GPersistentDataImpl::Impl::GetSignKey());
//    return Instance;
//}

//GDatabaseImpl& GPersistentDataImpl::GetDatabaseInstance()
//{
//    static bool bInitialized = false;

//    return Instance;
//}

//GPersistentDataImpl::GameDataRecord& GPersistentDataImpl::GetGameData()
//{
//    return Pimpl->GameData;
//}
