/*
 * symbian_helper.h
 *
 *  Created on: 3.8.2021
 *      Author: Fiodar Stryzhniou
 *
 * Public domain
 */

#ifndef SYMBIAN_HELPER_CPP_
#define SYMBIAN_HELPER_CPP_

#include <e32base.h>

template <class T>
class TAutoClose2
/**
@publishedAll


Automatically calls Close() on an object when that object goes out of scope.

The behaviour takes advantage of the fact that the compiler automatically 
destroys objects that go out of scope.
*/
	{
public:
	inline ~TAutoClose2()
#ifdef __LEAVE_EQUALS_THROW__
	{if (!std::uncaught_exception()) iObj.Close();}
#else
	{iObj.Close();}
#endif

	inline void PushL() {CleanupStack::PushL(TCleanupItem(Close, (TAny *)&iObj));}
	inline void Pop() {CleanupStack::Pop();}
	inline T* operator->() {return &iObj;}
private:
	static void Close(TAny *aObj) {((T *)aObj)->Close();}
public:
	/**
	An instance of the template class.
	*/
	T iObj;
	};

#endif /* SYMBIAN_HELPER_CPP_ */
