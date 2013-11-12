#include <Game.hpp>
#include <cstring>
#include <System/Memory.hpp>
#include <unistd.h>
#include <IntroductionGameState.hpp>

const ZED_FLOAT32 THRUST_SPEED = 0.2f;
const ZED_FLOAT32 STRAFE_SPEED = 0.2f;
const ZED_FLOAT32 ELEVATE_SPEED = 0.2f;
const ZED_FLOAT32 YAW_SPEED = 0.02f;
const ZED_FLOAT32 PITCH_SPEED = 0.02f;

namespace StickMatch
{
	Game::Game( )
	{
		m_pWindow = ZED_NULL;
		m_pRenderer = ZED_NULL;
		m_pInputManager = ZED_NULL;

		memset( &m_Canvas, 0, sizeof( m_Canvas ) );
		m_Running = ZED_FALSE;
	}

	Game::~Game( )
	{
		zedSafeDelete( m_pInputManager );
		zedSafeDelete( m_pRenderer );
		zedSafeDelete( m_pWindow );
	}

	ZED_UINT32 Game::Execute( )
	{
		// NOT CROSS-PLATFORM!
		XEvent Event;
		ZED::System::WINDOWDATA	WindowData = m_pWindow->WindowData( );
		// !NOT CROSS-PLATFORM
		
		m_Running = ZED_TRUE;

		// Set up the world grid
		m_WorldGrid = ZED::Utility::Grid( m_pRenderer );
		ZED_COLOUR GridColour;
		GridColour.Red = 1.0f;
		GridColour.Green = 1.0f;
		GridColour.Blue = 1.0f;
		GridColour.Alpha = 1.0f;

		if( m_WorldGrid.Initialise( 1000, 1000, ZED::Utility::PLANE_AXIS_XZ,
			GridColour, 0.0f, 1.0f ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		// Set up the debug camera
		m_DebugCamera.ClippingPlanes( 1.0f, 10000.0f );
		ZED::Arithmetic::Matrix4x4 Projection;
		m_DebugCamera.PerspectiveProjection( 45.0f, 1280.0f/720.0f,
			&Projection );
		ZED::Arithmetic::Vector3 CameraVelocity( 0.0f, 0.0f, 0.0f );
		ZED::Arithmetic::Vector3 CameraRotation( 0.0f, 0.0f, 0.0f );
		m_DebugCamera.Position(
			ZED::Arithmetic::Vector3( 0.0f, 100.0f, 100.0f ) );
		ZED_UINT32 HalfWidth = 1280 / 2;
		ZED_UINT32 HalfHeight = 720 / 2;
		m_pWindow->WarpPointer( HalfWidth, HalfHeight );
		ZED_UINT32 MouseX = 0, MouseY = 0;
		m_pWindow->HideCursor( );

		GameAttributes Attribs;
		Attribs.pInputManager = m_pInputManager;
		Attribs.pKeyboard = &m_Keyboard;
		Attribs.pMouse = &m_Mouse;
		Attribs.pRenderer = m_pRenderer;

		m_StateManager.GameAttributes( Attribs );

		m_StateManager.Push( IntroductionGameState::Instance( ) );

		while( m_Running )
		{
			m_pWindow->Update( );
			m_pInputManager->Update( );

			// The reason for this loop is that the left over messages in the
			// queue need to be processed
			while( XPending( WindowData.pX11Display ) > 0 )
			{
				XNextEvent( WindowData.pX11Display, &Event );
			}

			if( m_Keyboard.IsKeyDown( K_ESCAPE ) )
			{
				m_Running = ZED_FALSE;
			}
			m_StateManager.Execute( );
			/*

			if( m_Keyboard.IsKeyDown( 'w' ) )
			{
				CameraVelocity[ 2 ] = -THRUST_SPEED;
			}
			if( m_Keyboard.IsKeyDown( 's' ) )
			{
				CameraVelocity[ 2 ] = THRUST_SPEED;
			}

			if( m_Keyboard.IsKeyDown( K_SHIFT ) )
			{
				CameraVelocity *= 5.0f;
			}

			if( m_Keyboard.IsKeyDown( 'a' ) )
			{
				CameraVelocity[ 0 ] = -STRAFE_SPEED;
			}
			if( m_Keyboard.IsKeyDown( 'd' ) )
			{
				CameraVelocity[ 0 ] = STRAFE_SPEED;
			}

			if( m_Mouse.IsButtonDown( ZED_MOUSE_BUTTON_4 ) )
			{
				CameraVelocity[ 1 ] = ELEVATE_SPEED;
			}
			if( m_Mouse.IsButtonDown( ZED_MOUSE_BUTTON_5 ) )
			{
				CameraVelocity[ 1 ] = -ELEVATE_SPEED;
			}

			m_Mouse.Position( &MouseX, &MouseY );

			if( m_Mouse.IsButtonDown( ZED_MOUSE_BUTTON_2 ) )
			{
				if( MouseX < HalfWidth )
				{
					CameraRotation[ 1 ] = YAW_SPEED;
				}
				if( MouseX > HalfWidth )
				{
					CameraRotation[ 1 ] = -YAW_SPEED;
				}

				if( MouseY < HalfHeight )
				{
					CameraRotation[ 0 ] += PITCH_SPEED;
				}
				if( MouseY > HalfHeight )
				{
					CameraRotation[ 0 ] += -PITCH_SPEED;
				}
			}

			m_DebugCamera.Move( CameraVelocity );
			m_DebugCamera.Rotate( CameraRotation[ 0 ],
				ZED::Arithmetic::Vector3( 1.0f, 0.0f, 0.0f ) );

			zedTrace( "Camera rot: %f\n", CameraRotation[ 0 ] );
			
			this->Update( 16667ULL );
			this->Render( );

			CameraVelocity.Zero( );
//			CameraRotation.Zero( );
			m_pWindow->WarpPointer( HalfWidth, HalfHeight );*/
		}

		m_pWindow->ShowCursor( );

		return ZED_OK;
	}

	void Game::Update( const ZED_UINT64 p_MicroSeconds )
	{
	}

	void Game::Render( )
	{
		ZED::Arithmetic::Matrix4x4	ProjectionView, Projection, View;
		m_DebugCamera.Projection( &Projection );
		m_DebugCamera.View( &View );
		ProjectionView = Projection*View;
		m_pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_WorldGrid.Render( &ProjectionView );
		m_pRenderer->EndScene( );
	}
}

