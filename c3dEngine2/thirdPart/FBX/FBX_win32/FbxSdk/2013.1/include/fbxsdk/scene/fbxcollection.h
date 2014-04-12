/****************************************************************************************
 
   Copyright (C) 2012 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxcollection.h
#ifndef _FBXSDK_SCENE_COLLECTION_H_
#define _FBXSDK_SCENE_COLLECTION_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/fbxobject.h>
#include <fbxsdk/core/fbxmanager.h>
#include <fbxsdk/core/fbxevent.h>
#include <fbxsdk/core/base/fbxerror.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FbxCriteria;

/** A FbxObject derived container for FbxObject.
  * \nosubgrouping
  *
  */
class FBXSDK_DLL FbxCollection : public FbxObject
{
    FBXSDK_OBJECT_DECLARE(FbxCollection, FbxObject);

public:
	/**
	  * \name Collection member management
	  */
	//@{
        //! Deletes all objects in the container.
        virtual void Clear();

        /** Adds a member.
		  * \param pMember Object to be added.
		  */
        virtual bool AddMember(FbxObject* pMember) { return ConnectSrcObject(pMember); }

        /** Removes a member.
		  * \param pMember Object to be removed.
		  */
        virtual bool RemoveMember(FbxObject* pMember) { return DisconnectSrcObject(pMember); }

        /** Returns the number of objects contained within the collection.
		  * \return The number of objects the collection contains.
		  */
        inline int GetMemberCount () const { return GetSrcObjectCount(); }

        /** Returns the member of the collection at the given index.
		  * \param pIndex The given index.
		  * \return The member of the collection at the given index.
		  */
        inline FbxObject* GetMember(int pIndex=0) const { return GetSrcObject(pIndex); }

        /** Judges whether an object is a part of the collection.
		  * \param pMember The member to be judged.
		  * \return \c True if it is a member of the collection, returns \c false if it is not a member.
          */
        virtual bool IsMember(const FbxObject* pMember) const;
	//@}

	/**
	  * \name Templated member management
	  */
	//@{
        /** Returns the number of class T objects contained within the collection.
		  * \return The number of objects of class T the collection contains.
		  */
        template <class T> inline int GetMemberCount(const T*) const { return GetSrcObjectCount(T::ClassId); }

        /** Returns the member of class T at the given index in the collection.
		  * \param pIndex The given index.
		  * \return The member of class T at the given index.
		  */
        template <class T> inline T* GetMember(const T*, int pIndex=0) const { return FbxCast<T>(GetSrcObject(T::ClassId, pIndex)); }

        /** Searches for a member of class T.
		  * \param pName Member name.
		  */
		template <class T> inline T* FindMember(const T*, const char* pName) const { return FbxCast<T>(FindSrcObject(T::ClassId, pName)); }
	//@}

	/**
	  * \name Criteria based member management
	  */
	//@{
        /** Returns the number of class T objects contained within the collection.
		  * \return The number of objects of class T the collection contains.
		  */
        inline int GetMemberCount(const FbxCriteria& pCriteria) const { return GetSrcObjectCount(pCriteria); }

        /** Returns the member of class T at the given index in the collection.
		  * \param pIndex The given index.
		  * \return The member of class T at the given index.
		  */
        inline FbxObject* GetMember(const FbxCriteria& pCriteria, int pIndex=0) const { return GetSrcObject(pCriteria, pIndex); }

        /** Searches for a member of class T.
		  * \param pName Member name.
		  */
		inline FbxObject* FindMember(const FbxCriteria& pCriteria, const char* pName) const { return FindSrcObject(pCriteria, pName); }
	//@}

	/**
	  * \name Selection management
	  */
	//@{
        /** Selects/Deselects all the contained objects.
		  * \param pSelection If \c true, all objects are selected, if \c false, all objects are deselected.
		  */
        virtual void SetSelectedAll(bool pSelection);

        /** Selects/Deselects an object.
		  * \param pObject The object to be selected or deselected.
		  * \param pSelection If \c true, pObject is selected, if \c false, pObject is deselected.
		  */
        virtual void SetSelected(FbxObject* pObject, bool pSelection);

        /** Returns whether the specified object is selected or not.
		  * \param pObject The specified object.
          * \return Whether pObject is selected or not. 
		  */
        virtual bool GetSelected(FbxObject* pObject);
	//@}

///////////////////////////////////////////////////////////////////////////////
//  WARNING!
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
	FbxCollection(FbxManager& pManager, const char* pName);
#endif /* #ifndef DOXYGEN_SHOULD_SKIP_THIS */
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_SCENE_COLLECTION_H_ */
