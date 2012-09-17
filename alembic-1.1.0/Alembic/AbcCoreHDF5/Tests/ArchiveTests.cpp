//-*****************************************************************************
//
// Copyright (c) 2009-2012,
//  Sony Pictures Imageworks Inc. and
//  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Sony Pictures Imageworks, nor
// Industrial Light & Magic, nor the names of their contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-*****************************************************************************

#include <Alembic/AbcCoreAbstract/All.h>
#include <Alembic/AbcCoreHDF5/All.h>
#include <Alembic/Util/All.h>

#include <Alembic/AbcCoreAbstract/Tests/Assert.h>

#include <iostream>
#include <vector>

#include <hdf5.h>

//-*****************************************************************************
namespace A5 = Alembic::AbcCoreHDF5;

namespace ABC = Alembic::AbcCoreAbstract;

using ABC::chrono_t;
using Alembic::Util::float32_t;
using Alembic::Util::int32_t;
using Alembic::Util::byte_t;
using Alembic::Util::Dimensions;

//-*****************************************************************************

void testReadWriteEmptyArchive()
{
    std::string archiveName = "emptyArchive.abc";

    {
        A5::WriteArchive w;
        ABC::MetaData m;
        m.set("Bleep", "bloop");
        m.set("eep", "");
        m.set("potato", "salad");
        m.set("geoScope", "tasty");

        ABC::ArchiveWriterPtr a = w(archiveName, m);
        ABC::ObjectWriterPtr archive = a->getTop();

        TESTING_ASSERT(archive->getFullName() == "/");

        // use this to get current reporting mechanism, then supress it
        // since we expect to see H5F errors because we will be trying to open
        // a file that is already open for writing.
        H5E_auto_t func;
        void * client_data;
        H5Eget_auto2(H5E_DEFAULT, &func, &client_data);
        H5Eset_auto2(H5E_DEFAULT, NULL, NULL);

        // can't write an already open archive
        TESTING_ASSERT_THROW(w(archiveName, ABC::MetaData()),
            Alembic::Util::Exception);

        Alembic::AbcCoreHDF5::ReadArchive r;

        // can't read an already open archive
        TESTING_ASSERT_THROW(r( archiveName ), Alembic::Util::Exception);

        // turn the error reporting back on for later tests
        H5Eset_auto2(H5E_DEFAULT, func, client_data);

    }

    {
        A5::ReadArchive r;
        ABC::ArchiveReaderPtr a = r( archiveName );
        ABC::ObjectReaderPtr archive = a->getTop();
        ABC::MetaData m = archive->getHeader().getMetaData();
        TESTING_ASSERT(m.get("Bleep") == "bloop");
        TESTING_ASSERT(m.get("eep") == "");
        TESTING_ASSERT(m.get("potato") == "salad");
        TESTING_ASSERT(m.get("geoScope") == "tasty");
        TESTING_ASSERT(archive->getName() == "ABC");
        TESTING_ASSERT(archive->getFullName() == "/");
        TESTING_ASSERT(archive->getParent() == NULL);
        TESTING_ASSERT(archive->getNumChildren() == 0);

        // even though we didn't write anything make sure we intrincially have
        // the default sampling
        TESTING_ASSERT(a->getNumTimeSamplings() == 1);
        TESTING_ASSERT(*(a->getTimeSampling(0)) == ABC::TimeSampling());

        ABC::CompoundPropertyReaderPtr parent = archive->getProperties();
        TESTING_ASSERT(parent->getNumProperties() == 0);

        // get it again to make sure we clean ourselves up properly
        A5::ReadArchive r2;
        ABC::ArchiveReaderPtr a2 = r2( archiveName );
        ABC::ObjectReaderPtr archive2 = a2->getTop();
        ABC::CompoundPropertyReaderPtr p2 = archive2->getProperties();
        TESTING_ASSERT(p2->getNumProperties() == 0);
    }
}

