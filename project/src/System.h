#ifndef _SYSTEM_H
#define _SYSTEM_H

namespace Crescer3D
{
	// Enter new subsystems here
	enum SystemType
	{
		Sys_Invalid,
		Sys_Window,
		Sys_Game,
		Sys_Input,
		Sys_Logger,
		Sys_Player,
		Sys_MAX
	};

	struct SystemData
	{
		SystemData(const SystemType& type);
		SystemType systemType;
	};

	class System
	{
		friend class Engine;

	public:
		System(const SystemData& data);
		virtual ~System();

		virtual bool Initialize() { return true; }
		virtual bool Update() { return true; }
		virtual bool ShutDown() { return true; }

		inline SystemType GetType() { return m_SystemType; }

	protected:
		SystemType m_SystemType;
	};
}

#endif // _SYSTEM_H