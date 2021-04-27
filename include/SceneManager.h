#pragma once

#include <memory>
#include <stack>

#include "Scene.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> m_newScene;
	std::stack<std::unique_ptr<Scene> > m_sceneStack;

	bool m_shouldAdd = false;
	bool m_shouldRemove = false;
	bool m_shouldReplace = false;

public:
	SceneManager() = default;

	Scene& GetCurrent() {return *(m_sceneStack.top().get());}

	void Push(std::unique_ptr<Scene> scene, bool wantReplace = false);
	void Pop();
	void ProcessSceneChange();
};

