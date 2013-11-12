#ifndef __STICKMATCH_GAMEATTRIBUTES_HPP__
#define __STICKMATCH_GAMEATTRIBUTES_HPP__

#include <System/DataTypes.hpp>
#include <Renderer/Renderer.hpp>
#include <System/InputManager.hpp>
#include <System/Keyboard.hpp>
#include <System/Mouse.hpp>

namespace StickMatch
{
	// I know, this is probably the worst solution (and it is), but I need to
	// get this done as soon as possible.  It goes against what I would
	// normally do, but I have to put something together to get a job and I'll
	// re-work the way this works later.
	typedef struct __tagGameAttributes
	{
		ZED::System::InputManager	*pInputManager;
		ZED::System::Keyboard		*pKeyboard;
		ZED::System::Mouse			*pMouse;
		ZED::Renderer::Renderer		*pRenderer;
	} GameAttributes;
}

#endif
