#ifndef __STICKMATCH_GAME_HPP__
#define __STICKMATCH_GAME_HPP__

#include <System/DataTypes.hpp>
#include <System/Window.hpp>
#include <System/Keyboard.hpp>
#include <System/Mouse.hpp>
#include <System/InputManager.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/CanvasDescription.hpp>
#include <Utility/Grid.hpp>
#include <Renderer/FreeCamera.hpp>

namespace StickMatch
{
	class Game
	{
	public:
		Game( );
		~Game( );

		ZED_UINT32 Initialise( );
		ZED_UINT32 Execute( );

	private:
		void Update( const ZED_UINT64 p_MicroSeconds );
		void Render( );

		ZED::System::Window					*m_pWindow;
		ZED::System::InputManager			*m_pInputManager;
		ZED::System::Keyboard				m_Keyboard;
		ZED::System::Mouse					m_Mouse;
		ZED::Renderer::Renderer				*m_pRenderer;
		ZED::Renderer::CanvasDescription	m_Canvas;

		ZED_BOOL	m_Running;

		ZED::Utility::Grid			m_WorldGrid;
		ZED::Renderer::FreeCamera	m_DebugCamera;
	};
}

#endif

