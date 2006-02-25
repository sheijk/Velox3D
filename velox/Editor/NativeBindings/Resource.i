%include "../../API/V3d/Resource/VResourceData.h"
%template(VResDataIterator) v3d::VRangeIterator<v3d::resource::VResourceData>;
%template(VResourceIterator) v3d::VRangeIterator<v3d::resource::VResource>;
%ignore v3d::resource::VResource::ChildIterator() const;
%include "../../API/V3d/Resource/VResource.h"
%include "../../API/V3d/Resource/VResourceId.h"
%ignore v3d::resource::IVResourceManager::RegisterResourceType;
%include "../../API/V3d/Resource/IVResourceManager.h"

