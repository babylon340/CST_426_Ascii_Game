#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include <functional>

class Input
{
private:
	HANDLE threadId;
	std::map<UINT, std::vector<std::function<void(bool)>>*> callbacks;

	static DWORD WINAPI InputProc(LPVOID param)
	{
		std::map<UINT, std::vector<std::function<void(bool)>>*>& callbacks = *(reinterpret_cast<std::map<UINT, std::vector<std::function<void(bool)>>*>*>(param));

		HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
		INPUT_RECORD record;
		DWORD burn;

		while (true)
		{
			ReadConsoleInput(input, &record, 1, &burn);
			if (record.EventType == KEY_EVENT)
			{
				std::map<UINT, std::vector<std::function<void(bool)>>*>::iterator mapItr = callbacks.find(record.Event.KeyEvent.wVirtualKeyCode);
				if (mapItr != callbacks.end())
				{
					std::vector<std::function<void(bool)>>::iterator vecItr = mapItr->second->begin();
					for (; vecItr != mapItr->second->end(); ++vecItr)
					{
						(*vecItr)(record.Event.KeyEvent.bKeyDown);
					}
				}
			}
		}
	}
public:
	Input() : threadId(INVALID_HANDLE_VALUE)
	{
		threadId = CreateThread(NULL, 0, Input::InputProc, &callbacks, CREATE_SUSPENDED, NULL);
	}
	Input(const Input&) = delete;
	~Input()
	{
		for (std::map<UINT, std::vector<std::function<void(bool)>>*>::iterator itr = callbacks.begin();
			itr != callbacks.end(); ++itr)
		{
			delete (*itr).second;
		}
	}
	Input& operator=(const Input&) = delete;

	void Start()
	{
		ResumeThread(threadId);
	}
	void Stop()
	{
		SuspendThread(threadId);
	}

	void AddHandler(UINT keycode, std::function<void(bool)> callback)
	{
		std::map<UINT, std::vector<std::function<void(bool)>>*>::iterator mapItr = callbacks.find(keycode);
		if (mapItr == callbacks.end())
		{
			std::vector<std::function<void(bool)>>* temp = new std::vector<std::function<void(bool)>>();
			callbacks.insert(std::make_pair(keycode, temp));
			mapItr = callbacks.find(keycode);
		}

		mapItr->second->push_back(callback);
	}
};