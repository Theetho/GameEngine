#pragma once

class Node : public Engine::Renderable
{
public:
	Node();
	Node(Node* parent);
	Node(Node* parent, std::vector<Node*>& children);
	virtual ~Node();

	virtual void OnUpdate(const double& delta);

	virtual void AddChildren(std::vector<Node*>& children);
	virtual void AddChild(Node* child);

	const std::vector<Node*>& GetChildren() const;
	const Node*				  GetParent() const;

	void SetParent(Node* parent);
protected:
	Node*			   mParent;
	std::vector<Node*> mChildren;

	virtual void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const;
};

