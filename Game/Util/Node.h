#pragma once

class Node : public Engine::Renderable
{
public:
	Node(Node* parent = nullptr);
	~Node();

	virtual void OnUpdate(const double& delta);

	void AddChildren(std::vector<Node*>& children);
	void AddChild(Node* child);

	const std::vector<Node*>& GetChildren() const;
	Node*					  GetParent();
	const Engine::Transform&  GetGlobalTransform() const;
	const Engine::Transform&  GetLocalTransform() const;

	void SetParent(Node* parent);
protected:
	Node*			   mParent;
	std::vector<Node*> mChildren;
	Engine::Transform  mGlobalTransform;
	Engine::Transform  mLocalTransform;

	virtual void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const = 0;
};

