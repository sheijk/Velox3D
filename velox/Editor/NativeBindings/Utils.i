%rename(Assign) v3d::utils::VFourCC::operator==;
%ignore v3d::utils::VFourCC::operator!=;
%ignore v3d::utils::VFourCC::operator<;
%rename(toString) v3d::utils::VFourCC::AsStdString;
%include "../../API/V3dLib/Utils/VFourCC.h"

%include "../../API/V3dLib/Graphics/Misc/IVCamera.h"
%include "../../API/V3dLib/Graphics/Misc/VCamera.h"

%include "../../API/V3dLib/Property/VPropertyManager.h"

