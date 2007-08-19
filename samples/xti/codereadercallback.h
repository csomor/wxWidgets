/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xtistrm.h
// Purpose:     streaming runtime metadata information (extended class info)
// Author:      Stefan Csomor
// Modified by:
// Created:     27/07/03
// RCS-ID:      $Id: xtistrm.h 47827 2007-07-31 19:25:09Z FM $
// Copyright:   (c) 2003 Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _CODEDEPERSISTER_
#define _CODEDEPERSISTER_

#include "wx/defs.h"

/*
wxObjectCodeReaderCallback implements the callbacks that will depersist
an object into a C++ initialization function.
*/

class WXDLLIMPEXP_BASE wxTextOutputStream;

class WXDLLIMPEXP_BASE wxObjectCodeReaderCallback: public wxObjectWriterCallback
{
private:
    struct wxObjectCodeReaderCallbackInternal;
    wxObjectCodeReaderCallbackInternal * m_data;
    wxTextOutputStream *m_fp;
    wxString ValueAsCode( const wxxVariant &param );

public:
    wxObjectCodeReaderCallback(wxTextOutputStream *out);
    virtual ~wxObjectCodeReaderCallback();

    // allocate the new object on the heap, that object will have the passed in ID
    virtual void AllocateObject(int objectID, wxClassInfo *classInfo,
        wxxVariantArray &metadata);

    // initialize the already allocated object having the ID objectID 
    // with the Create method creation parameters which are objects are 
    // having their Ids passed in objectIDValues having objectId <> wxInvalidObjectID

    virtual void CreateObject(int objectID,
        const wxClassInfo *classInfo,
        int paramCount,
        wxxVariant *variantValues,
        int *objectIDValues,
        const wxClassInfo **objectClassInfos,
        wxxVariantArray &metadata
        );

    // construct the new object on the heap, that object will have the 
    // passed in ID (for objects that don't support allocate-create type 
    // of creation) creation parameters which are objects are having their 
    // Ids passed in objectIDValues having objectId <> wxInvalidObjectID

    virtual void ConstructObject(int objectID,
        const wxClassInfo *classInfo,
        int paramCount,
        wxxVariant *VariantValues,
        int *objectIDValues,
        const wxClassInfo **objectClassInfos,
        wxxVariantArray &metadata);

    // destroy the heap-allocated object having the ID objectID, this may 
    // be used if an object is embedded in another object and set via value 
    // semantics, so the intermediate object can be destroyed after safely
    virtual void DestroyObject(int objectID, wxClassInfo *classInfo);

    // set the corresponding property
    virtual void SetProperty(int objectID,
        const wxClassInfo *classInfo,
        const wxPropertyInfo* propertyInfo,
        const wxxVariant &variantValue);

    // sets the corresponding property (value is an object)
    virtual void SetPropertyAsObject(int objectId,
        const wxClassInfo *classInfo,
        const wxPropertyInfo* propertyInfo,
        int valueObjectId);

    // adds an element to a property collection
    virtual void AddToPropertyCollection( int objectID,
        const wxClassInfo *classInfo,
        const wxPropertyInfo* propertyInfo,
        const wxxVariant &VariantValue);

    // sets the corresponding property (value is an object)
    virtual void AddToPropertyCollectionAsObject(int objectID,
        const wxClassInfo *classInfo,
        const wxPropertyInfo* propertyInfo,
        int valueObjectId);

    // sets the corresponding event handler
    virtual void SetConnect(int eventSourceObjectID,
        const wxClassInfo *eventSourceClassInfo,
        const wxPropertyInfo *delegateInfo,
        const wxClassInfo *eventSinkClassInfo,
        const wxHandlerInfo* handlerInfo,
        int eventSinkObjectID );
};

#endif
