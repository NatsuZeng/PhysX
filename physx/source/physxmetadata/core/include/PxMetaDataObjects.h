//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2018 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.

#ifndef PX_METADATAOBJECTS_H
#define PX_METADATAOBJECTS_H
#include "foundation/PxMemory.h"

// include the base headers instead of the PxPhysicsAPI.h
//Geometry Library
#include "geometry/PxBoxGeometry.h"
#include "geometry/PxCapsuleGeometry.h"
#include "geometry/PxConvexMesh.h"
#include "geometry/PxConvexMeshGeometry.h"
#include "geometry/PxGeometry.h"
#include "geometry/PxGeometryHelpers.h"
#include "geometry/PxGeometryQuery.h"
#include "geometry/PxHeightField.h"
#include "geometry/PxHeightFieldDesc.h"
#include "geometry/PxHeightFieldFlag.h"
#include "geometry/PxHeightFieldGeometry.h"
#include "geometry/PxHeightFieldSample.h"
#include "geometry/PxMeshQuery.h"
#include "geometry/PxMeshScale.h"
#include "geometry/PxPlaneGeometry.h"
#include "geometry/PxSimpleTriangleMesh.h"
#include "geometry/PxSphereGeometry.h"
#include "geometry/PxTriangle.h"
#include "geometry/PxTriangleMesh.h"
#include "geometry/PxTriangleMeshGeometry.h"

// PhysX Core SDK
#include "PxActor.h"
#include "PxAggregate.h"
#include "PxArticulation.h"
#include "PxArticulationJoint.h"
#include "PxArticulationReducedCoordinate.h"
#include "PxArticulationJointReducedCoordinate.h"
#include "PxArticulationLink.h"
#include "PxBatchQuery.h"
#include "PxBatchQueryDesc.h"
#include "PxClient.h"
#include "PxConstraint.h"
#include "PxConstraintDesc.h"
#include "PxContact.h"
#include "PxContactModifyCallback.h"
#include "PxDeletionListener.h"
#include "PxFiltering.h"
#include "PxForceMode.h"
#include "PxLockedData.h"
#include "PxMaterial.h"
#include "PxPhysics.h"
#include "PxPhysicsVersion.h"
#include "PxPhysXConfig.h"
#include "PxQueryFiltering.h"
#include "PxQueryReport.h"
#include "PxRigidActor.h"
#include "PxRigidBody.h"
#include "PxRigidDynamic.h"
#include "PxRigidStatic.h"
#include "PxScene.h"
#include "PxSceneDesc.h"
#include "PxSceneLock.h"
#include "PxShape.h"
#include "PxSimulationEventCallback.h"
#include "PxSimulationStatistics.h"
#include "PxVisualizationParameter.h"
#include "PxPruningStructure.h"


/** \addtogroup physics
@{
*/

namespace physx
{

class PxArticulationLink;
class PxArticulationJoint;
class PxArticulationJointReducedCoordinate;
class PxArticulationJointBase;

struct PxPropertyInfoName
{
	enum Enum
	{
		Unnamed = 0,
#include "PxAutoGeneratedMetaDataObjectNames.h"
		LastPxPropertyInfoName
	};
};

struct PxU32ToName
{
	const char* mName;
	PxU32		mValue;
};

struct PxPropertyInfoBase
{
	const char* mName;
	PxU32 mKey; 
	PxPropertyInfoBase( const char* n, PxU32 inKey )
		: mName( n )
		, mKey( inKey )
	{
	}
};

template<PxU32 TKey>
struct PxPropertyInfoParameterizedBase : public PxPropertyInfoBase
{
	PxPropertyInfoParameterizedBase( const char* inName )
		: PxPropertyInfoBase( inName, TKey ) {}
};

template<PxU32 TKey, typename TObjType, typename TPropertyType>
struct PxReadOnlyPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef TPropertyType (*TGetterType)( const TObjType* );
	TGetterType mGetter;
	PxReadOnlyPropertyInfo( const char* inName, TGetterType inGetter )
		: PxPropertyInfoParameterizedBase<TKey>( inName )
		, mGetter( inGetter ) {}
	TPropertyType get( const TObjType* inObj ) const { return mGetter( inObj ); }
};

