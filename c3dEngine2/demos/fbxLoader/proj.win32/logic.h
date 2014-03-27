#include "myh.h"

inline void updateLogic(long dt,long t){
	//不管可见与否都播动画，反正播动画不需任何开销，仅是时间++而已
		modelx2.animationAdvance_rollback(1*dt);
	

}