void testReadWriteTimeSamplingArchive()
{
    std::string archiveName = "timeSampsArchive.abc";

    {
        A5::WriteArchive w;
        ABC::ArchiveWriterPtr a = w(archiveName, ABC::MetaData());

        // we always have 1
        TESTING_ASSERT(a->getNumTimeSamplings() == 1);

        // getting a time sampling that doesn't exist should throw
        TESTING_ASSERT_THROW(a->getTimeSampling(43),
            Alembic::Util::Exception);

        // first one is the default time sampling
        TESTING_ASSERT(*(a->getTimeSampling(0)) == ABC::TimeSampling());

        std::vector< double > samps;

        // uniform sampling starts at second 34, 24fps
        samps.push_back(34.0);
        ABC::TimeSampling ts(ABC::TimeSamplingType(1.0/24.0), samps);
        uint32_t index = a->addTimeSampling(ts);
        TESTING_ASSERT(index == 1);

        // even though we add the same thing, we get the same index back
        index = a->addTimeSampling(ts);
        TESTING_ASSERT(index == 1);

        // cyclic sampling example
        samps.push_back(34.25);
        samps.push_back(34.5);
        ts = ABC::TimeSampling(ABC::TimeSamplingType(3, 1.0), samps);
        index = a->addTimeSampling(ts);
        TESTING_ASSERT(index == 2);

        // really weird acyclic example
        samps.push_back(300.0);
        samps.push_back(500.0);
        ts = ABC::TimeSampling(
            ABC::TimeSamplingType(ABC::TimeSamplingType::kAcyclic), samps);
        index = a->addTimeSampling(ts);
        TESTING_ASSERT(index == 3);

        // now we should have 4
        TESTING_ASSERT(a->getNumTimeSamplings() == 4);
    }

    {
        A5::ReadArchive r;
        ABC::ArchiveReaderPtr a = r( archiveName );

        TESTING_ASSERT(a->getNumTimeSamplings() == 4);

        // first one is the default time sampling
        TESTING_ASSERT(*(a->getTimeSampling(0)) == ABC::TimeSampling());

        std::vector< double > samps;

        // uniform sampling starts at second 34, 24fps
        samps.push_back(34.0);
        ABC::TimeSampling ts(ABC::TimeSamplingType(1.0/24.0), samps);
        TESTING_ASSERT( ts == *(a->getTimeSampling(1)) );

        // cyclic sampling example
        samps.push_back(34.25);
        samps.push_back(34.5);
        ts = ABC::TimeSampling(ABC::TimeSamplingType(3, 1.0), samps);
        TESTING_ASSERT( ts == *(a->getTimeSampling(2)) );

        // really weird acyclic example
        samps.push_back(300.0);
        samps.push_back(500.0);
        ts = ABC::TimeSampling(
            ABC::TimeSamplingType(ABC::TimeSamplingType::kAcyclic), samps);
        TESTING_ASSERT( ts == *(a->getTimeSampling(3)) );
    }
}

void writeArchive( const std::string & iName, bool iCache )
{
    ABC::MetaData m;
    ABC::ObjectHeader header("a", m);
    A5::WriteArchive w( iCache );
    ABC::ArchiveWriterPtr a = w(iName, m );
    ABC::ObjectWriterPtr root = a->getTop();
    std::vector< ABC::ObjectWriterPtr > objVec;

    objVec.push_back(root);
    objVec.push_back(root->createChild(header));
    header.setName("b");
    objVec.push_back(root->createChild(header));

    // add some number of objects to the existing ones (that aren't the root)
    int numObjs = objVec.size();
    for (int i = 1; i < numObjs; ++i)
    {
        header.setName("a");
        objVec.push_back(objVec[i]->createChild(header));
        header.setName("b");
        objVec.push_back(objVec[i]->createChild(header));
        header.setName("c");
        objVec.push_back(objVec[i]->createChild(header));
    }

    ABC::DataType i32d(Alembic::Util::kInt32POD, 1);

    // let's add 3 array properties to EVERY object
    for (std::size_t i = 0; i < objVec.size(); ++i)
    {
        ABC::CompoundPropertyWriterPtr top = objVec[i]->getProperties();
        std::vector<ABC::ArrayPropertyWriterPtr> props;
        props.push_back(top->createArrayProperty("a", m, i32d, 0));
        props.push_back(top->createArrayProperty("b", m, i32d, 0));
        props.push_back(top->createArrayProperty("c", m, i32d, 0));

        for (std::size_t i = 1; i < props.size(); ++i)
        {
            std::vector <Alembic::Util::int32_t> vali(i, 0);
            Alembic::Util::Dimensions dims(i);
            for (std::size_t j = i; j < props.size(); ++j)
            {
                props[j]->setSample(
                    ABC::ArraySample(&(vali.front()), i32d, dims));
            }
        }
    }
}