template<PxU32 TKey, typename TObjType, typename TPropertyType>
struct PxWriteOnlyPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef void(*TSetterType)( TObjType*, TPropertyType inArg );
	TSetterType mSetter;
	PxWriteOnlyPropertyInfo( const char* inName, TSetterType inSetter )
		: PxPropertyInfoParameterizedBase<TKey>( inName )
		, mSetter( inSetter ) {}
	void set( TObjType* inObj, TPropertyType inArg ) const { mSetter( inObj, inArg ); }
};


//Define the property types on the auto-generated objects.
template<PxU32 TKey, typename TObjType, typename TSetPropType, typename TGetPropType>
struct PxPropertyInfo : public PxReadOnlyPropertyInfo<TKey, TObjType, TGetPropType>
{
	typedef typename PxReadOnlyPropertyInfo<TKey, TObjType, TGetPropType>::TGetterType TGetterType;
	typedef void(*TSetterType)( TObjType*, TSetPropType inArg );
	TSetterType mSetter;

	PxPropertyInfo( const char* inName, TSetterType inSetter, TGetterType inGetter )
		: PxReadOnlyPropertyInfo<TKey, TObjType, TGetPropType>( inName, inGetter )
		, mSetter( inSetter ) {}
	void set( TObjType* inObj, TSetPropType inArg ) const { mSetter( inObj, inArg ); }
};

template<PxU32 TKey, typename TObjType, typename TPropertyType>
struct PxRangePropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef void (*TSetterType)( TObjType*,TPropertyType,TPropertyType);
	typedef void (*TGetterType)( const TObjType*,TPropertyType&,TPropertyType&);

	const char* mArg0Name;
	const char* mArg1Name;

	TSetterType mSetter;
	TGetterType mGetter;

	PxRangePropertyInfo( const char* name, const char* arg0Name, const char* arg1Name
							, TSetterType setter, TGetterType getter )
		: PxPropertyInfoParameterizedBase<TKey>( name )
		, mArg0Name( arg0Name )
		, mArg1Name( arg1Name )
		, mSetter( setter )
		, mGetter( getter )
	{
	}
	void set( TObjType* inObj, TPropertyType arg0, TPropertyType arg1 ) const { mSetter( inObj, arg0, arg1 ); }
	void get( const TObjType* inObj, TPropertyType& arg0, TPropertyType& arg1 ) const { mGetter( inObj, arg0, arg1 ); }
};

template<PxU32 TKey, typename TObjType, typename TIndexType, typename TPropertyType>
struct PxIndexedPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef void (*TSetterType)( TObjType*, TIndexType, TPropertyType );
	typedef TPropertyType (*TGetterType)( const TObjType* inObj, TIndexType );

	TSetterType mSetter;
	TGetterType mGetter;

	PxIndexedPropertyInfo( const char* name, TSetterType setter, TGetterType getter )
		: PxPropertyInfoParameterizedBase<TKey>( name )
		, mSetter( setter )
		, mGetter( getter )
	{
	}
	void set( TObjType* inObj, TIndexType inIndex, TPropertyType arg ) const { mSetter( inObj, inIndex, arg ); }
	TPropertyType get( const TObjType* inObj, TIndexType inIndex ) const { return mGetter( inObj, inIndex ); }
};

template<PxU32 TKey, typename TObjType, typename TIndexType, typename TPropertyType>
struct PxExtendedIndexedPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef PxU32 (*TNbObjectsMember)( const TObjType* );
	typedef void (*TSetterType)( TObjType*, TIndexType, TPropertyType );
	typedef TPropertyType (*TGetterType)( const TObjType* inObj, TIndexType );

	TSetterType mSetter;
	TGetterType mGetter;
    PxU32       mCount;
	TNbObjectsMember	mNbObjectsMember;

	PxExtendedIndexedPropertyInfo( const char* name, TGetterType getter, TNbObjectsMember inNb, TSetterType setter)
		: PxPropertyInfoParameterizedBase<TKey>( name )
		, mSetter( setter )
		, mGetter( getter )
        , mNbObjectsMember( inNb )
	{
	}

	PxU32 size( const TObjType* inObj ) const { return mNbObjectsMember( inObj ); }
	void set( TObjType* inObj, TIndexType inIndex, TPropertyType arg ) const { mSetter( inObj, inIndex, arg ); }
	TPropertyType get( const TObjType* inObj, TIndexType inIndex ) const { return mGetter( inObj, inIndex ); }
};

