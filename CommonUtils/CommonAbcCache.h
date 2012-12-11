#ifndef __COMMON_ABC_CACHE_H__
#define __COMMON_ABC_CACHE_H__


#include <boost/smart_ptr.hpp>

typedef boost::shared_ptr<AbcG::IXform> IXformPtr;

class AbcObjectCache {
protected:

public:
	AbcObjectCache( Alembic::Abc::IObject & objToCache );
    ~AbcObjectCache();

    //AbcObjectCache(const AbcObjectCache& cache);
    //AbcObjectCache& operator=(const AbcObjectCache& cache);

	Abc::IObject obj;
	int numSamples;
	bool isConstant;
	bool isMeshPointCache;
	bool isMeshTopoDynamic;
	std::vector<std::string> childIdentifiers;
	std::string fullName;
	std::string parentIdentifier;

    IXformPtr getXform();
    Abc::M44d getXformMatrix(int index);
private:
    IXformPtr pObjXform;
    std::vector<Abc::M44d> iXformVec;
};

typedef std::map<std::string,AbcObjectCache> AbcArchiveCache;

void createAbcArchiveCache( Abc::IArchive *pArchive, AbcArchiveCache* fullNameToObjectCache );

#endif // __COMMON_ABC_CACHE_H__