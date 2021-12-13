#pragma once

namespace Salt
{
	class KeyPressedEvent
	{
	public:
		KeyPressedEvent(int keyCode);
		int GetKeyCode() const;
	private:
		int mKeyCode{ -1 };
	};
}