template<PxU32 TKey, typename TObjType, typename TIndex1Type, typename TIndex2Type, typename TPropertyType>
struct PxDualIndexedPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef void (*TSetterType)( TObjType*, TIndex1Type, TIndex2Type, TPropertyType );
	typedef TPropertyType (*TGetterType)( const TObjType* inObj, TIndex1Type, TIndex2Type );

	TSetterType mSetter;
	TGetterType mGetter;

	PxDualIndexedPropertyInfo( const char* name, TSetterType setter, TGetterType getter )
		: PxPropertyInfoParameterizedBase<TKey>( name )
		, mSetter( setter )
		, mGetter( getter )
	{
	}
	void set( TObjType* inObj, TIndex1Type inIdx1, TIndex2Type inIdx2, TPropertyType arg ) const { mSetter( inObj, inIdx1, inIdx2, arg ); }
	TPropertyType get( const TObjType* inObj, TIndex1Type inIdx1, TIndex2Type inIdx2 ) const { return mGetter( inObj, inIdx1, inIdx2 ); }
};

template<PxU32 TKey, typename TObjType, typename TIndex1Type, typename TIndex2Type, typename TPropertyType>
struct PxExtendedDualIndexedPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef void (*TSetterType)( TObjType*, TIndex1Type, TIndex2Type, TPropertyType );
	typedef TPropertyType (*TGetterType)( const TObjType* inObj, TIndex1Type, TIndex2Type );

	TSetterType mSetter;
	TGetterType mGetter;
	PxU32		mId0Count;
	PxU32		mId1Count;

	PxExtendedDualIndexedPropertyInfo( const char* name, TSetterType setter, TGetterType getter, PxU32 id0Count, PxU32 id1Count )
		: PxPropertyInfoParameterizedBase<TKey>( name )
		, mSetter( setter )
		, mGetter( getter )
		, mId0Count( id0Count )
		, mId1Count( id1Count )
	{
	}

	void set( TObjType* inObj, TIndex1Type inIdx1, TIndex2Type inIdx2, TPropertyType arg ) const { mSetter( inObj, inIdx1, inIdx2, arg ); }
	TPropertyType get( const TObjType* inObj, TIndex1Type inIdx1, TIndex2Type inIdx2 ) const { return mGetter( inObj, inIdx1, inIdx2 ); }
};

template<PxU32 TKey, typename TObjType, typename TCollectionType>
struct PxBufferCollectionPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef PxU32 (*TNbObjectsMember)( const TObjType* );
	typedef PxU32 (*TGetObjectsMember)( const TObjType*, TCollectionType*, PxU32 );
	typedef void (*TSetObjectsMember)( TObjType*, TCollectionType*, PxU32 );
	
	TGetObjectsMember	mGetObjectsMember;
	TNbObjectsMember	mNbObjectsMember;
	TSetObjectsMember	mSetObjectsMember;
	
	PxBufferCollectionPropertyInfo( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb, TSetObjectsMember inSet )
		: PxPropertyInfoParameterizedBase<TKey>( inName )
		, mGetObjectsMember( inGetter )
		, mNbObjectsMember( inNb )
		, mSetObjectsMember( inSet )
	{
	}
	PxU32 size( const TObjType* inObj ) const { return mNbObjectsMember( inObj ); }
	PxU32 get( const TObjType* inObj, TCollectionType* inBuffer, PxU32 inNumItems ) const { return mGetObjectsMember( inObj, inBuffer, inNumItems ); }
	void set( TObjType* inObj, TCollectionType* inBuffer, PxU32 inNumItems ) const { mSetObjectsMember( inObj, inBuffer, inNumItems); }
};