void readArchive( const std::string & iName, bool iCache )
{
    Alembic::AbcCoreHDF5::ReadArchive r( iCache );
    ABC::ArchiveReaderPtr a = r( iName );
    std::vector< ABC::ObjectReaderPtr > objs;
    objs.push_back( a->getTop() );
    TESTING_ASSERT( objs[0]->getNumChildren() == 2 );
    objs.push_back( objs[0]->getChild(0) );
    objs.push_back( objs[0]->getChild(1) );

    std::size_t numObjs = objs.size();
    for (std::size_t i = 1; i < numObjs; ++i)
    {
        TESTING_ASSERT( objs[i]->getNumChildren() == 3 );
        for (std::size_t j = 0; j < numObjs; ++j)
        {
            objs.push_back( objs[i]->getChild(j) );
        }
    }

    for (std::size_t i = 0; i < objs.size(); ++i)
    {
        TESTING_ASSERT( objs[i]->getProperties()->getNumProperties() == 3 );

        ABC::CompoundPropertyReaderPtr cpr = objs[i]->getProperties();
        ABC::ArrayPropertyReaderPtr apr = cpr->getArrayProperty("a");

        TESTING_ASSERT( 0 ==
            objs[i]->getProperties()->getArrayProperty("a")->getNumSamples() );
        TESTING_ASSERT( 1 ==
            objs[i]->getProperties()->getArrayProperty("b")->getNumSamples() );
        TESTING_ASSERT( 2 ==
            objs[i]->getProperties()->getArrayProperty("c")->getNumSamples() );
    }
}

void writeVeryEmptyArchive( const std::string & iName, bool iCache )
{
    ABC::MetaData m;
    A5::WriteArchive w( iCache );
    ABC::ArchiveWriterPtr a = w(iName, m);
}

void readVeryEmptyArchive( const std::string & iName, bool iCache )
{
    Alembic::AbcCoreHDF5::ReadArchive r( iCache );
    ABC::ArchiveReaderPtr a = r( iName );
    TESTING_ASSERT(a->getTop()->getNumChildren() == 0);
}

int main ( int argc, char *argv[] )
{
    testReadWriteEmptyArchive();
    testReadWriteTimeSamplingArchive();

    writeArchive("noCacheTest.abc", false);
    readArchive("noCacheTest.abc", false);
    readArchive("noCacheTest.abc", true);

    writeArchive("cacheTest.abc", true);
    readArchive("cacheTest.abc", false);
    readArchive("cacheTest.abc", true);

    writeVeryEmptyArchive("noCacheTestEmpty.abc", false);
    readVeryEmptyArchive("noCacheTestEmpty.abc", false);
    readVeryEmptyArchive("noCacheTestEmpty.abc", true);

    writeVeryEmptyArchive("cacheTestEmpty.abc", true);
    readVeryEmptyArchive("cacheTestEmpty.abc", false);
    readVeryEmptyArchive("cacheTestEmpty.abc", true);

    return 0;
}
