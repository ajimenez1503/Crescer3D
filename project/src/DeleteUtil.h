#ifndef _DELETEMACRO_H
#define _DELETEMACRO_H

// Defines
#define SafeRelease(x) { if(x) {x->Release(); x = NULL;} } // Macro for releasing COM object
#define SafeDelete(x) { if(x) {delete x; x = NULL;} } // Macro for deleting objects

#endif