template<PxU32 TKey, typename TObjType, typename TIndexType, typename TPropertyType>
struct PxFixedSizeLookupTablePropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef PxU32 (*TNbObjectsMember)( const TObjType* );
	typedef PxReal (*TGetXMember)( const TObjType*, PxU32 );
	typedef PxReal (*TGetYMember)( const TObjType*, PxU32 );
	typedef void (*TAddPairMember)( TObjType*, PxReal, PxReal );
	typedef void (*TClearMember)( TObjType* );

	TGetXMember			mGetXMember;
	TGetYMember			mGetYMember;
	TNbObjectsMember	mNbObjectsMember;
	TAddPairMember		mAddPairMember;
	TClearMember		mClearMember;

	PxFixedSizeLookupTablePropertyInfo( const char* inName, TGetXMember inGetterX, TGetYMember inGetterY, TNbObjectsMember inNb, TAddPairMember inAddPair, TClearMember inClear )
		: PxPropertyInfoParameterizedBase<TKey>( inName )
		, mGetXMember( inGetterX )
		, mGetYMember( inGetterY )
		, mNbObjectsMember( inNb )
		, mAddPairMember( inAddPair )
		, mClearMember( inClear )
		
	{
	}
	PxU32 size( const TObjType* inObj ) const { return mNbObjectsMember( inObj ); }
	PxReal getX( const TObjType* inObj, const PxU32 index )  const { return mGetXMember( inObj, index ); }
	PxReal getY( const TObjType* inObj, const PxU32 index )  const { return mGetYMember( inObj, index ); }
	void addPair( TObjType* inObj, const PxReal x, const PxReal y ) { mAddPairMember( inObj, x, y );  }
	void clear( TObjType* inObj ) { mClearMember( inObj );  }
};

template<PxU32 TKey, typename TObjType, typename TCollectionType>
struct PxReadOnlyCollectionPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef PxU32 (*TNbObjectsMember)( const TObjType* );
	typedef PxU32 (*TGetObjectsMember)( const TObjType*, TCollectionType*, PxU32 );

	TGetObjectsMember	mGetObjectsMember;
	TNbObjectsMember	mNbObjectsMember;

	PxReadOnlyCollectionPropertyInfo( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb )
		: PxPropertyInfoParameterizedBase<TKey>( inName )
		, mGetObjectsMember( inGetter )
		, mNbObjectsMember( inNb )
	{
	}
	PxU32 size( const TObjType* inObj ) const { return mNbObjectsMember( inObj ); }
	PxU32 get( const TObjType* inObj, TCollectionType* inBuffer, PxU32 inBufSize ) const { return mGetObjectsMember( inObj, inBuffer, inBufSize); }
};


template<PxU32 TKey, typename TObjType, typename TCollectionType, typename TFilterType>
struct PxReadOnlyFilteredCollectionPropertyInfo : public PxPropertyInfoParameterizedBase<TKey>
{
	typedef PxU32 (*TNbObjectsMember)( const TObjType*, TFilterType );
	typedef PxU32 (*TGetObjectsMember)( const TObjType*, TFilterType, TCollectionType*, PxU32 );

	TGetObjectsMember	mGetObjectsMember;
	TNbObjectsMember	mNbObjectsMember;

	PxReadOnlyFilteredCollectionPropertyInfo( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb )
		: PxPropertyInfoParameterizedBase<TKey>( inName )
		, mGetObjectsMember( inGetter )
		, mNbObjectsMember( inNb )
	{
	}

	PxU32 size( const TObjType* inObj, TFilterType inFilter ) const { return mNbObjectsMember( inObj, inFilter ); }
	PxU32 get( const TObjType* inObj, TFilterType inFilter, TCollectionType* inBuffer, PxU32 inBufSize ) const { return mGetObjectsMember( inObj, inFilter, inBuffer, inBufSize); }
};

template<PxU32 TKey, typename TObjType, typename TCollectionType, typename TCreateArg>
struct PxFactoryCollectionPropertyInfo : public PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >
{
	typedef typename PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >::TGetObjectsMember TGetObjectsMember;
	typedef typename PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >::TNbObjectsMember TNbObjectsMember;
	typedef TCollectionType (*TCreateMember)( TObjType*, TCreateArg );

	TCreateMember mCreateMember;
	PxFactoryCollectionPropertyInfo( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb, TCreateMember inMember )
		: PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >( inName, inGetter, inNb )
		, mCreateMember( inMember )
	{
	}
	TCollectionType create( TObjType* inObj, TCreateArg inArg ) const { return mCreateMember( inObj, inArg ); }
};


