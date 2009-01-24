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

#include <d3d10.h>
#include <vector>

#include "../DataBox.h"
#include "../DataStream.h"

#include "Direct3D10Exception.h"

#include "Device.h"
#include "Texture3D.h"
#include "Texture3DDescription.h"

using namespace System;
using namespace System::IO;

namespace SlimDX
{
namespace Direct3D10
{ 
	Texture3D::Texture3D( ID3D10Texture3D* pointer )
	{
		Construct( pointer );
	}
	
	Texture3D::Texture3D( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}
	
	Texture3D::Texture3D( SlimDX::Direct3D10::Device^ device, Texture3DDescription description )
	{
		Construct( Build( device, description, 0 ) );
	}

	Texture3D::Texture3D( SlimDX::Direct3D10::Device^ device, Texture3DDescription description, DataBox^ data )
	{
		if( data != nullptr )
		{
			D3D10_SUBRESOURCE_DATA initialData;
			initialData.pSysMem = data->Data->RawPointer;
			initialData.SysMemPitch = data->RowPitch;
			initialData.SysMemSlicePitch = data->SlicePitch;
			Construct( Build( device, description, &initialData ) );	
		}
		else 
		{
			Construct( Build( device, description, 0 ) );	
		}
	}
	
	Texture3D::Texture3D( SlimDX::Direct3D10::Device^ device, Texture3DDescription description, array<DataBox^>^ data )
	{
		if( data != nullptr )
		{
			std::vector<D3D10_SUBRESOURCE_DATA> initialData( data->Length );
			for(unsigned int dataIndex = 0; dataIndex < initialData.size(); ++dataIndex ) 
			{
				initialData[dataIndex].pSysMem = data[dataIndex]->Data->RawPointer;
				initialData[dataIndex].SysMemPitch = data[dataIndex]->RowPitch;
				initialData[dataIndex].SysMemSlicePitch = data[dataIndex]->SlicePitch;
			}
			
			Construct( Build( device, description, &initialData[0] ) );	
		} 
		else
		{
			Construct( Build( device, description, 0 ) );	
		}
	}

	Texture3D^ Texture3D::FromPointer( ID3D10Texture3D* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		Texture3D^ tableEntry = safe_cast<Texture3D^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew Texture3D( pointer );
	}

	Texture3D^ Texture3D::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		Texture3D^ tableEntry = safe_cast<Texture3D^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew Texture3D( pointer );
	}
	
	ID3D10Texture3D* Texture3D::Build( SlimDX::Direct3D10::Device^ device, Texture3DDescription description, D3D10_SUBRESOURCE_DATA* data )
	{
		ID3D10Texture3D* texture = 0;
		D3D10_TEXTURE3D_DESC nativeDescription = description.CreateNativeVersion();
		
		if( RECORD_D3D10( device->InternalPointer->CreateTexture3D( &nativeDescription, data, &texture ) ).IsFailure )
			throw gcnew Direct3D10Exception( Result::Last );
		
		return texture;
	} 
	
	Texture3DDescription Texture3D::Description::get()
	{
		D3D10_TEXTURE3D_DESC nativeDescription;
		InternalPointer->GetDesc( &nativeDescription );
		return Texture3DDescription( nativeDescription );
	}
	
	SlimDX::DataBox^ Texture3D::Map( int mipSlice, MapMode mode, MapFlags flags )
	{
		int subresource = D3D10CalcSubresource( mipSlice, 0, Description.MipLevels );
		int mipHeight = GetMipSize( mipSlice, Description.Height );
		
		D3D10_MAPPED_TEXTURE3D mappedBox;
		if( RECORD_D3D10( InternalPointer->Map( subresource, static_cast<D3D10_MAP>( mode ), static_cast<UINT>( flags ), &mappedBox ) ).IsFailure )
			return nullptr;
			
		int lockedSize = mipHeight * mappedBox.DepthPitch;
		return gcnew SlimDX::DataBox( mappedBox.RowPitch, mappedBox.DepthPitch, gcnew DataStream( mappedBox.pData, lockedSize, true, true, false ) );
	}

	void Texture3D::Unmap( int subresource )
	{
		InternalPointer->Unmap( subresource );
	}
	
	Texture3D^ Texture3D::FromFile( SlimDX::Direct3D10::Device^ device, String^ fileName )
	{
		ID3D10Resource* resource = Texture::ConstructFromFile( device, fileName, 0 );
		if( resource == 0 )
			return nullptr;
			
		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( resource ) );
	}
	
	Texture3D^ Texture3D::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory )
	{
		ID3D10Resource* resource = Texture::ConstructFromMemory( device, memory, 0 );
		if( resource == 0 )
			return nullptr;
			
		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( resource ) );
	}
	
	Texture3D^ Texture3D::FromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, int sizeInBytes )
	{
		ID3D10Resource* resource = Texture::ConstructFromStream( device, stream, sizeInBytes, 0 );
		if( resource == 0 )
			return nullptr;
			
		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( resource ) );
	}
	
	Texture3D^ Texture3D::FromFile( SlimDX::Direct3D10::Device^ device, String^ fileName, ImageLoadInformation loadInfo )
	{
		D3DX10_IMAGE_LOAD_INFO info = loadInfo.CreateNativeVersion();
		ID3D10Resource* resource = Texture::ConstructFromFile( device, fileName, &info );
		if( resource == 0 )
			return nullptr;

		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( resource ) );
	}

	Texture3D^ Texture3D::FromMemory( SlimDX::Direct3D10::Device^ device, array<Byte>^ memory, ImageLoadInformation loadInfo )
	{
		D3DX10_IMAGE_LOAD_INFO info = loadInfo.CreateNativeVersion();
		ID3D10Resource* resource = Texture::ConstructFromMemory( device, memory, &info );
		if( resource == 0 )
			return nullptr;

		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( resource ) );
	}

	Texture3D^ Texture3D::FromStream( SlimDX::Direct3D10::Device^ device, Stream^ stream, int sizeInBytes, ImageLoadInformation loadInfo )
	{
		D3DX10_IMAGE_LOAD_INFO info = loadInfo.CreateNativeVersion();
		ID3D10Resource* resource = Texture::ConstructFromStream( device, stream, sizeInBytes, &info );
		if( resource == 0 )
			return nullptr;

		D3D10_RESOURCE_DIMENSION type;
		resource->GetType( &type );
		if( type != D3D10_RESOURCE_DIMENSION_TEXTURE3D )
			throw gcnew InvalidOperationException( "Could not load file as 3D texture." ); 
		return gcnew Texture3D( static_cast<ID3D10Texture3D*>( resource ) );
	}
}
}
