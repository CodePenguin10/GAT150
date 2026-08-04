#include "pch.h"
#include "Audio.h"
#include "iostream"

namespace nu
{
	bool Audio::Initialize()
	{
		FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
		if (!CheckFMODResult(result))
			return false;

		void* extradriverdata = nullptr;
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);

		if (!CheckFMODResult(result))
		{
			return false;
		}

		return true;
	}

	void Audio::Shutdown()
	{
		CheckFMODResult(m_fmodSystem->release());
	}

	void Audio::Update()
	{
		CheckFMODResult(m_fmodSystem->update());
	}

	bool Audio::AddSound(const std::string& name, const std::string& filename)
	{
	//	// check if key exists in sounds map
	//	if (/*TODO: check if name already exists in m_sounds*/)
	//	{
	//		std::cerr << "Audio System : name already exists " << name << std::endl;
	//		return false;
	//	}

	//	// create sound from key
	//	FMOD::Sound* sound = nullptr;
	//	FMOD_RESULT result = m_fmodSystem->createSound(/*TODO: pass parameters to create sound*/);
	//	if (!CheckFMODResult(result))
	//		return false;

	//	// insert sound into map
	//	//TODO: add sound to m_sounds using name as key

		return true;
	}

	bool Audio::PlaySound(const std::string& name, bool loop)
	{
		// check if sound exists in sounds map
		if (m_sounds.find(name) == m_sounds.end())
		{
			std::cerr << "Audio System : name doesn't exists " << name << std::endl;
			return false;
		}

		// play sound from key
		FMOD_RESULT result = m_fmodSystem->playSound(m_sounds[name], 0, false, nullptr);
		if (!CheckFMODResult(result))
			return false;

		if (loop)
		{
			m_sounds[name]->setLoopCount(0);
		}

		return true;
	}

	bool Audio::CheckFMODResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cerr << "Error with: " << result << std::endl;
			return false;
		}

		return true;
	}
}