template<PxU32 TKey, typename TObjType, typename TCollectionType>
struct PxCollectionPropertyInfo : public PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >
{
	typedef typename PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >::TGetObjectsMember TGetObjectsMember;
	typedef typename PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >::TNbObjectsMember TNbObjectsMember;
	typedef void (*TAddMember)(TObjType*, TCollectionType&);
	typedef void (*TRemoveMember)(TObjType*, TCollectionType&);

	TAddMember		mAddMember;
	TRemoveMember	mRemoveMember;

	PxCollectionPropertyInfo( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb, TAddMember inMember, TRemoveMember inRemoveMember )
		: PxReadOnlyCollectionPropertyInfo< TKey, TObjType, TCollectionType >( inName, inGetter, inNb )
		, mAddMember( inMember )
		, mRemoveMember( inRemoveMember )
	{
	}
	void add( TObjType* inObj, TCollectionType& inArg ) const { mAddMember(inObj, inArg ); }
	void remove( TObjType* inObj, TCollectionType& inArg ) const { mRemoveMember( inObj, inArg ); }
};

template<PxU32 TKey, typename TObjType, typename TCollectionType, typename TFilterType>
struct PxFilteredCollectionPropertyInfo : public PxReadOnlyFilteredCollectionPropertyInfo<TKey, TObjType, TCollectionType, TFilterType>
{
	typedef typename PxReadOnlyFilteredCollectionPropertyInfo< TKey, TObjType, TCollectionType, TFilterType >::TGetObjectsMember TGetObjectsMember;
	typedef typename PxReadOnlyFilteredCollectionPropertyInfo< TKey, TObjType, TCollectionType, TFilterType >::TNbObjectsMember TNbObjectsMember;
	typedef void (*TAddMember)(TObjType*, TCollectionType&);
	typedef void (*TRemoveMember)(TObjType*, TCollectionType&);

	TAddMember		mAddMember;
	TRemoveMember	mRemoveMember;

	PxFilteredCollectionPropertyInfo( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb, TAddMember inMember, TRemoveMember inRemoveMember )
		: PxReadOnlyFilteredCollectionPropertyInfo<TKey, TObjType, TCollectionType, TFilterType>( inName, inGetter, inNb )
		, mAddMember( inMember )
		, mRemoveMember( inRemoveMember )
	{
	}
	void add( TObjType* inObj, TCollectionType& inArg ) const { mAddMember(inObj, inArg ); }
	void remove( TObjType* inObj, TCollectionType& inArg ) const { mRemoveMember( inObj, inArg ); }
};

//create a default info class for when we can't match
//the type correctly.
struct PxUnknownClassInfo
{
	static const char* getClassName() { return "__unknown_class"; }
	template<typename TReturnType, typename TOperator>
	TReturnType visitType( TOperator )
	{
		return TReturnType();
	}
	template<typename TOperator>
	void visitBases( TOperator )
	{
	}
	template<typename TOperator>
	PxU32 visitBaseProperties( TOperator, PxU32 inStartIndex = 0 ) const
	{
		return inStartIndex;
	}
	template<typename TOperator>
	PxU32 visitInstanceProperties( TOperator, PxU32 inStartIndex = 0 ) const
	{
		return inStartIndex;
	}
};

template<typename TDataType>
struct PxClassInfoTraits
{
	PxUnknownClassInfo Info;
	static bool getInfo()  { return false;}	
};

//move the bool typedef to the global namespace.
typedef bool _Bool;


template<PxU32 TPropertyName>
struct PxPropertyToValueStructMemberMap
{
	bool Offset;
};


#define DEFINE_PROPERTY_TO_VALUE_STRUCT_MAP( type, prop, valueStruct )																	\
	template<> struct PxPropertyToValueStructMemberMap< PxPropertyInfoName::type##_##prop >												\
	{																																	\
		PxU32 Offset;																													\
		PxPropertyToValueStructMemberMap< PxPropertyInfoName::type##_##prop >() : Offset( PX_OFFSET_OF_RT( valueStruct, prop ) ) {}		\
		template<typename TOperator> void visitProp( TOperator inOperator, valueStruct& inStruct ) { inOperator( inStruct.prop );	}	\
	};
	


