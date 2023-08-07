#pragma once
#include "SoundSystem.h"
#include <iostream>
#include "SDL.h"

namespace dae
{
	class SoundSystem::SoundSystemImpl
	{
	public:
		SoundSystemImpl()
		{
			Mix_Init(MIX_INIT_MP3);
			Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
		}

		~SoundSystemImpl() = default;

		SoundSystemImpl(const SoundSystemImpl& other) = delete;
		SoundSystemImpl(SoundSystemImpl&& other) = delete;
		SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
		SoundSystemImpl& operator=(SoundSystemImpl&& other) = delete;

		void playSound(const sound_id id, const int volume)
		{
			if (m_Muted) return;

			auto playchunk = m_Sound.at(id);

			if (playchunk == nullptr)
				return;

			auto channel = Mix_PlayChannel(-1, playchunk, 0);
			Mix_Volume(channel, volume);
		}
		void playMusic(const sound_id id, const int volume)
		{

			auto playchunk = m_Sound.at(id);

			if (playchunk == nullptr)
				return;

			auto channel = Mix_PlayChannel(1, playchunk, -1);
			Mix_Volume(channel, volume);
		}
		void Load(const sound_id id, const std::string& path)
		{
			auto datapath = ResourceManager::GetInstance().ReturnDataPath() + "SoundEffects/";
			auto fullpath = datapath + path;
			auto chunk = Mix_LoadWAV(fullpath.c_str());
			m_Sound.emplace(id, chunk);
		}
		void MuteUnmute()
		{
			m_Muted = !m_Muted;
			if (m_Muted)
			{
				//Mix_Volume(-1, 0);
				Mix_Pause(-1);
				std::cout << "Paused\n";
			}
			else
			{
				//Mix_Volume(-1, MIX_MAX_VOLUME);
				Mix_Resume(-1);
				std::cout << "Resumed\n";
			}
		}

	private:
		enum SoundState
		{
			SoundPlay,
			SoundLoaded
		};

		std::map<sound_id, Mix_Chunk*> m_Sound{};
		bool m_Muted = false;
	};

	dae::SoundSystem::SoundSystem()
	{
		m_pImpl = std::make_unique<SoundSystemImpl>();
	}

	SoundSystem::~SoundSystem()
	{
		m_pImpl.reset();
	}

	void dae::SoundSystem::playSound(const dae::sound_id id, const int volume)
	{
		m_pImpl->playSound(id, volume);
	}

	void dae::SoundSystem::playMusic(const sound_id id, const int volume)
	{
		m_pImpl->playMusic(id, volume);
	}

	void dae::SoundSystem::Load(const dae::sound_id id, const std::string& path)
	{
		m_pImpl->Load(id, path);
	}

	void dae::SoundSystem::MuteUnmute()
	{
		m_pImpl->MuteUnmute();
	}

}