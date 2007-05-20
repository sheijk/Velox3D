/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%template(VNodePtrIterator) v3d::VRangeIterator< v3d::VSharedPtr<v3d::entity::VNode> >;
%template(VNodeIterator) v3d::VRangeIterator<v3d::entity::VNode>;

%template(VNodePtr) v3d::VSharedPtr<v3d::entity::VNode>;
%template(VEntityPtr) v3d::VSharedPtr<v3d::entity::VEntity>;
%template(VPartPtr) v3d::VSharedPtr<v3d::entity::IVPart>;

// %template(VPartPtrIterator) v3d::VRangeIterator< v3d::VSharedPtr<v3d::entity::IVPart> >;
// %template(VEntityPtrIterator) v3d::VRangeIterator< v3d::VSharedPtr<v3d::entity::VEntity> >;

//%template(VEntityIterator) v3d::VRangeIterator<v3d::entity::VEntity>;
//%template(VPartIterator) v3d::VRangeIterator<v3d::entity::IVPart>;

%include "../../API/V3d/Entity/VNode.h"
%include "../../API/V3d/Entity/VPartDependency.h"
%include "../../API/V3d/Entity/IVPart.h"
%include "../../API/V3d/Entity/VEntity.h"
%include "../../API/V3d/Entity/IVPartParser.h"
%template(VPartParserIter) v3d::VRangeIterator<v3d::entity::IVPartParser>;
%include "../../API/V3d/Entity/IVEntitySerializationService.h"

%extend v3d::entity::VNode {
	v3d::entity::IVPart* ToPart() {
		return self->Convert<v3d::entity::IVPart>();
	}
	
	v3d::entity::VEntity* ToEntity() {
		return self->Convert<v3d::entity::VEntity>();
	}
}

%extend v3d::VSharedPtr<v3d::entity::IVPart> {
	v3d::VSharedPtr<v3d::entity::VNode> ToNodePtr() {
		return VSharedPtr<VNode>( *self );
	}
}

%extend v3d::VSharedPtr<v3d::entity::VEntity> {
	v3d::VSharedPtr<v3d::entity::VNode> ToNodePtr() {
		return VSharedPtr<VNode>( *self );
	}
}

%javaexception("Exception") v3d::entity::IVSceneParser::ParsePart {
	try {
		$action
	}
	catch(VException& e) {
		jclass clazz = jenv->FindClass("java/lang/RuntimeException");
		std::string msgString = e.ToString();
		jenv->ThrowNew(clazz, msgString.c_str());
		return $null;
	}
	catch(...) {
		jclass clazz = jenv->FindClass("java/lang/RuntimeException");
		jenv->ThrowNew(clazz, "Unknown exception occured");
		return $null;
	}
}

