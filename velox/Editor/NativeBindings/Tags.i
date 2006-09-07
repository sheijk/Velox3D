/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

%include "../../API/V3d/Tags/VTag.h"
%include "../../API/V3d/Tags/VTagRegistry.h"

%rename(equals) v3d::tags::VTag::operator==;
%ignore v3d::tags::VTag::operator!=;

%template(VTagIterator) v3d::VRangeIterator<const v3d::tags::VTag>;

