/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once

#include "Enums.h"

namespace SlimDX
{
	namespace DirectInput
	{
		enum class Key;

		public ref class KeyCollection : public System::Collections::Generic::ICollection<Key>
		{
		private:
			System::Collections::Generic::List<Key>^ list;

		internal:
			KeyCollection() { list = gcnew System::Collections::Generic::List<Key>(); }

			virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
			{
				return ((System::Collections::IEnumerable^)list)->GetEnumerator();
			}

			void AddItem( Key item ) { list->Add( item ); }
			void ClearItems() { list->Clear(); }
			void RemoveItem( Key item ) { list->Remove( item ); }

		public:
			virtual void Add( Key item ) { SLIMDX_UNREFERENCED_PARAMETER(item); throw gcnew System::NotSupportedException(); }
			virtual void Clear() { throw gcnew System::NotSupportedException(); }
			virtual bool Contains( Key item ) { return list->Contains( item ); }
			virtual void CopyTo( array<Key>^ array, int arrayIndex ) { list->CopyTo( array, arrayIndex ); }
			virtual bool Remove( Key item ) { SLIMDX_UNREFERENCED_PARAMETER(item); throw gcnew System::NotSupportedException(); }

			virtual System::Collections::Generic::IEnumerator<Key>^ GetEnumerator() { return list->GetEnumerator(); }

			virtual property int Count
			{
				int get() { return list->Count; }
			}

			virtual property bool IsReadOnly
			{
				bool get() { return true; }
			}
		};
	}
}