struct PxShapeGeometryPropertyHelper
{
	PX_PHYSX_CORE_API PxGeometryType::Enum getGeometryType(const PxShape* inShape) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxBoxGeometry& geometry) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxSphereGeometry& geometry) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxCapsuleGeometry& geometry) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxPlaneGeometry& geometry) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxConvexMeshGeometry& geometry) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxTriangleMeshGeometry& geometry) const;
	PX_PHYSX_CORE_API bool getGeometry(const PxShape* inShape, PxHeightFieldGeometry& geometry) const;
};


struct PxShapeGeometryProperty : public PxWriteOnlyPropertyInfo< PxPropertyInfoName::PxShape_Geometry, PxShape, const PxGeometry & >
								, public PxShapeGeometryPropertyHelper
{
	typedef PxWriteOnlyPropertyInfo< PxPropertyInfoName::PxShape_Geometry, PxShape, const PxGeometry & >::TSetterType TSetterType;
	typedef PxGeometryHolder (*TGetterType)( const PxShape* inObj );
	PxShapeGeometryProperty( const char* inName, TSetterType inSetter, TGetterType )
		: PxWriteOnlyPropertyInfo< PxPropertyInfoName::PxShape_Geometry, PxShape, const PxGeometry & >( inName, inSetter )
	{
	}
};

struct PxShapeMaterialsPropertyHelper
{
	PX_PHYSX_CORE_API void setMaterials(PxShape* inShape, PxMaterial*const* materials, PxU16 materialCount) const;
};

struct PxShapeMaterialsProperty : public PxReadOnlyCollectionPropertyInfo<PxPropertyInfoName::PxShape_Materials, PxShape, PxMaterial*>
								, public PxShapeMaterialsPropertyHelper
{
	typedef PxReadOnlyCollectionPropertyInfo< PxPropertyInfoName::PxShape_Materials, PxShape, PxMaterial* >::TGetObjectsMember TGetObjectsMember;
	typedef PxReadOnlyCollectionPropertyInfo< PxPropertyInfoName::PxShape_Materials, PxShape, PxMaterial* >::TNbObjectsMember TNbObjectsMember;
	PxShapeMaterialsProperty( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb )
		: PxReadOnlyCollectionPropertyInfo<PxPropertyInfoName::PxShape_Materials, PxShape, PxMaterial*>( inName, inGetter, inNb )
	{
	}
};

struct PxRigidActorShapeCollectionHelper
{
	PX_PHYSX_CORE_API PxShape* createShape(PxRigidActor* inActor, const PxGeometry& geometry, PxMaterial& material, PxShapeFlags shapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE) const;
	PX_PHYSX_CORE_API PxShape* createShape(PxRigidActor* inActor, const PxGeometry& geometry, PxMaterial *const* materials, PxU16 materialCount, PxShapeFlags shapeFlags = PxShapeFlag::eVISUALIZATION | PxShapeFlag::eSCENE_QUERY_SHAPE | PxShapeFlag::eSIMULATION_SHAPE) const;
};

struct PxRigidActorShapeCollection : public PxReadOnlyCollectionPropertyInfo<PxPropertyInfoName::PxRigidActor_Shapes, PxRigidActor, PxShape*>
									, public PxRigidActorShapeCollectionHelper
{
	typedef PxReadOnlyCollectionPropertyInfo< PxPropertyInfoName::PxRigidActor_Shapes, PxRigidActor, PxShape* >::TGetObjectsMember TGetObjectsMember;
	typedef PxReadOnlyCollectionPropertyInfo< PxPropertyInfoName::PxRigidActor_Shapes, PxRigidActor, PxShape* >::TNbObjectsMember TNbObjectsMember;
	PxRigidActorShapeCollection( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb )
		: PxReadOnlyCollectionPropertyInfo<PxPropertyInfoName::PxRigidActor_Shapes, PxRigidActor, PxShape*>( inName, inGetter, inNb )
	{
	}
};

struct PxArticulationLinkCollectionPropHelper
{
	PX_PHYSX_CORE_API PxArticulationLink*	createLink(PxArticulation* inArticulation, PxArticulationLink* parent, const PxTransform& pose) const;
};

struct PxArticulationLinkCollectionProp : public PxReadOnlyCollectionPropertyInfo<PxPropertyInfoName::PxArticulationBase_Links, PxArticulationBase, PxArticulationLink*>
										, public PxArticulationLinkCollectionPropHelper
{
	PxArticulationLinkCollectionProp( const char* inName, TGetObjectsMember inGetter, TNbObjectsMember inNb )
		: PxReadOnlyCollectionPropertyInfo<PxPropertyInfoName::PxArticulationBase_Links, PxArticulationBase, PxArticulationLink*>( inName, inGetter, inNb )
	{
	}
};

