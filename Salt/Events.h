#pragma once

#include "SaltUtils.h"

namespace Salt
{
	class SALT_API KeyPressedEvent
	{
	public:
		KeyPressedEvent(int keyCode);
		int GetKeyCode() const;
	private:
		int mKeyCode{ -1 };
	};
}


