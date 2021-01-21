#pragma once

#include <memory>
#include <stack>

#include "Scene.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> m_newScene;
	std::stack<std::unique_ptr<Scene> > m_sceneStack;

	bool m_shouldAdd;
	bool m_shouldRemove;
	bool m_shouldReplace;

public:
	SceneManager();
	~SceneManager();

public:
	void push(std::unique_ptr<Scene> scene, bool wantReplace = false);
	void pop();
	void processSceneChange();

public:
	std::unique_ptr<Scene>& getCurrent();
};

