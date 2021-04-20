#include "SceneManager.h"

SceneManager::SceneManager()
{
}

void SceneManager::push(std::unique_ptr<Scene> scene, bool wantReplace)
{
    m_shouldAdd = true;

    m_newScene = std::move(scene);

    m_shouldReplace = wantReplace;
}

void SceneManager::pop()
{
    m_shouldRemove = true;
}

void SceneManager::processSceneChange()
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
        m_sceneStack.top()->init();
    }
}

std::unique_ptr<Scene>& SceneManager::getCurrent()
{
    return m_sceneStack.top();
}
