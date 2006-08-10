%rename(Assign) v3d::utils::VFourCC::operator==;
%ignore v3d::utils::VFourCC::operator!=;
%ignore v3d::utils::VFourCC::operator<;
%rename(toString) v3d::utils::VFourCC::AsStdString;
%include "../../API/V3d/Utils/VFourCC.h"

%include "../../API/V3d/Graphics/Misc/IVCamera.h"
%include "../../API/V3d/Graphics/Misc/VCamera.h"

%include "../../API/V3d/Property/VPropertyManager.h"

