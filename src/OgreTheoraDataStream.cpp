/************************************************************************************
This source file is part of the Ogre3D Theora Video Plugin
For latest info, see http://ogrevideo.sourceforge.net/
*************************************************************************************
Copyright (c) 2008-2010 Kresimir Spes (kreso@cateia.com)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License (LGPL) as published by the
Free Software Foundation; either version 2 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
*************************************************************************************/
#ifndef OGRE_MAC_FRAMEWORK
  #include "OgreRoot.h"
#else
  #include <Ogre/OgreRoot.h>
#endif
#include "OgreTheoraDataStream.h"

namespace Ogre
{
	OgreTheoraDataStream::OgreTheoraDataStream(std::string filename,std::string group_name)
	{
		mName=filename;
		mStream = ResourceGroupManager::getSingleton().openResource(filename,group_name);
	}

	OgreTheoraDataStream::~OgreTheoraDataStream()
	{
		if (!(mStream.isNull()))
		{
			mStream->close();
			mStream.setNull();
		}
	}

	int OgreTheoraDataStream::read(void* output,int nBytes)
	{
		return mStream->read( output,nBytes); 
	}

	void OgreTheoraDataStream::seek(unsigned long byte_index)
	{
		mStream->seek(byte_index);
	}

	std::string OgreTheoraDataStream::repr()
	{
		return mName;
	}

	unsigned long OgreTheoraDataStream::size()
	{
		return mStream->size();
	}

	unsigned long OgreTheoraDataStream::tell()
	{
		return mStream->tell();
	}

} // end namespace Ogre
