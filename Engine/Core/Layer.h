#pragma once

namespace Engine
{
	class Event;
	class Camera3D;

	class Layer
	{
	public:
		virtual ~Layer()
		{}

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate(Ref<Camera3D> camera, const double& delta) = 0;
		virtual void OnEvent(Event& event) = 0;
		virtual void OnEngineGui() = 0;
	protected:
		virtual void OnGui() = 0;
	};
};

