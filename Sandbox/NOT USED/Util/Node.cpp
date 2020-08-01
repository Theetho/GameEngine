#include "pch.h"
#include "Node.h"

Node::Node()
	: mParent(nullptr)
	, mChildren()
{}

Node::Node(Node* parent)
	: mParent(parent)
	, mChildren()
{}

Node::Node(Node * parent, std::vector<Node*> & children)
	: mParent(parent)
	, mChildren(std::move(children))
{}

Node::~Node()
{}

void Node::OnUpdate(const double& delta)
{
	for (auto& child : mChildren)
	{
		child->OnUpdate(delta);
	}
}

void Node::AddChildren(std::vector<Node*>& children)
{
	mChildren.insert(mChildren.end(), children.begin(), children.end());
}

void Node::AddChild(Node* child)
{
	child->SetParent(this);
	mChildren.push_back(child);
}

const std::vector<Node*>& Node::GetChildren() const
{
	return mChildren;
}

const Node* Node::GetParent() const
{
	return mParent;
}

void Node::SetParent(Node* parent)
{
	mParent = parent;
}

void Node::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{
	for (auto& child : mChildren)
	{
		child->Render(render_command, shader);
	}
}
