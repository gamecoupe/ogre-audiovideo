/**
* @file OgreOggSoundFactory.cpp
* @author  Ian Stangoe
* @version v1.26
*
* @section LICENSE
* 
* This source file is part of OgreOggSound, an OpenAL wrapper library for   
* use with the Ogre Rendering Engine.										 
*                                                                           
* Copyright (c) 2013 Ian Stangoe
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
*
*/

#include <Ogre.h>

#include "OgreOggSound.h"
#include "OgreOggSoundFactory.h"

using namespace Ogre;
using namespace OgreOggSound;

String OgreOggSoundFactory::FACTORY_TYPE_NAME = "OgreOggISound";
//-----------------------------------------------------------------------
const String& OgreOggSoundFactory::getType(void) const
{
	return FACTORY_TYPE_NAME;
}
//-----------------------------------------------------------------------
#if OGRE_VERSION_MAJOR == 2 && OGRE_VERSION_MINOR == 0
MovableObject* OgreOggSoundFactory::createInstanceImpl(IdType id, ObjectMemoryManager *objectMemoryManager, const NameValuePairList* params)
#elif OGRE_VERSION_MAJOR == 2 && OGRE_VERSION_MINOR > 0
MovableObject* OgreOggSoundFactory::createInstanceImpl(IdType id, ObjectMemoryManager *objectMemoryManager, SceneManager* manager, const NameValuePairList* params)
#else
MovableObject* OgreOggSoundFactory::createInstanceImpl(const String& name, const NameValuePairList* params)
#endif
{
	String fileName;
	#if OGRE_VERSION_MAJOR == 2
	String reName = BLANKSTRING;
	#else
	String reName = name;
	#endif
	
	if (params != 0)
	{
		bool loop = false;
		bool stream = false;
		bool preBuffer = false;
		bool immediate = false;
		SceneManager* scnMgr = 0;

		NameValuePairList::const_iterator fileNameIterator = params->find("fileName");
		if (fileNameIterator != params->end())
		{
			// Get filename
			fileName = fileNameIterator->second;
		}

		NameValuePairList::const_iterator loopIterator = params->find("loop");
		if (loopIterator != params->end())
		{
			// Get loop setting
			loop = StringUtil::match(loopIterator->second,"true",false);
		}

		NameValuePairList::const_iterator streamIterator = params->find("stream");
		if (streamIterator != params->end())
		{
			// Get stream flag
			stream = StringUtil::match(streamIterator->second,"true",false);
		}

		NameValuePairList::const_iterator preBufferIterator = params->find("preBuffer");
		if (preBufferIterator != params->end())
		{
			// Get prebuffer flag
			preBuffer = StringUtil::match(preBufferIterator->second,"true",false);
		}

		NameValuePairList::const_iterator immediateIterator = params->find("immediate");
		if (immediateIterator != params->end())
		{
			// Get prebuffer flag
			immediate = StringUtil::match(immediateIterator->second,"true",false);
		}

		NameValuePairList::const_iterator sManIterator = params->find("sceneManagerName");
		if (sManIterator != params->end())
		{
			// Get SceneManager name
			scnMgr = Ogre::Root::getSingletonPtr()->getSceneManager(sManIterator->second);
		}

		NameValuePairList::const_iterator sNameIterator = params->find("name");
		if (sNameIterator != params->end())
		{
			// Get sound name
			reName = sNameIterator->second;
		}
		
		// when no caption is set
		if ( !scnMgr || reName == "" || fileName == "" )
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
				"'name & fileName & sceneManagerName' parameters required when constructing an OgreOggISound.",
				"OgreOggSoundFactory::createInstance");
		}

		#if OGRE_VERSION_MAJOR == 2
		return OgreOggSoundManager::getSingletonPtr()->_createSoundImpl(scnMgr, reName, id, fileName, stream, loop, preBuffer, immediate);
		#else
		return OgreOggSoundManager::getSingletonPtr()->_createSoundImpl(scnMgr, reName, fileName, stream, loop, preBuffer, immediate);
		#endif
	}

	return 0;
}
