#pragma once

namespace TypeidSystem
{
	using TypeID = size_t;

	class ITypeID
	{
	public:
		virtual  ~ITypeID() = default;
		virtual TypeID GetTypeID() const = 0;
	};

	inline TypeID GetNextTypeID ()
	{
		static TypeID nextTypeID = 0;
		return nextTypeID++;
	}

	template<typename T>
	TypeID GetTypeID()
	{
		static const TypeID typeID = GetNextTypeID();
		return typeID;
	}

	template<typename T>
	T* SafeCast(ITypeID* _type) {
		if (!_type)
			return nullptr;
		if (_type->GetTypeID() == GetTypeID<T>())
			return static_cast<T*>(_type);
		return nullptr;
	}

	template<typename T>
	const T* SafeCast(const ITypeID* _type) {
		if (!_type)
			return nullptr;
		if (_type->GetTypeID() == GetTypeID<T>())
			return static_cast<const T*>(_type);
		return nullptr;
	}
}

