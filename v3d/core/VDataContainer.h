#ifndef V3D_VDATACONTAINER_H
#define V3D_VDATACONTAINER_H

// disable warning 
#pragma warning( disable : 4786)

#include <string>
#include <map>
#include <Core/VMapContainer.h>
#include <Core/VTypes.h>

// *** VDataContainer ***
// Synopsis:
//    - allows you to store options identified by a string. option types can
//    be bool, int and string
//    options can be stored internal or be linked to external vars
class VDataContainer
{
public:
   typedef std::string DataId;
   enum EDataType { eNone, eText, eBool, eNumber };

   // *** CDataContainer ***
   // Synopsis:
   //    - constructor, what did you expect ?
   VDataContainer();

   // *** ~CDataContainer ***
   // Synopsis:
   //    - wow, a destructor !
   ~VDataContainer();

   // *** Clear ***
   // Synopsis:
   //    - removes all data
   void Clear();

   // *** GetType ***
   // Synopsis:
   //    - returns the type of option id
   EDataType GetType(DataId id) const;

   // *** TextCount ***
   // Synopsis:
   //    - returns number of texts (strings)
   vuint TextCount() const;

   // *** NumberCount ***
   // Synopsis:
   //    - returns number of numbers (ints)
   vuint NumberCount() const;

   // *** BoolCount ***
   // Synopsis:
   //    - returns number of bools
   vuint BoolCount() const;

   // *** GetTextId ***
   // Synopsis:
   //    - return id of text number nNumber
   // Inputs:
   //    - vuint nNumber: number of desired id
   // Returns:
   //    - DataId: the data id of option no. nNumber
   DataId GetTextId(vuint nNumber) const;

   // *** GetBoolId ***
   // Synopsis:
   //    - return id of bool number nNumber
   // Inputs:
   //    - vuint nNumber: number of desired id
   // Returns:
   //    - DataId: the data id of option no. nNumber
   DataId GetBoolId(vuint nNumber) const;

   // *** GetBoolId ***
   // Synopsis:
   //    - return id of nNumber-th number
   // Inputs:
   //    - vuint nNumber: number of desired id
   // Returns:
   //    - DataId: the data id of option no. nNumber
   DataId GetNumberId(vuint nNumber) const;

   // *** SetText ***
   // Synopsis:
   //    - change text
   // Inputs:
   //    - DataId id: the identifier of the option
   //    - std::string strVal: the new value
   virtual void SetText(DataId id, std::string strVal);

   // *** SetBool ***
   // Synopsis:
   //    - change bool
   // Inputs:
   //    - DataId id: the identifier of the option
   //    - std::string strVal: the new value
   virtual void SetBool(DataId id, vbool bVal);

   // *** SetNumber ***
   // Synopsis:
   //    - change number
   // Inputs:
   //    - DataId id: the identifier of the option
   //    - std::string strVal: the new value
   virtual void SetNumber(DataId id, vint nVal);

   // *** GetText ***
   // Synopsis:
   //    - get an option
   // Inputs:
   //    - DataId id: identifier of option to be changed
   // Returns:
   //    - std::string the text
   std::string GetText(DataId id) const;

   // *** GetBool ***
   // Synopsis:
   //    - get an option
   // Inputs:
   //    - DataId id: identifier of option to be changed
   // Returns:
   //    - vbool the text
   bool GetBool(DataId id) const;

   // *** GetText ***
   // Synopsis:
   //    - get an option
   // Inputs:
   //    - DataId id: identifier of option to be changed
   // Returns:
   //    - std::string the text
   int GetNumber(DataId id) const;

   // *** AddText ***
   // Synopsis:
   //    - create a new option
   // Inputs:
   //    - DataId id: identifier for new option
   //    - std::string* pStr: pointer to external data, 0 to create it internally
   // Returns:
   //    - vbool: true if succeeded, false if failed
   vbool AddText(DataId id, std::string* pStr = 0);

   // *** AddBool ***
   // Synopsis:
   //    - create a new option
   // Inputs:
   //    - DataId id: identifier for new option
   //    - vbool* pBool: pointer to external data, 0 to create it internally
   // Returns:
   //    - vbool: true if succeeded, false if failed
   vbool AddBool(DataId id, vbool* pBool = 0);

   // *** AddNumber ***
   // Synopsis:
   //    - create a new option
   // Inputs:
   //    - DataId id: identifier for new option
   //    - vint* pNumber: pointer to external data, 0 to create it internally
   // Returns:
   //    - vbool: true if succeeded, false if failed
   vbool AddNumber(DataId id, vint* pNumber = 0);

   void operator=(const VDataContainer& cont);
private:
   VMapContainer< DataId, std::string > m_Texts;
   VMapContainer< DataId, bool > m_Bools;
   VMapContainer< DataId, int > m_Numbers;
protected:
};

//---------------------------------------------------------------------------
#endif
