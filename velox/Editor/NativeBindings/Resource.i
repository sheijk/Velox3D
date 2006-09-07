/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%include "../../API/V3d/Resource/VResourceData.h"
%template(VResDataIterator) v3d::VRangeIterator<v3d::resource::VResourceData>;
%template(VResourceIterator) v3d::VRangeIterator<v3d::resource::VResource>;
%ignore v3d::resource::VResource::ChildIterator() const;
%include "../../API/V3d/Resource/VResource.h"
%include "../../API/V3d/Resource/VResourceId.h"
%ignore v3d::resource::IVResourceManager::RegisterResourceType;
%include "../../API/V3d/Resource/IVResourceManager.h"


