#include "cHacks.h"
#include "params.h"
#include "hostable.h"

extern const u8 hosTables[12][0x100][0x100] = {
	HOS_TABLE(CAMERA_MIN_HEIGHT),
	HOS_TABLE((CAMERA_MIN_HEIGHT+CAMERA_Z_STEP)),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(2*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(3*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(4*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(5*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(6*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(7*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(8*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(9*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(10*CAMERA_Z_STEP))),
	HOS_TABLE((CAMERA_MIN_HEIGHT+(11*CAMERA_Z_STEP)))
};