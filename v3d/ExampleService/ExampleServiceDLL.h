/**
 * Example Service DLL
 *
 * Makro um Import und Export in der gleichen Datei zu realisieren
 */
#ifdef EXAMPLESERVICE_EXPORTS
#define EXAMPLESERVICE_API __declspec(dllexport)
#else
#define EXAMPLESERVICE_API __declspec(dllimport)
#endif
//-----------------------------------------------------------------------------
#include <Kernel/ObjReg/VObjectRegistry.h>
//-----------------------------------------------------------------------------

EXAMPLESERVICE_API void Initialize(VObjectRegistry* in_pObjReg);
EXAMPLESERVICE_API void Shutdown();

//-----------------------------------------------------------------------------
