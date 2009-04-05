/*
* Copyright (c) 2007-2009 SlimDX Group
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

#include "Handle.h"

namespace SlimMath {
	public interface struct IOperation {
		property array<System::IntPtr>^ Parameters {
			virtual array<System::IntPtr>^ get() = 0;
		}

		property array<System::IntPtr>^ Results {
			virtual array<System::IntPtr>^ get() = 0;
		}

		property int Op {
			virtual int get() = 0;
		}
	};

	generic<typename T> where T : value class
	public ref class Operation sealed : IOperation {
	private:
		array<System::IntPtr>^ parameters;
		array<System::IntPtr>^ results;
		IHandle^ result;
		int op;

	internal:
		Operation(Handle<T>^ result, array<System::IntPtr>^ parameters, int op);

	public:
		property array<System::IntPtr>^ Parameters {
			virtual array<System::IntPtr>^ get() { return parameters; }
		}

		property array<System::IntPtr>^ Results {
			virtual array<System::IntPtr>^ get() { return results; }
		}

		property int Op {
			virtual int get() { return op; }
		}

		property IHandle^ Result {
			virtual IHandle^ get() { return result; }
		}
	};

	generic<typename T, typename U, typename V> where T : value class where U : value class where V : value class
	public ref class CompoundOperation sealed : IOperation {
	private:
		array<System::IntPtr>^ parameters;
		array<System::IntPtr>^ results;
		CompoundHandle<T, U, V>^ result;
		int op;

	internal:
		CompoundOperation(CompoundHandle<T, U, V>^ result, array<System::IntPtr>^ parameters, int op);

	public:
		property array<System::IntPtr>^ Parameters {
			virtual array<System::IntPtr>^ get() { return parameters; }
		}

		property array<System::IntPtr>^ Results {
			virtual array<System::IntPtr>^ get() { return results; }
		}

		property int Op {
			virtual int get() { return op; }
		}

		property CompoundHandle<T, U, V>^ Result {
			CompoundHandle<T, U, V>^ get() { return result; }
		}
	};

	generic<typename T, typename U> where U : value class
	public ref class TransformVector4ArrayOperation sealed : IOperation {
	private:
		System::Collections::Generic::List<System::Runtime::InteropServices::GCHandle>^ handles;
		array<T>^ source;
		array<System::IntPtr>^ fixedParameters;
		array<T>^ results;
		array<System::IntPtr>^ fixedResults;
		Handle<U>^ transform;
		int op;

	internal:
		TransformVector4ArrayOperation(array<T>^ result, array<T>^ parameters, Handle<U>^ transform, int op);

	public:
		property array<System::IntPtr>^ Parameters {
			virtual array<System::IntPtr>^ get() {
				if(fixedParameters == nullptr) {
					fixedParameters = gcnew array<System::IntPtr>(3);
					System::Runtime::InteropServices::GCHandle handle = System::Runtime::InteropServices::GCHandle::Alloc(source, System::Runtime::InteropServices::GCHandleType::Pinned);
					if(handles == nullptr)
						handles = gcnew System::Collections::Generic::List<System::Runtime::InteropServices::GCHandle>();
					handles->Add(handle);
					fixedParameters[0] = handle.AddrOfPinnedObject();
					fixedParameters[1] = transform->RawData;
					fixedParameters[2] = System::IntPtr(source->Length);
				}

				return fixedParameters;
			}
		}

		property array<System::IntPtr>^ Results {
			virtual array<System::IntPtr>^ get() {
				if(fixedResults == nullptr) {
					fixedResults = gcnew array<System::IntPtr>(1);
					System::Runtime::InteropServices::GCHandle handle = System::Runtime::InteropServices::GCHandle::Alloc(results, System::Runtime::InteropServices::GCHandleType::Pinned);
					if(handles == nullptr)
						handles = gcnew System::Collections::Generic::List<System::Runtime::InteropServices::GCHandle>();
					handles->Add(handle);
					fixedResults[0] = handle.AddrOfPinnedObject();
				}

				return fixedResults;
			}
		}

		property int Op {
			virtual int get() { return op; }
		}

		property array<T>^ Result {
			array<T>^ get() { return results; }
		}
	};
}