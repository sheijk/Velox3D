/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%template(VPartPtrIterator) v3d::VRangeIterator< v3d::VSharedPtr<v3d::entity::IVPart> >;
%template(VEntityPtrIterator) v3d::VRangeIterator< v3d::VSharedPtr<v3d::entity::VEntity> >;

%template(VEntityPtr) v3d::VSharedPtr<v3d::entity::VEntity>;
%template(VPartPtr) v3d::VSharedPtr<v3d::entity::IVPart>;

%template(VEntityIterator) v3d::VRangeIterator<v3d::entity::VEntity>;
%template(VPartIterator) v3d::VRangeIterator<v3d::entity::IVPart>;

%include "../../API/V3d/Entity/VPartDependency.h"
%include "../../API/V3d/Entity/IVPart.h"
%include "../../API/V3d/Entity/VEntity.h"
%include "../../API/V3d/Entity/IVPartParser.h"
%template(VPartParserIter) v3d::VRangeIterator<v3d::entity::IVPartParser>;
%include "../../API/V3d/Entity/IVEntitySerializationService.h"

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

