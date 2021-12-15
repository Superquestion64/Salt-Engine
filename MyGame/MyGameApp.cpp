#include "MyGameApp.h"

MyGameApp::MyGameApp(): mHero("Assets/Textures/TrueHero.png",0,0)
{
	mShader.Load("Assets/Shader/myVertexShader.glsl",
		"Assets/Shader/myFragmentShader.glsl");
	mShader.SetVec2IntUniform("screenSize", 800, 800);
}

void MyGameApp::OnUpdate()
{
	mHero.Draw(mShader);
}