template<typename TDataType>
struct PxEnumTraits { PxEnumTraits() : NameConversion( false ) {} bool NameConversion; };

struct NbShapesProperty : public PxIndexedPropertyInfo<PxPropertyInfoName::PxSimulationStatistics_NbShapes, PxSimulationStatistics, PxGeometryType::Enum, PxU32>
{
	PX_PHYSX_CORE_API NbShapesProperty();
};


struct NbDiscreteContactPairsProperty : public PxDualIndexedPropertyInfo<PxPropertyInfoName::PxSimulationStatistics_NbDiscreteContactPairs
																			, PxSimulationStatistics
																			, PxGeometryType::Enum
																			, PxGeometryType::Enum
																			, PxU32> 
{
	PX_PHYSX_CORE_API NbDiscreteContactPairsProperty();
};
struct NbModifiedContactPairsProperty : public PxDualIndexedPropertyInfo<PxPropertyInfoName::PxSimulationStatistics_NbModifiedContactPairs
																			, PxSimulationStatistics
																			, PxGeometryType::Enum
																			, PxGeometryType::Enum
																			, PxU32> 
{
	PX_PHYSX_CORE_API NbModifiedContactPairsProperty();
};

struct NbCCDPairsProperty : public PxDualIndexedPropertyInfo<PxPropertyInfoName::PxSimulationStatistics_NbCCDPairs
																			, PxSimulationStatistics
																			, PxGeometryType::Enum
																			, PxGeometryType::Enum
																			, PxU32>
{
	PX_PHYSX_CORE_API NbCCDPairsProperty();
};

struct NbTriggerPairsProperty : public PxDualIndexedPropertyInfo<PxPropertyInfoName::PxSimulationStatistics_NbTriggerPairs
																			, PxSimulationStatistics
																			, PxGeometryType::Enum
																			, PxGeometryType::Enum
																			, PxU32> 
{
	PX_PHYSX_CORE_API NbTriggerPairsProperty();
};


struct SimulationStatisticsProperty : public PxReadOnlyPropertyInfo<PxPropertyInfoName::PxScene_SimulationStatistics, PxScene, PxSimulationStatistics>
{
	PX_PHYSX_CORE_API SimulationStatisticsProperty();
};

struct PxMetaDataPlane
{
	PxVec3 normal;
	PxReal distance;
	PxMetaDataPlane( PxVec3 n = PxVec3( 0, 0, 0 ), PxReal d = 0 )
		: normal( n )
		, distance( d )
	{
	}
};

#include "PxAutoGeneratedMetaDataObjects.h"

#undef DEFINE_PROPERTY_TO_VALUE_STRUCT_MAP

static PxU32ToName g_physx__PxQueryFlag__EnumConversion[] = {
		{ "eSTATIC", static_cast<PxU32>( PxQueryFlag::eSTATIC ) },
		{ "eDYNAMIC", static_cast<PxU32>( PxQueryFlag::eDYNAMIC ) },
		{ "ePREFILTER", static_cast<PxU32>( PxQueryFlag::ePREFILTER ) },
		{ "ePOSTFILTER", static_cast<PxU32>( PxQueryFlag::ePOSTFILTER ) },
		{ NULL, 0 }
	};

template<> struct PxEnumTraits<PxQueryFlag::Enum > { PxEnumTraits() : NameConversion( g_physx__PxQueryFlag__EnumConversion ) {} const PxU32ToName* NameConversion; }; 


template<typename TObjType, typename TOperator>
inline PxU32 visitAllProperties( TOperator inOperator )
{
	PxU32 thePropCount = PxClassInfoTraits<TObjType>().Info.visitBaseProperties( inOperator );
	return PxClassInfoTraits<TObjType>().Info.visitInstanceProperties( inOperator, thePropCount );
}

template<typename TObjType, typename TOperator>
inline void visitInstanceProperties( TOperator inOperator )
{
	PxClassInfoTraits<TObjType>().Info.visitInstanceProperties( inOperator, 0 );
}

}

/** @} */
#endif
