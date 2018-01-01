#pragma once

#include "VectorHelper.hpp"
#include <functional>
#include <vector>

namespace Jagerts::Felcp::Helpers
{
	template<class T>
	using Event = std::function<void(void* sender, const T& arg)>>;

	template<class T>
	class EventHandler
	{
	public:
		inline void Subscribe(Event<T>& event)
		{
			this->_events.push_back(event);
		}

		inline void Unsubscribe(Event<T>& event)
		{
			VectorHelper::RemoveItem(this->_events, event);
		}

		inline void UnsubscribeAll()
		{
			this->_events.clear();
		}

		inline void Execute(void* sender, const T& arg)
		{
			for (int index = 0; index < this->_events.size(); index++)
				this->_events[index](sender, arg);
		}
	private:
		std::vector<Event<T>> _events;
	};
}