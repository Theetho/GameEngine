#include "pch.h"
#include "Node.h"

Node::Node(Node* parent)
	: mParent(parent)
	, mChildren()
	, mGlobalTransform()
	, mLocalTransform()
{}

Node::~Node()
{}

void Node::OnUpdate(const double& delta)
{
	for (auto child : mChildren)
	{
		child->OnUpdate(delta);
	}
}

void Node::AddChildren(std::vector<Node*>& children)
{
	for (auto child : children)
	{
		this->AddChild(child);
	}
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

Node* Node::GetParent()
{
	return mParent;
}

const Engine::Transform& Node::GetGlobalTransform() const
{
	return mGlobalTransform;
}

const Engine::Transform& Node::GetLocalTransform() const
{
	return mLocalTransform;
}

void Node::SetParent(Node* parent)
{
	mParent = parent;
}

void Node::Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const
{}
