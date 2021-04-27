#include "SceneManager.h"

void SceneManager::Push(std::unique_ptr<Scene> scene, const bool wantReplace)
{
    m_shouldAdd = true;

    m_newScene = std::move(scene);

    m_shouldReplace = wantReplace;
}

void SceneManager::Pop()
{
    m_shouldRemove = true;
}

void SceneManager::ProcessSceneChange()
{
    if (m_shouldRemove && !m_sceneStack.empty())
    {
        m_sceneStack.pop();

        m_shouldRemove = false;
    }

    if (m_shouldAdd)
    {
        if (m_shouldReplace && !m_sceneStack.empty())
        {          
            m_sceneStack.pop();
            m_shouldReplace = false;
        }

        m_sceneStack.push(std::move(m_newScene));
        m_shouldAdd = false;
        m_sceneStack.top()->Init();
    }
}
