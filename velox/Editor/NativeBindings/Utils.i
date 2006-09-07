/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%rename(Assign) v3d::utils::VFourCC::operator==;
%ignore v3d::utils::VFourCC::operator!=;
%ignore v3d::utils::VFourCC::operator<;
%rename(toString) v3d::utils::VFourCC::AsStdString;
%include "../../API/V3d/Utils/VFourCC.h"

%include "../../API/V3d/Graphics/Misc/IVCamera.h"
%include "../../API/V3d/Graphics/Misc/VCamera.h"

%include "../../API/V3d/Property/VPropertyManager.h"


